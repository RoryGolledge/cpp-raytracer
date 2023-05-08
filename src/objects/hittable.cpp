#include <objects/hittable.h>

auto objects::hit_record::set_face_normal(
    const ray::ray &r, const glm::vec3 &outward_normal
) -> void {
    front_face = glm::dot(r.direction, outward_normal) < 0;
    normal = front_face ? outward_normal :-outward_normal;
}

