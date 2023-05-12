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
        sphere(glm::vec3 centre, float radius, material::material& mat):
            centre(centre), radius(radius), mat(mat) {};
        sphere(const sphere& other):
            centre(other.centre), radius(other.radius), mat(other.mat) {};

        virtual auto hit(
            const ray::ray& r, float t_min, float t_max
        ) const -> std::optional<hit_record> override;

    public:
        glm::vec3 centre;
        float radius;
        material::material& mat;
    };
}

#endif // OBJECTS_SPHERE_H

