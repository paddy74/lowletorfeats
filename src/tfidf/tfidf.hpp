#pragma once

#include <cassert>

#include <lowletorfeats/Tfidf.hpp>
#include "lowletorfeats/base/stdllf.hpp"
#include "tf.hpp"
#include "idf.hpp"


namespace lowletorfeats
{

/**
 * @brief Calculate Term Frequency / Inverse Document Frequency (TF/IDF) for
 *  a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
double Tfidf::tfidf(
    uint const & docTermFrequency, uint const & docMaxTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm
)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency)
        * idfNorm(numDocs, numDocsWithTerm);
}


/**
 * @brief Calculate TF/IDF with the given TF and IDF versions for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
double Tfidf::tfidf(
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
 * @brief Calculate TF/IDF with the given TF and IDF versions for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
double Tfidf::tfidf(
    double (*tfFunction)(uint, uint),
    double (*idfFunction)(uint, uint),
    uint const & docTermFrequency, uint const & docMaxTermFrequency,
    uint const & numDocs, uint const & numDocsWithTerm
)
{
    return (*tfFunction)(docTermFrequency, docMaxTermFrequency)
        * (*idfFunction)(numDocs, numDocsWithTerm);
}


/**
 * @brief Calculate the TF-IDF of a document for a group of terms (query).
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
double Tfidf::queryTfidf(
    base::TermFrequencyMap const & docTermFreqMap, uint const & docMaxTermFrequency,
    uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
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

            score += tfidf(
                docTermFrequency, docMaxTermFrequency,
                numDocs, numDocsWithTerm);
        }
        catch (std::out_of_range const & e)
        {
            continue;  // score += 0
        }
    }

    return score;
}

}
