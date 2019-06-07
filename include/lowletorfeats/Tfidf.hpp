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
    static base::FValType tfLogNorm(uint const & docTermFrequency);

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
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        float const & k);

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
        uint const & docTermFrequency, uint const & docMaxTermFrequency);

    /**
     * @brief Return the sum of tfLogNorm for a document.
     *
     */
    static base::FValType sumTfLogNorm(
        base::StrUintMap const & docTermFreqMap);

    /**
     * @brief Return the sum of tfDoubleNorm for a document.
     *
     */
    static base::FValType sumTfDoubleNorm(
        base::StrUintMap const & docTermFreqMap,
        uint const & docMaxTermFrequency);

    /* Inverse document frequency */
    /******************************/
    base::FValType static idfDefault(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfSmooth(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfMax(
        uint const & numDocsWithTerm, uint const & docMaxTermFrequency);
    base::FValType static idfProb(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfNorm(
        uint const & numDocs, uint const & numDocsWithTerm);

    /* TF/IDF */
    /**********/
    base::FValType static tfidf(
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(uint const &),
        base::FValType (*idfFunction)(uint const &, uint const &),
        uint const & docTermFrequency, uint const & numDocs,
        uint const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(uint, uint),
        base::FValType (*idfFunction)(uint, uint),
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static queryTfidf(
        base::StrUintMap const & docTermFreqMap,
        uint const & docMaxTermFrequency, uint const & numDocs,
        base::StrUintMap const & docsWithTermFreqMap,
        base::StrUintMap const & queryTermFreqMap);

private:
    Tfidf() {}
};

}  // namespace lowletorfeats
