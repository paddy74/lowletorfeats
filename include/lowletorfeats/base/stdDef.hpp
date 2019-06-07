#pragma once

#include <tsl/ordered_map.h>

#include <lowletorfeats/base/FeatureKey.hpp>
#include <unordered_map>  // unordered_map

namespace lowletorfeats::base
{
typedef long double FValType;  // Feature value type
typedef float WeightType;      // Section weight type

typedef std::unordered_map<std::string, double>
    StrDblMap;  // String to double map
typedef std::unordered_map<std::string, std::size_t>
    StrUintMap;  // String to size map
typedef std::unordered_map<std::string, std::string>
    StrStrMap;  // String to string map
typedef std::unordered_map<std::string, base::StrUintMap>
    StructuredTermFrequencyMap;  // String to string-size map

typedef tsl::ordered_map<FeatureKey, FValType> FeatureMap;  // FKey to FVal map

}  // namespace lowletorfeats::base
