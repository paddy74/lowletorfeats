#pragma once

#include "stdllf.hpp"


namespace lowletorfeats::base
{
    template<typename KEY_T, typename VAL_T>
    VAL_T mapValueSum(std::unordered_map<KEY_T, VAL_T> const & a)
    {
        return std::accumulate(
            a.begin(),
            a.end(),
            0,
            [](const std::size_t previous, auto const & element)
                { return previous + element.second; }
        );
    }
}
