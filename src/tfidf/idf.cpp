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
    std::size_t const & numDocs, std::size_t const & numDocsWithTerm)
{
    return log(
        static_cast<base::FValType>(numDocs) /
        static_cast<base::FValType>(numDocsWithTerm));
}

/**
 * @brief Inverse document frequency smooth
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfSmooth(
    std::size_t const & numDocs, std::size_t const & numDocsWithTerm)
{
    return log(
        static_cast<base::FValType>(numDocs) /
        static_cast<base::FValType>(1 + numDocsWithTerm));
}

/**
 * @brief Inverse document frequency max
 *
 * @param numDocsWithTerm
 * @param docMaxTermFrequency
 * @return base::FValType
 */
base::FValType Tfidf::idfMax(
    std::size_t const & numDocsWithTerm,
    std::size_t const & docMaxTermFrequency)
{
    return log(
        (static_cast<base::FValType>(docMaxTermFrequency) *
         static_cast<base::FValType>(numDocsWithTerm)) /
        static_cast<base::FValType>(1 + numDocsWithTerm));
}

/**
 * @brief Probabilistic inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfProb(
    std::size_t const & numDocs, std::size_t const & numDocsWithTerm)
{
    return log(
        static_cast<base::FValType>(numDocs - numDocsWithTerm) /
        static_cast<base::FValType>(numDocsWithTerm));
}

/**
 * @brief Normalized inverse document frequency
 *
 * @param numDocs
 * @param numDocsWithTerm
 * @return base::FValType
 */
base::FValType Tfidf::idfNorm(
    std::size_t const & numDocs, std::size_t const & numDocsWithTerm)
{
    base::FValType const numDocsWithoutTerm =
        static_cast<base::FValType>(numDocs - numDocsWithTerm);

    return log(
        (numDocsWithoutTerm + 0.5) /
        (static_cast<base::FValType>(numDocsWithTerm) + 0.5));
}

}  // namespace lowletorfeats
