#include <cmath>

#include <glm/ext.hpp>

#include <camera.h>

namespace camera {
    camera::camera(
        glm::vec3 position,
        glm::vec3 look_at,
        glm::vec3 world_up_vector,
        float vfov,
        float aspect_ratio
    ) {
        auto theta = glm::radians(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2.f * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto view_direction = glm::normalize(position - look_at);
        auto side_vector = glm::normalize(glm::cross(world_up_vector, view_direction));
        auto up_vector = glm::cross(view_direction, side_vector);

        origin = position;
        horizontal = viewport_width * side_vector;
        vertical = viewport_height * up_vector;
        lower_left_corner = origin - horizontal / 2.f - vertical / 2.f - view_direction;
    }

    auto camera::get_ray(float u, float v) const -> ray::ray {
        return {
            origin,
            lower_left_corner + u * horizontal + v * vertical - origin
        };
    }
}
