#include <glm/geometric.hpp>

#include <objects/sphere.h>

auto objects::sphere::hit(
    const ray::ray& r, float t_min, float t_max
) const -> std::optional<hit_record> {
    auto oc = r.origin - centre;
    auto a = static_cast<float>(std::pow(glm::length(r.direction), 2));
    auto half_b = dot(oc, r.direction);
    auto c = static_cast<float>(std::pow(glm::length(oc), 2)) - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return {};

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return {};
    }

    auto record = hit_record{};
    record.t = root;
    record.position = r.at(record.t);
    auto outward_normal = (record.position - centre) / radius;

    record.set_face_normal(r, outward_normal);

    return { record };
}

