#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <glm/geometric.hpp>

#include <ray.h>
#include <materials/material.h>
#include <objects/hittable.h>

namespace material {
    class dielectric : public material {
    public:
        dielectric(
            const float refraction_index,
            const colour::colour a = colour::colour{1.0, 1.0, 1.0}
        ) : albedo(a), refraction_index(refraction_index) {}

        virtual auto scatter(
            const ray::ray& r_in, const objects::hit_record& rec
        ) const -> std::optional<scatter_out> override;

        colour::colour albedo;
        float refraction_index;
    };
}

#endif // DIELECTRIC_H

