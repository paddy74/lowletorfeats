#pragma once

#include <unordered_map>  // unordered_map

#include "FeatureKey.hpp"


namespace lowletorfeats::base
{
    typedef std::unordered_map<std::string, uint> StrUintMap;
    typedef std::unordered_map<std::string, std::string> StrStrMap;
    typedef std::unordered_map<std::string, base::StrUintMap>
        StructuredTermFrequencyMap;

    typedef std::unordered_map<FeatureKey, double> FeatureMap;
}
