#pragma once

#include <cassert>

#include "base/llfstd.hpp"
#include "idf.hpp"


namespace lowletorfeats
{

double bm25(
    uint const & docTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm,
    uint const & avgDocLen,
    float const & b, float const & k1
)
{
    double const idf = idfNorm(numDocs, numDocsWithTerm);

    double const numer = docTermFrequency * (k1 + 1);
    double const denom = docTermFrequency
        + (k1 * (1 - b + (b * (numDocs / avgDocLen))));

    return idf * (numer / denom);
}


double bm25(
    uint const & docTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm,
    uint const & avgDocLen
)
{
    float const k1 = 1.2;
    float const b = 0.74;

    return bm25(
        docTermFrequency,
        numDocs, numDocsWithTerm,
        avgDocLen,
        b, k1
    );
}


double queryBm25(
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

            score += bm25(
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
