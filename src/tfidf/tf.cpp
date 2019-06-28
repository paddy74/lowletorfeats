#include <cmath>  // log
#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/utils.hpp>

namespace lowletorfeats
{
base::FValType Tfidf::tfLogNorm(std::size_t const & docTermFrequency)
{
    return log(1 + static_cast<base::FValType>(docTermFrequency));
}

base::FValType Tfidf::tfDoubleNorm(
    std::size_t const & docTermFrequency,
    std::size_t const & docMaxTermFrequency, float const & k)
{
    return k + ((1 - k) * (static_cast<base::FValType>(docTermFrequency) /
                           static_cast<base::FValType>(
                               (docMaxTermFrequency + docTermFrequency))));
}

base::FValType Tfidf::tfDoubleNorm(
    std::size_t const & docTermFrequency,
    std::size_t const & docMaxTermFrequency)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency, 0.5);
}

base::FValType Tfidf::sumTfLogNorm(base::StrSizeMap const & docTermFreqMap)
{
    return Tfidf::tfLogNorm(utils::mapValueSum(docTermFreqMap));
    ;
}

base::FValType Tfidf::sumTfDoubleNorm(
    base::StrSizeMap const & docTermFreqMap,
    std::size_t const & docMaxTermFrequency)
{
    return tfDoubleNorm(
        utils::mapValueSum(docTermFreqMap), docMaxTermFrequency);
}

}  // namespace lowletorfeats
