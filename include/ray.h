#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

namespace ray {
    struct ray {
        ray(const glm::vec3& origin, const glm::vec3& direction):
            origin(origin), direction(direction) {}

        auto at(float t) const -> glm::vec3 {
            return origin + direction * t;
        }

        glm::vec3 origin;
        glm::vec3 direction;
    };
}
#endif // RAY_H

