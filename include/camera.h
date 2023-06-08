#ifndef CAMERA_H
#define CAMERA_H

#include <ray.h>
#include <glm/vec3.hpp>

namespace camera {
    class camera {
    public:
        camera(
            glm::vec3 position,
            glm::vec3 look_at,
            glm::vec3 up_vector,
            float vfov,
            float aspect_ratio
        );

        auto get_ray(float u, float v) const -> ray::ray;

    private:
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
    };
}

#endif // CAMERA_H

