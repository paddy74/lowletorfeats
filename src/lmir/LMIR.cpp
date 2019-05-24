#include <cmath>
#include <lowletorfeats/LMIR.hpp>
#include <lowletorfeats/utils.hpp>

namespace lowletorfeats
{
/* Constructors */

LMIR::LMIR() {}

LMIR::LMIR(base::StrUintMap const & corpusTfMap)
{
    std::size_t nTotalTerms = utils::mapValueSum(corpusTfMap);

    for (auto const & mapPair : corpusTfMap)
        this->termProbabilityMap[mapPair.first] = mapPair.second / nTotalTerms;
}

LMIR::LMIR(LMIR const & other)
{
    this->termProbabilityMap = other.termProbabilityMap;
}

/* Public class methods */

base::FValType LMIR::absolute_discount(
    base::StrUintMap const & docTermFreqMap, std::size_t const docLen,
    base::StrUintMap const & queryTermFreqMap) const
{
    std::size_t const nUniqueTerms = docTermFreqMap.size();
    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (docTermFreqMap.count(term) != 0)
        {
            std::size_t const docTermFrequency = docTermFreqMap.at(term);

            long double c = docTermFrequency - delta;
            if (!(c > 0)) c = 0;

            score +=
                log(c / docLen + this->delta * nUniqueTerms / docLen *
                                     this->termProbabilityMap.at(term));
        }
    }

    return score;
}

base::FValType LMIR::dirichlet(
    base::StrUintMap const & docTermFreqMap, std::size_t const docLen,
    base::StrUintMap const & queryTermFreqMap) const
{
    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (docTermFreqMap.count(term) != 0)
        {
            auto const docTermFrequency = docTermFreqMap.at(term);

            score +=
                log((docTermFrequency +
                     this->mu * this->termProbabilityMap.at(term)) /
                    (docLen + this->mu));
        }
    }

    return score;
}

base::FValType LMIR::jelinek_mercer(
    base::StrUintMap const & docTermFreqMap, std::size_t const docLen,
    base::StrUintMap const & queryTermFreqMap) const
{
    auto const docPml = this->calcDocPml(docTermFreqMap, docLen);

    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (docTermFreqMap.count(term) != 0)
        {
            score +=
                log((1 - this->lamb) * docPml.at(term) +
                    this->lamb * this->termProbabilityMap.at(term));
        }
    }

    return score;
}

/* Private class methods */

base::StrDblMap LMIR::calcDocPml(
    base::StrUintMap const & docTermFreqMap, std::size_t const docLen) const
{
    base::StrDblMap pMl;
    for (auto const & mapPair : docTermFreqMap)
        pMl[mapPair.first] = mapPair.second / docLen;

    return pMl;
}

}  // namespace lowletorfeats
