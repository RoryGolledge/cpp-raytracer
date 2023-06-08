#include "ray.h"
#include <materials/metal.h>

auto material::metal::scatter(
    const ray::ray& r_in, const objects::hit_record& rec
) const -> std::optional<scatter_out> {
    auto reflected = glm::reflect(glm::normalize(r_in.direction), rec.normal);
    auto direction = reflected + fuzz * ray::random_in_unit_sphere();

    if (dot(direction, rec.normal) > 0) {
        return {{albedo, {rec.position, direction}}};
    }

    return {};
}
