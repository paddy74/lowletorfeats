#pragma once

#include <algorithm>  // max_element
#include <map>
#include <numeric>  // accumulate
#include <unordered_map>
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
 * @brief Find the maximum key-value pair in an `unorderd_map`.
 *  Based on: https://stackoverflow.com/a/34937216/7706917
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @return std::pair<KEY_T, VALUE_T>
 */
template <typename KEY_T, typename VALUE_T>
std::pair<KEY_T, VALUE_T> findMaxValuePair(
    std::unordered_map<KEY_T, VALUE_T> const & x)
{
    using pairtype = std::pair<KEY_T, VALUE_T>;

    return *std::max_element(
        x.begin(), x.end(), [](const pairtype & p1, const pairtype & p2) {
            return p1.second < p2.second;
        });
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
template <typename KEY_T, typename VALUE_T>
std::vector<KEY_T> getKeyVect(std::unordered_map<KEY_T, VALUE_T> x)
{
    std::vector<KEY_T> outVect;
    outVect.reserve(x.size());

    for (auto const & imap : x) outVect.push_back(imap.first);

    return outVect;
}

/**
 * @brief Get a vector of the map's keys
 *
 * @tparam KEY_T
 * @tparam VALUE_T
 * @param x
 * @return std::vector<KEY_T>
 */
template <typename KEY_T, typename VALUE_T>
std::vector<KEY_T> getKeyVect(std::map<KEY_T, VALUE_T> x)
{
    std::vector<KEY_T> outVect;
    outVect.reserve(x.size());

    for (auto const & imap : x) outVect.push_back(imap.first);

    return outVect;
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
