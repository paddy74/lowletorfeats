#include <cmath>  // log

#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/utils.hpp>

namespace lowletorfeats
{

/**
 * @brief Log normalized term frequency.
 *
 * @param docTermFrequency The term's frequency.
 * @return base::FValType
 */
base::FValType Tfidf::tfLogNorm(uint const & docTermFrequency)
{
    return log(1 + (base::FValType)docTermFrequency);
}


/**
 * @brief Double normalization term frequency.
 *  Prevents a bias towards longer documents.
 *
 * @param docTermFrequency The term's frequency.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @param k
 * @return base::FValType
 */
base::FValType Tfidf::tfDoubleNorm(
    uint const & docTermFrequency, uint const & docMaxTermFrequency,
    float const & k)
{
    return k + ((1 - k)
        * ((base::FValType)docTermFrequency
            / (base::FValType)(docMaxTermFrequency + docTermFrequency)
        )
    );
}


/**
 * @brief Double normalization term frequency (k = 0.5).
 *  Prevents a bias towards longer documents.
 *
 * @param docTermFrequency The term's frequency.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring term.
 * @return base::FValType
 */
base::FValType Tfidf::tfDoubleNorm(
    uint const & docTermFrequency, uint const & docMaxTermFrequency)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency, 0.5);
}


base::FValType Tfidf::sumTfLogNorm(base::StrUintMap const & docTermFreqMap)
{
    return Tfidf::tfLogNorm(utils::mapValueSum(docTermFreqMap));;
}


base::FValType Tfidf::sumTfDoubleNorm(
    base::StrUintMap const & docTermFreqMap,
    uint const & docMaxTermFrequency
)
{
    return tfDoubleNorm(utils::mapValueSum(docTermFreqMap), docMaxTermFrequency);
}

}
