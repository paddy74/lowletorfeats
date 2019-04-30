#pragma once

#include <lowletorfeats/base/FeatureKey.hpp>

#include <unordered_map>  // unordered_map


namespace lowletorfeats::base
{
    typedef long double FValType;
    typedef float WeightType;

    typedef std::unordered_map<std::string, std::size_t> StrUintMap;
    typedef std::unordered_map<std::string, std::string> StrStrMap;
    typedef std::unordered_map<std::string, base::StrUintMap>
        StructuredTermFrequencyMap;

    typedef std::unordered_map<FeatureKey, FValType> FeatureMap;
}