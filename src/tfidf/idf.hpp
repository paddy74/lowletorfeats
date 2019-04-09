#pragma once

#include <cmath>  // log


namespace lowletorfeats::tfidf
{

/**
 * @brief Inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return double
 */
double idfDefault(uint const & numDocs, uint const & numDocsWithTerm)
{
    return log(numDocs / numDocsWithTerm);
}


/**
 * @brief Inverse document frequency smooth
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return double
 */
double idfSmooth(uint const & numDocs, uint const & numDocsWithTerm)
{
    return log(numDocs / (1 + numDocsWithTerm));
}


/**
 * @brief Inverse document frequency max
 *
 * @param numDocsWithTerm
 * @param docMaxTermFrequency
 * @return double
 */
double idfMax(uint const & numDocsWithTerm, uint const & docMaxTermFrequency)
{
    return log((docMaxTermFrequency * numDocsWithTerm)
        / (1 + numDocsWithTerm));
}


/**
 * @brief Probabilistic inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return double
 */
double idfProb(uint const & numDocs, uint const & numDocsWithTerm)
{
    return log((numDocs - numDocsWithTerm) / numDocsWithTerm);
}


/**
 * @brief Normalized inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return double
 */
double idfNorm(uint const & numDocs, uint const & numDocsWithTerm)
{
    uint const numDocsWithoutTerm = numDocs - numDocsWithTerm;
    return log((numDocsWithoutTerm + 0.5) / (numDocsWithTerm + 0.5));
}

}
