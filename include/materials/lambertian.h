#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <glm/geometric.hpp>

#include <ray.h>
#include <materials/material.h>
#include <objects/hittable.h>

namespace material {
    class lambertian : public material {
    public:
        lambertian(const colour::colour a) : albedo(a) {}

        virtual auto scatter(
            const ray::ray& r_in, const objects::hit_record& rec
        ) const -> std::optional<scatter_out> override;

        colour::colour albedo;
    };
}

#endif // LAMBERTIAN_H
       //
