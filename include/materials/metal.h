#ifndef METAL_H
#define METAL_H

#include <glm/geometric.hpp>

#include <ray.h>
#include <materials/material.h>
#include <objects/hittable.h>

namespace material {
    class metal : public material {
    public:
        metal(const colour::colour a, const float fuzz):
            albedo(a), fuzz(fuzz < 1 ? fuzz : 1) {}

        virtual auto scatter(
            const ray::ray& r_in, const objects::hit_record& rec
        ) const -> std::optional<scatter_out> override;

        colour::colour albedo;
        float fuzz;
    };
}

#endif // METAL_H

