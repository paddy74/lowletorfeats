#pragma once

#include <cassert>

#include "base/stdllf.hpp"
#include "idf.hpp"


namespace lowletorfeats
{

double bm25plus(
    uint const & docTermFrequency,
    uint const & numDocs, uint numDocsWithTerm,
    uint const & avgDocLen,
    float const & b, float const & k1, float const & delta
)
{
    double const idf = idfNorm(numDocs, numDocsWithTerm);

    double const numer = docTermFrequency * (k1 + 1);
    double const denom = docTermFrequency
        + (k1 * (1 - b + (b * (numDocs / avgDocLen))));

    return idf * ((numer / denom) + delta);
}


double bm25plus(
    uint const & docTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm,
    uint const & avgDocLen
)
{
    float const k1 = 1.2;
    float const b = 0.74;
    float const delta = 1.0;

    return bm25plus(
        docTermFrequency,
        numDocs, numDocsWithTerm,
        avgDocLen,
        b, k1, delta
    );
}


double queryBm25plus(
    base::TermFrequencyMap const & docTermFreqMap,
    uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
    uint const & avgDocLen,
    base::TermFrequencyMap const & queryTermFreqMap
)
{
    assert(queryTermFreqMap.size() == docsWithTermFreqMap.size());

    double score = 0;
    for (auto const & [term, tf] : queryTermFreqMap)
    {
        try
        {
            uint const docTermFrequency = docTermFreqMap.at(term);
            uint const numDocsWithTerm = docsWithTermFreqMap.at(term);

            score += bm25plus(
                docTermFrequency,
                numDocs, numDocsWithTerm,
                avgDocLen
            );
        }
        catch (std::out_of_range const & e)
        {
            continue;  // score += 0
        }
    }
}

}
