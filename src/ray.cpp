#include <random>

#include <glm/geometric.hpp>

#include <ray.h>

auto ray::random_float() -> float {
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution(0.f, 1.f);
    return distribution(generator);
}

auto ray::random_in_unit_sphere() -> glm::vec3 {
    while (true) {
        auto v = glm::vec3{
            (random_float() - 0.5f) * 2.f, (random_float() - 0.5f) * 2.f, (random_float() - 0.5f) * 2.f
        };
        if (std::pow(glm::length(v), 2) < 1) return v;
    }
};

