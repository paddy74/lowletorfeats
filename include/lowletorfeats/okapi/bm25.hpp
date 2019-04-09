#pragma once

#include <cassert>

#include "lowletorfeats/base/stdllf.hpp"
#include "lowletorfeats/tfidf/idf.hpp"


namespace lowletorfeats::okapi
{

/**
 * @brief Calculate Okapi Best Match 25 (BM25) for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @param avgDocLen Average document length of the collection.
 * @param b
 * @param k1
 * @return double
 */
double bm25(
    uint const & docTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm,
    uint const & avgDocLen,
    float const & b, float const & k1
)
{
    double const idf = tfidf::idfNorm(numDocs, numDocsWithTerm);

    double const numer = docTermFrequency * (k1 + 1);
    double const denom = docTermFrequency
        + (k1 * (1 - b + (b * (numDocs / avgDocLen))));

    return idf * (numer / denom);
}


/**
 * @brief Calculate Okapi Best Match 25 (BM25) for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @param avgDocLen Average document length of the collection.
 * @return double
 */
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


/**
 * @brief Calculate the BM25 of a document for a group of terms (query).
 *  To calculate the BM25 for an entire document (no query) the
 *  `queryTermFreqMap` should be the document's token vector.
 *
 * @param docTermFreqMap `TermFrequencyMap` for the document.
 * @param numDocs Number of documents in the collection.
 * @param docsWithTermFreqMap Number of documents containing each term.
 * @param avgDocLen Average document length of the collection.
 * @param queryTermFreqMap `TermFrequencyMap` for the query.
 * @return double
 */
double queryBm25(
    base::TermFrequencyMap const & docTermFreqMap,
    uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
    uint const & avgDocLen,
    base::TermFrequencyMap const & queryTermFreqMap
)
{
    // Ensure the number of terms is the same
    assert(queryTermFreqMap.size() == docsWithTermFreqMap.size());

    // Sum the scores for each term
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

    return score;
}

}
