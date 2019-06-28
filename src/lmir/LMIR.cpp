#include <cmath>
#include <lowletorfeats/LMIR.hpp>
#include <lowletorfeats/utils.hpp>

namespace lowletorfeats
{
/* Constructors */

LMIR::LMIR() {}

LMIR::LMIR(base::StrSizeMap const & corpusTfMap)
{
    std::size_t nTotalTerms = utils::mapValueSum(corpusTfMap);

    for (auto const & mapPair : corpusTfMap)
        this->termProbabilityMap[mapPair.first] =
            static_cast<double>(mapPair.second) /
            static_cast<double>(nTotalTerms);
}

LMIR::LMIR(LMIR const & other)
{
    this->termProbabilityMap = other.termProbabilityMap;
}

/* Public class methods */

base::FValType LMIR::absolute_discount(
    base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
    base::StrSizeMap const & queryTermFreqMap) const
{
    std::size_t const nUniqueTerms = docTermFreqMap.size();
    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (docTermFreqMap.count(term) != 0)
        {
            std::size_t const docTermFrequency = docTermFreqMap.at(term);

            double c = static_cast<double>(docTermFrequency) - this->delta;
            if (!(c > 0)) c = 0;

            score +=
                log(c / static_cast<float>(docLen) +
                    this->delta * static_cast<float>(nUniqueTerms) /
                        static_cast<float>(docLen) *
                        this->termProbabilityMap.at(term));
        }
    }

    return score;
}

base::FValType LMIR::dirichlet(
    base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
    base::StrSizeMap const & queryTermFreqMap) const
{
    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (docTermFreqMap.count(term) != 0)
        {
            double const & docTermFrequency =
                static_cast<double>(docTermFreqMap.at(term));
            double const & termProb =
                static_cast<double>(this->termProbabilityMap.at(term));

            score +=
                log((docTermFrequency + this->mu * termProb) /
                    static_cast<double>(docLen + this->mu));
        }
    }

    return score;
}

base::FValType LMIR::jelinek_mercer(
    base::StrSizeMap const & docTermFreqMap, std::size_t const docLen,
    base::StrSizeMap const & queryTermFreqMap) const
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
    base::StrSizeMap const & docTermFreqMap, std::size_t const docLen) const
{
    base::StrDblMap pMl;
    for (auto const & mapPair : docTermFreqMap)
        pMl[mapPair.first] =
            static_cast<double>(mapPair.second) / static_cast<double>(docLen);

    return pMl;
}

}  // namespace lowletorfeats
