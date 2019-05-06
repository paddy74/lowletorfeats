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
 * @brief Calculate the sum of every value in the `unordered_map`.
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param a
 * @return VALUE_T
 */
template <typename KEY_T, typename VALUE_T>
VALUE_T mapValueSum(std::unordered_map<KEY_T, VALUE_T> const & a)
{
    return std::accumulate(
        a.begin(), a.end(), 0,
        [](const std::size_t previous, auto const & element) {
            return previous + element.second;
        });
}

/**
 * @brief Merge b into a (inplace). The values of matching keys are summed.
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param a
 * @param b
 */
template <typename KEY_T, typename VALUE_T>
void additiveMergeInplace(
    std::unordered_map<KEY_T, VALUE_T> & a,
    std::unordered_map<KEY_T, VALUE_T> const & b)
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
 * @brief Split a string on a delimiter.
 *
 * @param str
 * @param delim
 * @return std::vector<std::string>
 */  // TODO: Fix this weird af workaround that makes zero sense
template <typename T>
std::vector<T> strSplit(T const & str, char const & delim)
{
    std::vector<std::string> tokens;

    // Skip delimiters at the beginning
    std::string::size_type lastPos = str.find_first_not_of(delim, 0);
    // Find first non-delimiter
    std::string::size_type pos = str.find_first_of(delim, lastPos);

    while ((std::string::npos != pos || std::string::npos != lastPos))
        {
            // Found token, add to the token vector
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters
            lastPos = str.find_first_not_of(delim, pos);
            // Find next non-delimiter
            pos = str.find_first_of(delim, lastPos);
        }

    return tokens;
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
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @return std::vector<KEY_T>
 */
template <typename KEY_T, typename VALUE_T>
std::vector<KEY_T> getValueVect(std::unordered_map<KEY_T, VALUE_T> x)
{
    std::vector<KEY_T> outVect;
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
 * @brief Get the intersection of two unorderd_maps
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @param filterMap
 * @return std::unordered_map<KEY_T, VALUE_T>
 */
template <typename KEY_T, typename VALUE_T>
std::unordered_map<KEY_T, VALUE_T> getIntersection(
    std::unordered_map<KEY_T, VALUE_T> const & a,
    std::unordered_map<KEY_T, VALUE_T> const & b)
{
    std::unordered_map<KEY_T, VALUE_T> interMap;

    for (auto const & pair : a)
        {
            if (b.find(pair.first) != b.end()) interMap.insert(pair);
        }

    return interMap;
}

}  // namespace lowletorfeats::utils
