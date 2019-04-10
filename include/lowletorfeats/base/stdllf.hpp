#pragma once

#include <map>
#include <unordered_map>
#include <vector>


namespace lowletorfeats::base
{
    typedef enum FeatureNames
    {
        // Document length
        dl,

        // TF
        tflognorm,
        tfdoublenorm,
        // IDF
        idfdefault,
        idfsmooth,
        idfmax,
        idfprob,
        idfnorm,
        // TF/IDF
        tfidf,

        // Okapi
        bm25,
        bm25plus,

        // LMIR
        abs,
        dir,
        jm
    } FeatureNames;

    typedef std::unordered_map<std::string, uint> StrUintMap;
    typedef std::unordered_map<std::string, std::string> StrStrMap;
    typedef std::unordered_map<std::string, base::StrUintMap>
        StructuredTermFrequencyMap;
    typedef std::unordered_map<FeatureNames, double> DocFeatureMap;
}
