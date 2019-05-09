#include <cmath>  // log
#include <lowletorfeats/Tfidf.hpp>

namespace lowletorfeats
{
/**
 * @brief Inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfDefault(
    uint const & numDocs, uint const & numDocsWithTerm)
{
    return log((base::FValType)numDocs / (base::FValType)numDocsWithTerm);
}

/**
 * @brief Inverse document frequency smooth
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfSmooth(
    uint const & numDocs, uint const & numDocsWithTerm)
{
    return log(
        (base::FValType)numDocs / (base::FValType)(1 + numDocsWithTerm));
}

/**
 * @brief Inverse document frequency max
 *
 * @param numDocsWithTerm
 * @param docMaxTermFrequency
 * @return base::FValType
 */
base::FValType Tfidf::idfMax(
    uint const & numDocsWithTerm, uint const & docMaxTermFrequency)
{
    return log(
        ((base::FValType)docMaxTermFrequency *
         (base::FValType)numDocsWithTerm) /
        (base::FValType)(1 + numDocsWithTerm));
}

/**
 * @brief Probabilistic inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfProb(
    uint const & numDocs, uint const & numDocsWithTerm)
{
    return log(
        ((base::FValType)numDocs - (base::FValType)numDocsWithTerm) /
        (base::FValType)numDocsWithTerm);
}

/**
 * @brief Normalized inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfNorm(
    uint const & numDocs, uint const & numDocsWithTerm)
{
    base::FValType const numDocsWithoutTerm = numDocs - numDocsWithTerm;
    return log(
        (numDocsWithoutTerm + 0.5) / ((base::FValType)numDocsWithTerm + 0.5));
}

}  // namespace lowletorfeats
