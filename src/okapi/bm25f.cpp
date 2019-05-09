#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/Tfidf.hpp>

namespace lowletorfeats
{
/**
 * @brief Calculate the BM25f score.
 *
 * @param structDocTermFreqMap
 * @param numDocs
 * @param structDocsWithTermFreqMap
 * @param avgDocLen
 * @param queryTermFreqMap
 * @param sectionWeights
 * @return base::FValType
 */
base::FValType Okapi::queryBm25f(
    base::StructuredTermFrequencyMap const & structDocTermFreqMap,
    uint const & numDocs,
    base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
    base::StrUintMap const & avgDocLenMap,
    base::StrUintMap const & queryTermFreqMap,
    std::unordered_map<std::string, base::WeightType> const & sectionWeights)
{
    // Calculate full idf
    base::FValType fullIdf = 0;
    for (auto const & mapPair : structDocsWithTermFreqMap.at("full"))
        fullIdf += Tfidf::idfNorm(numDocs, mapPair.second);

    // Calculate BM25 for each field
    base::FValType totalBm25 = 0;
    for (auto const & [sectionKey, tfMap] : structDocTermFreqMap)
    {
        if (!(structDocsWithTermFreqMap.count(sectionKey) == 0 ||
              sectionWeights.count(sectionKey) == 0) ||
            avgDocLenMap.count(sectionKey) == 0)
        {
            auto const & docsWithTermFreqMap =
                structDocsWithTermFreqMap.at(sectionKey);
            auto const & weight = sectionWeights.at(sectionKey);
            auto const & avgDocLen = avgDocLenMap.at(sectionKey);

            base::FValType bm25 = Okapi::queryBm25(
                tfMap, numDocs, docsWithTermFreqMap, avgDocLen,
                queryTermFreqMap);
            bm25 *= weight;

            totalBm25 += bm25;
        }
    }

    // Calculate BM25f
    return fullIdf * totalBm25;
}

/**
 * @brief Calculate the BM25f+ score.
 *
 * @param structDocTermFreqMap
 * @param numDocs
 * @param structDocsWithTermFreqMap
 * @param avgDocLen
 * @param queryTermFreqMap
 * @param sectionWeights
 * @return base::FValType
 */
base::FValType Okapi::queryBm25fplus(
    base::StructuredTermFrequencyMap const & structDocTermFreqMap,
    uint const & numDocs,
    base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
    base::StrUintMap const & avgDocLenMap,
    base::StrUintMap const & queryTermFreqMap,
    std::unordered_map<std::string, base::WeightType> const & sectionWeights)
{
    // Calculate full idf
    base::FValType fullIdf = 0;
    for (auto const & mapPair : structDocsWithTermFreqMap.at("full"))
        fullIdf += Tfidf::idfNorm(numDocs, mapPair.second);

    // Calculate BM25 for each field
    base::FValType totalBm25plus = 0;
    for (auto const & [sectionKey, tfMap] : structDocTermFreqMap)
    {
        if (!(structDocsWithTermFreqMap.count(sectionKey) == 0 ||
              sectionWeights.count(sectionKey) == 0) ||
            avgDocLenMap.count(sectionKey) == 0)
        {
            auto const & docsWithTermFreqMap =
                structDocsWithTermFreqMap.at(sectionKey);
            auto const & weight = sectionWeights.at(sectionKey);
            auto const & avgDocLen = avgDocLenMap.at(sectionKey);

            base::FValType bm25plus = Okapi::queryBm25plus(
                tfMap, numDocs, docsWithTermFreqMap, avgDocLen,
                queryTermFreqMap);
            bm25plus *= weight;

            totalBm25plus += bm25plus;
        }
    }

    // Calculate BM25f
    return fullIdf * totalBm25plus;
}

}  // namespace lowletorfeats
