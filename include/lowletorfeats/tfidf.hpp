#pragma once

#include <cassert>

#include "base/llfstd.hpp"
#include "tf.hpp"
#include "idf.hpp"


namespace lowletorfeats
{

double tfidf(
    uint const & docTermFrequency, uint const & docMaxTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm
)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency)
        * idfNorm(numDocs, numDocsWithTerm);
}


/**
 * @brief Calculate tf-idf with the given functions
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @param docTermFrequency
 * @return double
 */
double tfidf(
    double (*tfFunction)(uint const &),
    double (*idfFunction)(uint const &, uint const &),
    uint const & docTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm
)
{
    return (*tfFunction)(docTermFrequency)
        * (*idfFunction)(numDocs, numDocsWithTerm);
}


/**
 * @brief Calculate tf-idf with the given functions
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @param docTermFrequency
 * @return double
 */
/**double tfidf(
    double (*tfFunction)(uint, uint),
    double (*idfFunction)(uint, uint),
    uint docTermFrequency, docMaxTermFrequency,
    uint numDocs, uint numDocsWithTerm
)
{
    return (*tfFunction)(docTermFrequency, docMaxTermFrequency)
        * (*idfFunction)(numDocs, numDocsWithTerm);
}*/


/**
 * @brief Calculate the TF-IDF of a document for a group of terms.
 *  To calculate the TF-IDF for an entire document (no query) the
 *  `queryTermFreqMap` should be the document's token vector.
 *
 * @param docTermFreqMap `TermFrequencyMap` for the document.
 * @param docMaxTermFrequency Number of times the document's maximum occuring
 *  term appears in the document.
 * @param numDocs Number of documents in the collection.
 * @param docsWithTermFreqMap Number of documents containing each term.
 * @param queryTermFreqMap `TermFrequencyMap` for the query.
 * @return double
 */
double queryTfidf(
    base::TermFrequencyMap const & docTermFreqMap, uint const & docMaxTermFrequency,
    uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
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

            score += tfidf(
                docTermFrequency, docMaxTermFrequency,
                numDocs, numDocsWithTerm);
        }
        catch (std::out_of_range const & e)
        {
            continue;  // score += 0
        }
    }
}

}
