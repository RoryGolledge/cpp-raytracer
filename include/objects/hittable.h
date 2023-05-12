#ifndef OBJECTS_HITTABLE_H
#define OBJECTS_HITTABLE_H

#include <glm/detail/qualifier.hpp>
#include <materials/material.h>
#include <optional>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ray.h>
#include <utility>

namespace objects {
    struct hit_record {
        glm::vec3 position;
        glm::vec3 normal;
        // TODO: This probably doesn't need to be a pointer. Some level of
        // indirection is needed, but referencing is a hassle in the current system
        material::material* material;
        float t;

        bool front_face;

        hit_record() = default;

        hit_record(const hit_record& other):
            position(other.position),
            normal(other.normal),
            material(other.material) {}

        auto operator=(const hit_record& other) -> hit_record& {
            position = other.position;
            normal = other.normal;
            material = other.material;

            return *this;
        }

        // Self-moving is a you-problem
        auto operator=(hit_record&& other) -> hit_record& {
            position = std::exchange(other.position, {});
            normal = std::exchange(other.normal, {});
            material = std::exchange(other.material, nullptr);

            return *this;
        }

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

