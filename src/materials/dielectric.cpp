
#include "ray.h"
#include <materials/dielectric.h>

namespace {
    auto reflectance(float cosine, float ref_idx) -> float {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * static_cast<float>(std::pow((1 - cosine), 5));
    }
}

auto material::dielectric::scatter(
    const ray::ray& r_in, const objects::hit_record& rec
) const -> std::optional<scatter_out> {
    float refraction_ratio = rec.front_face ? (1.f / refraction_index) : refraction_index;

    auto unit_direction = glm::normalize(r_in.direction);
    auto cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.f);
    auto sin_theta = std::sqrt(1.f - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.f;

    auto direction = glm::vec3{};

    if (
        cannot_refract ||
        reflectance(cos_theta, refraction_ratio) > ray::random_float()
    ) {
        direction = glm::reflect(unit_direction, rec.normal);
    } else {
        direction = glm::refract(unit_direction, rec.normal, refraction_ratio);
    }

    return {{albedo, {rec.position, direction}}};
}

