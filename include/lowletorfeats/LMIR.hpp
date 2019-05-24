#pragma once

#include <lowletorfeats/base/stdDef.hpp>
#include <vector>

namespace lowletorfeats
{
class LMIR
{
public:
    /* Public member variables */

    float lamb = 0.1;
    ushort mu = 2000;
    float delta = 0.7;

    /* Constructors */

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
    LMIR(base::StrUintMap const & totalTermsMap);

    /**
     * @brief Copy constructor for a new LMIR object.
     *
     * @param other
     */
    LMIR(LMIR const & other);

    /* Public class methods */

    base::FValType absolute_discount(
        base::StrUintMap const & docTermFreqMap, std::size_t const docLen,
        base::StrUintMap const & queryTermFreqMap);
    base::FValType dirichlet();
    base::FValType jelinek_mercer();

private:
    /* Private member variables */

    base::StrDblMap pCorpusMap;  // corpus wide

    /* Private class methods */

    base::StrDblMap calcDocPml(
        base::StrUintMap const & docTermFreqMap,
        std::size_t const docLen) const;
};

}  // namespace lowletorfeats
