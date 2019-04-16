#pragma once

#include <lowletorfeats/Okapi.hpp>
#include "bm25.hpp"
#include "bm25plus.hpp"


namespace lowletorfeats
{

/**
 * @brief Calculate the BM25f score.
 *
 * @param structDocTermFreqMap
 * @param numDocs
 * @param structDocsWithTermFreqMap
 * @param avgDocLen
 * @param queryTermFreqMap
 * @param structWeights
 * @return double
 */
double Okapi::queryBm25f(
    std::unordered_map<std::string, base::StrUintMap>
        const & structDocTermFreqMap,
    uint const & numDocs,
    std::unordered_map<std::string, base::StrUintMap>
        structDocsWithTermFreqMap,
    base::StrUintMap const & avgDocLenMap,
    base::StrUintMap const & queryTermFreqMap,
    std::unordered_map<std::string, double> structWeights
)
{
    // Calculate full idf
    double const fullIdf = 0;

    // Calculate BM25 for each field
    double totalBm25 = 0;
    for (auto const & [sectionKey, tfMap] : structDocTermFreqMap)
    {
        auto const & docsWithTermFreqMap =
            structDocsWithTermFreqMap.at(sectionKey);
        auto const & weight = structWeights.at(sectionKey);
        auto const & avgDocLen = avgDocLenMap.at(sectionKey);

        double bm25 = Okapi::queryBm25(
            tfMap, numDocs, docsWithTermFreqMap, avgDocLen, queryTermFreqMap
        );
        bm25 *= weight;

        totalBm25 += bm25;
    }

    // Calculate BM25f
    return fullIdf * totalBm25;
}


/**
 * @brief Calculate the BM25f+ score.
 *
 * @param structDocTermFreqMap
 * @param numDocs
 * @param structDocsWithTermFreqMap
 * @param avgDocLen
 * @param queryTermFreqMap
 * @param structWeights
 * @return double
 */
double Okapi::queryBm25fplus(
    std::unordered_map<std::string, base::StrUintMap>
        const & structDocTermFreqMap,
    uint const & numDocs,
    std::unordered_map<std::string, base::StrUintMap>
        structDocsWithTermFreqMap,
    base::StrUintMap const & avgDocLenMap,
    base::StrUintMap const & queryTermFreqMap,
    std::unordered_map<std::string, double> structWeights
)
{
    // Calculate full idf
    double fullIdf = 0;
    for (auto const & [term, tf] : structDocsWithTermFreqMap["full"])
        fullIdf += Tfidf::idfNorm(numDocs, tf);

    // Calculate BM25 for each field
    double totalBm25plus = 0;
    for (auto const & [sectionKey, tfMap] : structDocTermFreqMap)
    {
        auto const & docsWithTermFreqMap =
            structDocsWithTermFreqMap.at(sectionKey);
        auto const & weight = structWeights.at(sectionKey);
        auto const & avgDocLen = avgDocLenMap.at(sectionKey);

        double bm25plus = Okapi::queryBm25plus(
            tfMap, numDocs, docsWithTermFreqMap, avgDocLen, queryTermFreqMap
        );
        bm25plus *= weight;

        totalBm25plus += bm25plus;
    }

    // Calculate BM25f
    return fullIdf * totalBm25plus;
}

}
