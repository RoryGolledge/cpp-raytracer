#ifndef HITTABLE_GROUP_H
#define HITTABLE_GROUP_H

#include <objects/hittable.h>
#include <ray.h>

#include <utility>
#include <vector>
#include <memory>

#include <iostream>

namespace objects {
    template <typename ...Ts>
    concept all_hittables = (... && std::derived_from<Ts, hittable>);

    template <typename ...Ts>
    requires
        all_hittables<Ts...>
    class hittable_group : public hittable {
    public:

        hittable_group(const std::tuple<Ts...>& nodes): nodes(nodes) {};
        hittable_group(const std::tuple<Ts...>&& nodes): nodes(nodes) {};

        template <typename ...Args>
        //requires
        //    std::is_same_v<Ts..., Args...>
        hittable_group(Args&&... args): nodes(std::forward<Args>(args)...) {};

        virtual auto hit(
            const ray::ray& r, float t_min, float t_max
        ) const -> std::optional<hit_record> override {
            auto record = std::optional<hit_record>{};
            do_hit<sizeof...(Ts) - 1>(r, t_min, t_max, record);

            return record;
        }

    private:
        std::tuple<Ts...> nodes;

        template <std::size_t Index>
        requires 
            (Index < sizeof...(Ts))
        auto do_hit(
            const ray::ray& r, const float t_min, const float t_max,
            std::optional<hit_record>& rec
        ) const -> void {
            auto closest_so_far = t_max;

            auto this_record = std::get<Index>(nodes).hit(r, t_min, t_max);

            if (this_record.has_value()) {
                closest_so_far = this_record->t;
                rec = std::move(this_record);
            }

            if constexpr (Index != 0) {
                do_hit<Index - 1>(r, t_min, closest_so_far, rec);
            }
        }
    };
}

#endif // HITTABLE_GROUP_H

