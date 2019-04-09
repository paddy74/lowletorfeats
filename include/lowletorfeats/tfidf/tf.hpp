#pragma once

#include <cmath>  // log


namespace lowletorfeats::tfidf
{

/**
 * @brief Log normalized term frequency.
 *
 * @param docTermFrequency The term's frequency.
 * @return double
 */
double tfLogNorm(uint const & docTermFrequency)
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
double tfDoubleNorm(
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
double tfDoubleNorm(
    uint const & docTermFrequency, uint const & docMaxTermFrequency)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency, 0.5);
}

}
