#pragma once

#include <map>
#include <vector>


namespace lowletorfeats::base
{
    typedef std::map<std::string, uint> TermFrequencyMap;  // Map of term frequency
    typedef std::map<std::string, double> DocFeatureMap;  // Features for a given document
}
