#ifndef OBJECTS_HITTABLE_H
#define OBJECTS_HITTABLE_H

#include <optional>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ray.h>

namespace objects {
    struct hit_record {
        glm::vec3 position;
        glm::vec3 normal;
        float t;

        bool front_face;

        auto set_face_normal(
            const ray::ray& r, const glm::vec3& outward_normal
        ) -> void;
    };

    struct hittable {
        virtual auto hit(
            const ray::ray& r, float t_min, float t_max
        ) const -> std::optional<hit_record> = 0;

        virtual ~hittable() = default;
    };
}

#endif // OBJECTS_HITTABLE_H

