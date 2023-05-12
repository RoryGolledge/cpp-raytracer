#ifndef MATERIAL_H
#define MATERIAL_H

#include <colour.h>
#include <optional>
#include <ray.h>

namespace objects {
    struct hit_record;
}

namespace material {
    struct scatter_out {
        colour::colour attenuation;
        ray::ray scatter;
    };

    struct material {
        virtual auto scatter(
            const ray::ray& r_in, const objects::hit_record& rec
        ) const -> std::optional<scatter_out> = 0;

        virtual ~material() = default;
    };
}

#endif // MATERIAL_H

