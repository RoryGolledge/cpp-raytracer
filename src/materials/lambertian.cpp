
#include <materials/lambertian.h>

auto material::lambertian::scatter(
    const ray::ray& r_in, const objects::hit_record& rec
) const -> std::optional<scatter_out> {
    (void) r_in;
    auto scatter_direction = rec.normal + glm::normalize(ray::random_in_unit_sphere());
    if (
        scatter_direction.x < 1e-8f &&
        scatter_direction.y < 1e-8f &&
        scatter_direction.z < 1e-8f
    ) {
        scatter_direction = rec.normal;
    }

    return {{albedo, {rec.position, scatter_direction}}};
}
