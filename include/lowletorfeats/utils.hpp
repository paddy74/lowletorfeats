#pragma once

#include <algorithm>  // max_element
#include <map>
#include <numeric>  // accumulate
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace lowletorfeats::utils
{
/**
 * @brief Calculate the sum of every value in the `unordered_map` or `map`.
 *
 * @tparam Container
 * @param x
 * @return Container::mapped_type
 */
template <class Container>
auto mapValueSum(Container const & x) -> typename Container::mapped_type
{
    return std::accumulate(
        x.begin(), x.end(), 0,
        [](const std::size_t previous, auto const & element) {
            return previous + element.second;
        });
}

/**
 * @brief Merge b into a (inplace). The values of matching keys are summed.
 *
 * @tparam Container
 * @param a
 * @param b
 */
template <class Container>
void additiveMergeInplace(Container & a, Container const & b)
{
    for (auto const & [key, value] : b) a[key] += value;
}

/**
 * @brief Find the maximum key-value pair in std::pair value_type container.
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @return std::pair<KEY_T, VALUE_T>
 */
template <class Container>
auto findMaxValuePair(Container const & x) -> typename Container::value_type
{
    using value_t = typename Container::value_type;

    if (x.size() == 0) return value_t();
    if (x.size() == 1) return *x.begin();

    const auto compare = [](value_t const & p1, value_t const & p2) {
        return p1.second < p2.second;
    };
    return *std::max_element(x.begin(), x.end(), compare);
}

/**
 * @brief Get a vector of the map's keys
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @return std::vector<KEY_T>
 */
template <class Container>
auto getKeyVect(Container const & x)
    -> std::vector<typename Container::key_type>
{
    using key_t = typename Container::key_type;

    std::vector<key_t> outVect;
    outVect.reserve(x.size());

    for (auto const & imap : x) outVect.push_back(imap.first);

    return outVect;
}

/**
 * @brief Get an `unordered_set` of the map's keys.
 *
 * @tparam Container
 * @param x
 * @return std::unordered_set<typename Container::key_type>
 */
template <class Container>
auto getKeyUnorderedSet(Container const & x)
    -> std::unordered_set<typename Container::key_type>
{
    using key_t = typename Container::key_type;

    std::unordered_set<key_t> outSet;
    outSet.reserve(x.size());

    for (auto const & imap : x) outSet.insert(imap.first);

    return outSet;
}

/**
 * @brief Get a vector of the map's values
 *
 * @tparam Container A `std::unordered_map` or `std::map`
 * @param x The map
 * @return std::vector<typename Container::mapped_type> Vector of map values
 */
template <class Container>
std::vector<typename Container::mapped_type> getValueVect(Container const & x)
{
    using mapped_t = typename Container::mapped_type;

    std::vector<mapped_t> outVect;
    outVect.reserve(x.size());

    for (auto const & imap : x) outVect.push_back(imap.second);

    return outVect;
}

/**
 * @brief Get the intersecting terms of two vectors
 *
 * @tparam T
 * @param a
 * @param b
 * @return std::list<T>
 */
template <typename T>
std::vector<T> getIntersection(
    std::vector<T> const & a, std::vector<T> const & b)
{
    std::vector<T> interLst;

    std::set_intersection(
        a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(interLst));

    return interLst;
}

/**
 * @brief Get the intersection of two maps.
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @param filterMap
 * @return std::unordered_map<KEY_T, VALUE_T>
 */
template <class Container>
Container getIntersection(Container const & a, Container const & b)
{
    Container interMap;

    for (auto const & pair : a)
    {
        if (b.find(pair.first) != b.end()) interMap.insert(pair);
    }

    return interMap;
}

}  // namespace lowletorfeats::utils
