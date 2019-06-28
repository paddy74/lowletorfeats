#pragma once

#include <lowletorfeats/base/stdDef.hpp>
#include <vector>

namespace lowletorfeats
{
/**
 * @brief Class for calculate LMIR scores.
 *
 */
class LMIR
{
public:
    /* Public member variables */
    /***************************/

    float lamb = 0.1f;
    ushort mu = 2000;
    float delta = 0.7f;

    /* Constructors */
    /****************/

    /**
     * @brief Empty constructor for new LMIR object.
     *
     */
    LMIR();

    /**
     * @brief Default constructor for a new LMIR object.
     *
     * @param totalTermsMap
     */
    LMIR(base::StrSizeMap const & corpusTfMap);

    /**
     * @brief Copy constructor for a new LMIR object.
     *
     * @param other
     */
    LMIR(LMIR const & other);

    /* Public class methods */
    /************************/

    /**
     * @brief Calculate the absolute cumulative discount score.
     *
     */
    base::FValType absolute_discount(
        base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
        base::StrSizeMap const & queryTermFreqMap) const;

    /**
     * @brief Calculate the Dirichlet score.
     *
     */
    base::FValType dirichlet(
        base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
        base::StrSizeMap const & queryTermFreqMap) const;

    /**
     * @brief Calculate the Jelinek-Mercer Score
     *
     * @param docTermFreqMap
     * @param docLen
     * @param queryTermFreqMap
     * @return base::FValType
     */
    base::FValType jelinek_mercer(
        base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
        base::StrSizeMap const & queryTermFreqMap) const;

private:
    /* Private member variables */
    /****************************/

    base::StrDblMap termProbabilityMap;  // corpus wide term probability

    /* Private class methods */
    /*************************/

    /**
     * @brief Calculate the PML score for each term in the document.
     *
     * @param docTermFreqMap The document's term frequency map.
     * @param docLen The length of the document.
     * @return base::StrDblMap The calculated pMl for each term.
     */
    base::StrDblMap calcDocPml(
        base::StrSizeMap const & docTermFreqMap,
        std::size_t const docLen) const;
};

}  // namespace lowletorfeats
