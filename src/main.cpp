#include <array>
#include <thread>
#include <iostream>
#include <limits>
#include <random>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <camera.h>
#include <colour.h>
#include <objects/hittable_group.h>
#include <objects/sphere.h>
#include <ray.h>

auto random_float() -> float {
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution(0.f, 1.f);
    return distribution(generator);
}

auto ray_colour(
    const ray::ray& r, const objects::hittable& world, uint16_t depth
) -> colour::colour {
    if (depth == 0) return {};

    auto random_in_unit_sphere = []() -> glm::vec3 {
        while (true) {
            auto v = glm::vec3{
                (random_float() - 0.5f) * 2.f, (random_float() - 0.5f) * 2.f, (random_float() - 0.5f) * 2.f
            };
            if (std::pow(glm::length(v), 2) < 1) return v;
        }
    };

    auto record = world.hit(r, 0.001f, std::numeric_limits<float>::infinity());
    if (record.has_value()) {
        auto target = record->position + record->normal + glm::normalize(random_in_unit_sphere());
        return .5f * ray_colour(
            {record->position, target - record->position}, world, depth - 1
        );
    }

    auto unit_direction = glm::normalize(r.direction);
    auto t = .5f * (unit_direction.y + 1.f);
    return (1.f - t) * colour::colour{1., 1., 1.} + t * colour::colour{.5, .7, 1.};
}

int main(void) {
    // World
    const auto world = objects::hittable_group<objects::sphere, objects::sphere>{
        objects::sphere{{0, 0, -1}, .5f},
        objects::sphere{{0, -100.5, -1}, 100},
    };

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Camera
    camera::camera cam;
    
    // Thread
    const size_t standard_chunk_size = 16;
    const size_t n_chunks = image_height / standard_chunk_size;
    auto chunk_buffer = std::array<std::array<colour::colour, image_width>, standard_chunk_size>{};

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    size_t remaining_lines = image_height;
    std::cerr << "\rScanlines remaining: " << remaining_lines << ' ' << std::flush;

    for (auto chunk = size_t{0}; chunk <= n_chunks; ++chunk) {
        size_t chunk_size = standard_chunk_size;
        if (chunk == n_chunks) {
            chunk_size = image_height % standard_chunk_size;
        }

        auto threads = std::vector<std::thread>{chunk_size};

        for (auto thread_id = size_t{0}; thread_id < chunk_size; ++thread_id) {
            threads[thread_id] = std::thread{[&, thread_id](){
                auto const row = image_height - (chunk * standard_chunk_size + thread_id);

                for (auto col = size_t{0}; col < image_width; ++col) {
                    for (int _ = 0; _ < samples_per_pixel; ++_) {
                        auto u = (static_cast<float>(col) + random_float()) / (image_width - 1);
                        auto v = (static_cast<float>(row) + random_float()) / (image_height - 1);
                        auto r = cam.get_ray(u, v);
                        chunk_buffer[thread_id][col] += ray_colour(r, world, max_depth);
                    }
                }
            }};
        }

        for (auto& thread: threads) {
            thread.join();
        }

        for (auto row = size_t{0}; row < chunk_size; ++row) {
            for (auto& pixel: chunk_buffer[row]) {
                colour::write_colour(std::cout, pixel, samples_per_pixel);
                pixel = {};
            }
        }

        remaining_lines -= chunk_size;
        std::cerr << "\rScanlines remaining: " << remaining_lines << ' ' << std::flush;
    }

    std::cerr << "\nDone.\n";

	return 0;
}
