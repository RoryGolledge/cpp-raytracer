#ifndef COLOUR_H
#define COLOUR_H

#include <algorithm>
#include <cmath>

#include <glm/vec3.hpp>

namespace colour {
    using colour = glm::vec3;

    inline auto write_colour(
        std::ostream &out, colour pixel_color, int samples_per_pixel
    ) -> void {
        auto r = pixel_color.r;
        auto g = pixel_color.g;
        auto b = pixel_color.b;

        // Divide the color by the number of samples.
        auto scale = 1.f / static_cast<float>(samples_per_pixel);
        r = std::sqrt(r * scale);
        g = std::sqrt(g * scale);
        b = std::sqrt(b * scale);

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256.f * std::clamp(r, 0.f, .999f)) << ' '
            << static_cast<int>(256.f * std::clamp(g, 0.f, .999f)) << ' '
            << static_cast<int>(256.f * std::clamp(b, 0.f, .999f)) << '\n';
    }
}

#endif // COLOUR_H

