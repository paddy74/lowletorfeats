#pragma once

#include <unordered_map>  // unordered_map

#include "FeatureKey.hpp"


namespace lowletorfeats::base
{
    typedef std::unordered_map<std::string, std::size_t> StrUintMap;
    typedef std::unordered_map<std::string, std::string> StrStrMap;
    typedef std::unordered_map<std::string, base::StrUintMap>
        StructuredTermFrequencyMap;

    typedef long double FValType;
    typedef float WeightType;
    typedef std::unordered_map<FeatureKey, FValType> FeatureMap;
}
