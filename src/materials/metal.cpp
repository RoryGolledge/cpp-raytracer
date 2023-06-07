#include "ray.h"
#include <materials/metal.h>

auto material::metal::scatter(
    const ray::ray& r_in, const objects::hit_record& rec
) const -> std::optional<scatter_out> {
    glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction), rec.normal);
    auto out = scatter_out{
        albedo,
        {rec.position, reflected + fuzz * ray::random_in_unit_sphere()}
    };

    if (dot(out.scatter.direction, rec.normal) > 0) {
        return out;
    }

    return {};
}
