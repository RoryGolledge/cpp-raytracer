#ifndef OBJECTS_SPHERE_H
#define OBJECTS_SPHERE_H

#include <optional>

#include <objects/hittable.h>
#include <glm/vec3.hpp>

#include <ray.h>
#include <utility>

namespace objects {
    class sphere : public hittable {
        public:
            sphere(glm::vec3& centre, float radius) : centre(centre), radius(radius) {};
            sphere(glm::vec3&& centre, float radius) : centre(centre), radius(radius) {};

            sphere(sphere&& other): 
                centre(std::exchange(other.centre, {0, 0, 0})),
                radius(std::exchange(other.radius, 1.f)) {}

            virtual auto hit(
                const ray::ray& r, float t_min, float t_max
            ) const -> std::optional<hit_record> override;

        public:
            glm::vec3 centre;
            float radius;
    };
}

#endif // OBJECTS_SPHERE_H

