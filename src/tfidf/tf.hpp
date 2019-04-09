#pragma once

#include <cmath>  // log

#include <lowletorfeats/Tfidf.hpp>

namespace lowletorfeats
{

/**
 * @brief Log normalized term frequency.
 *
 * @param docTermFrequency The term's frequency.
 * @return double
 */
double Tfidf::tfLogNorm(uint const & docTermFrequency)
{
    return log(1 + docTermFrequency);
}


/**
 * @brief Double normalization term frequency.
 *  Prevents a bias towards longer documents.
 *
 * @param docTermFrequency The term's frequency.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @param k
 * @return double
 */
double Tfidf::tfDoubleNorm(
    uint const & docTermFrequency, uint const & docMaxTermFrequency,
    float const & k)
{
    return k + ((1 - k)
        * (docTermFrequency / (docMaxTermFrequency + docTermFrequency)));
}


/**
 * @brief Double normalization term frequency (k = 0.5).
 *  Prevents a bias towards longer documents.
 *
 * @param docTermFrequency The term's frequency.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @return double
 */
double Tfidf::tfDoubleNorm(
    uint const & docTermFrequency, uint const & docMaxTermFrequency)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency, 0.5);
}


double Tfidf::queryTfLogNorm(base::TermFrequencyMap const & docTermFreqMap)
{
    double score = 0;
    for (auto const & [term, tf] : docTermFreqMap)
        score += tfLogNorm(tf);
    return score;
}


double Tfidf::queryTfDoubleNorm(
    base::TermFrequencyMap const & docTermFreqMap,
    uint const & docMaxTermFrequency
)
{
    double score = 0;
    for (auto const & [term, tf] : docTermFreqMap)
        score += tfDoubleNorm(tf, docMaxTermFrequency);
    return score;
}

}
