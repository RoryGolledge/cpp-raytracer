#ifndef CAMERA_H
#define CAMERA_H

#include <ray.h>
#include <glm/vec3.hpp>

namespace camera {
    class camera {
    public:
        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            origin = glm::vec3{0};
            horizontal = glm::vec3(viewport_width, 0, 0);
            vertical = glm::vec3(0, viewport_height, 0);
            lower_left_corner = origin - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length);
        }

        ray::ray get_ray(float u, float v) const {
            return {
                origin,
                lower_left_corner + u * horizontal + v * vertical - origin
            };
        }

    private:
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
    };
}

#endif // CAMERA_H

