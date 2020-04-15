#pragma once

#include <algorithm>
#include <future>
#include <execution>

namespace lab {

    namespace detail {

        constexpr static auto PARALLELING_POINT = 7000;

        template<typename Iter, typename Comp>
        void default_quick (Iter beg, Iter end, Comp comp) {

            const auto distance = std::distance(beg, end);

            if (distance < 2) {
                return;
            }
            using std::swap;

            auto last = std::prev(end);
            swap(*std::next(beg, distance / 2), *last);

            auto bound = std::partition(beg, last, [&](const auto &el) {
                return comp(el, *last);
            });
            swap(*bound, *last);

            default_quick(beg, bound, comp);
            default_quick(std::next(bound), end, comp);
        }


        template<typename Iter, typename Comp>
        void parallel_quick(Iter beg, Iter end, Comp comp) {

            const auto distance = std::distance(beg, end);

            if (distance < 2) {
                return;
            }
            if (distance <= PARALLELING_POINT) {
                default_quick(beg, end, comp);
                return;
            }

            using std::swap;

            auto last = std::prev(end);
            swap (*std::next(beg, distance / 2), *last);

            auto bound = std::partition(beg, last, [&](const auto &el) {
                return comp(el, *last);
            });
            swap (*bound, *last);

            if (std::distance(beg, bound) > PARALLELING_POINT) {
                auto func_call_result = std::async(std::launch::async, parallel_quick<Iter, Comp>, beg, bound, comp);
                parallel_quick(std::next(bound), end, comp);
                func_call_result.wait();
            }
            else {
                parallel_quick(beg, bound, comp);
                parallel_quick(std::next(bound), end, comp);
            }
        }
    }


    enum class ExecutionPolicy {Default, Parallel};

    template <typename Iter, typename Comp = std::less<>>
    inline void quick_sort (Iter begin, Iter end, Comp comp = std::less<>{})
    {
        quick_sort(begin, end, ExecutionPolicy::Default, comp);
    }


    template <typename Iter, typename Comp = std::less<>>
    inline void quick_sort (Iter begin,
                            Iter end,
                            ExecutionPolicy policy,
                            Comp comp = std::less<>{})
    {
        if (policy == ExecutionPolicy::Default) {
            detail::default_quick(begin, end, comp);
        }
        else {
            detail::parallel_quick(begin, end, comp);
        }
    }
}