#pragma once

#include <numeric>  // accumulate
#include <algorithm>  // max_element

#include "stdllf.hpp"


namespace lowletorfeats::utillf
{
    /**
     * @brief Calculate the sum of every value in the `unordered_map`.
     *
     * @tparam KEY_T
     * @tparam VALUE_T
     * @param a
     * @return VALUE_T
     */
    template<typename KEY_T, typename VALUE_T>
    VALUE_T mapValueSum(std::unordered_map<KEY_T, VALUE_T> const & a)
    {
        return std::accumulate(
            a.begin(),
            a.end(),
            0,
            [] (const std::size_t previous, auto const & element)
                { return previous + element.second; }
        );
    }


    /**
     * @brief Merge b into a (inplace). The values of matching keys are summed.
     *
     * @tparam KEY_T
     * @tparam VALUE_T
     * @param a
     * @param b
     */
    template<typename KEY_T, typename VALUE_T>
    void additiveMergeInplace(
        std::unordered_map<KEY_T, VALUE_T> & a,
        std::unordered_map<KEY_T, VALUE_T> const & b
    )
    {
        for (auto const & [key, value] : b)
            a[key] += value;
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
    template<typename KEY_T, typename VALUE_T>
    std::pair<KEY_T, VALUE_T> findMaxValuePair(
        std::unordered_map<KEY_T, VALUE_T> const & x
    )
    {
        using pairtype=std::pair<KEY_T, VALUE_T>;

        return *std::max_element(
            x.begin(),
            x.end(),
            [] (const pairtype & p1, const pairtype & p2)
            {
                return p1.second < p2.second;
            }
        );
    }


    /**
     * @brief Split a string on a delimiter. TODO: Better performance (vector bad)
     *
     * @param str
     * @param delim
     * @return std::vector<std::string>
     */
    std::vector<std::string> strSplit(std::string const & str, char const & delim)
    {
        std::vector<std::string> out;

        size_t start;
        size_t end = 0;

        while ( (start = str.find_first_not_of(delim, end)) != std::string::npos)
        {
            end = str.find(delim, start);
            out.push_back(str.substr(start, end - start));
        }
    }


    /**
     * @brief Get a vector of the map's keys
     *
     * @tparam KEY_T
     * @tparam VALUE_T
     * @param x
     * @return std::vector<KEY_T>
     */
    template<typename KEY_T, typename VALUE_T>
    std::vector<KEY_T> getKeyVect(std::unordered_map<KEY_T, VALUE_T> x)
    {
        std::vector<KEY_T> outVect;
        outVect.reserve(x.size());

        for (auto const & imap : x)
        {
            outVect.push_back(imap.first);
        }
    }


    /**
     * @brief Get a vector of the map's values
     *
     * @tparam KEY_T
     * @tparam VALUE_T
     * @param x
     * @return std::vector<KEY_T>
     */
    template<typename KEY_T, typename VALUE_T>
    std::vector<KEY_T> getValueVect(std::unordered_map<KEY_T, VALUE_T> x)
    {
        std::vector<KEY_T> outVect;
        outVect.reserve(x.size());

        for (auto const & imap : x)
        {
            outVect.push_back(imap.second);
        }
    }
}
