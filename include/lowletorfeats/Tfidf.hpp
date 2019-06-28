#pragma once

#include <lowletorfeats/base/stdDef.hpp>

namespace lowletorfeats
{
/**
 * @brief Static class for claculating TF/IDF related scores.
 *
 */
class Tfidf
{
public:
    /* Term frequency */
    /******************/

    /**
     * @brief Log normalized term frequency.
     *
     * @param docTermFrequency The term's frequency.
     * @return base::FValType
     */
    static base::FValType tfLogNorm(std::size_t const & docTermFrequency);

    /**
     * @brief Double normalization term frequency.
     *  Prevents a bias towards longer documents.
     *
     * @param docTermFrequency The term's frequency.
     * @param docMaxTermFrequency Frequency of the document's maximum occuring
     * term.
     * @param k
     * @return base::FValType
     */
    static base::FValType tfDoubleNorm(
        std::size_t const & docTermFrequency,
        std::size_t const & docMaxTermFrequency, float const & k);

    /**
     * @brief Double normalization term frequency (k = 0.5).
     *  Prevents a bias towards longer documents.
     *
     * @param docTermFrequency The term's frequency.
     * @param docMaxTermFrequency Frequency of the document's maximum occuring
     * term.
     * @return base::FValType
     */
    static base::FValType tfDoubleNorm(
        std::size_t const & docTermFrequency,
        std::size_t const & docMaxTermFrequency);

    /**
     * @brief Return the sum of tfLogNorm for a document.
     *
     */
    static base::FValType sumTfLogNorm(
        base::StrSizeMap const & docTermFreqMap);

    /**
     * @brief Return the sum of tfDoubleNorm for a document.
     *
     */
    static base::FValType sumTfDoubleNorm(
        base::StrSizeMap const & docTermFreqMap,
        std::size_t const & docMaxTermFrequency);

    /* Inverse document frequency */
    /******************************/
    base::FValType static idfDefault(
        std::size_t const & numDocs, std::size_t const & numDocsWithTerm);
    base::FValType static idfSmooth(
        std::size_t const & numDocs, std::size_t const & numDocsWithTerm);
    base::FValType static idfMax(
        std::size_t const & numDocsWithTerm,
        std::size_t const & docMaxTermFrequency);
    base::FValType static idfProb(
        std::size_t const & numDocs, std::size_t const & numDocsWithTerm);
    base::FValType static idfNorm(
        std::size_t const & numDocs, std::size_t const & numDocsWithTerm);

    /* TF/IDF */
    /**********/
    base::FValType static tfidf(
        std::size_t const & docTermFrequency,
        std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(std::size_t const &),
        base::FValType (*idfFunction)(
            std::size_t const &, std::size_t const &),
        std::size_t const & docTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(std::size_t const &, std::size_t const &),
        base::FValType (*idfFunction)(
            std::size_t const &, std::size_t const &),
        std::size_t const & docTermFrequency,
        std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm);
    base::FValType static queryTfidf(
        base::StrSizeMap const & docTermFreqMap,
        std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
        base::StrSizeMap const & docsWithTermFreqMap,
        base::StrSizeMap const & queryTermFreqMap);

private:
    Tfidf() {}
};

}  // namespace lowletorfeats
