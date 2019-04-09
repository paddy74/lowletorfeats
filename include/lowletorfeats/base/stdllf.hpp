#pragma once

#include <map>
#include <unordered_map>
#include <vector>


namespace lowletorfeats::base
{
    typedef std::unordered_map<std::string, uint> TermFrequencyMap;  // Map of term frequency
    typedef std::unordered_map<std::string, double> DocFeatureMap;  // Features for a given document

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
}
