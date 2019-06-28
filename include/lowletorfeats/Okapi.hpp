#pragma once

#include <lowletorfeats/base/stdDef.hpp>

namespace lowletorfeats
{
/**
 * @brief Static class for calculating Okapi BM25 like scores.
 *
 */
class Okapi
{
public:
    /* BM25 */
    /********/
    static base::FValType bm25(
        std::size_t const & docTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm, float const & avgDocLen,
        float const & b, float const & k1);
    static base::FValType bm25(
        std::size_t const & docTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm, float const & avgDocLen);
    static base::FValType queryBm25(
        base::StrSizeMap const & docTermFreqMap, std::size_t const & numDocs,
        base::StrSizeMap const & docsWithTermFreqMap, float const & avgDocLen,
        base::StrSizeMap const & queryTermFreqMap);

    /* BM25+ */
    /*********/
    static base::FValType bm25plus(
        std::size_t const & docTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm, float const & avgDocLen,
        float const & b, float const & k1, float const & delta);
    static base::FValType bm25plus(
        std::size_t const & docTermFrequency, std::size_t const & numDocs,
        std::size_t const & numDocsWithTerm, float const & avgDocLen);
    static base::FValType queryBm25plus(
        base::StrSizeMap const & docTermFreqMap, std::size_t const & numDocs,
        base::StrSizeMap const & docsWithTermFreqMap, float const & avgDocLen,
        base::StrSizeMap const & queryTermFreqMap);

    /* BM25f */
    /*********/
    static base::FValType queryBm25f(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        std::size_t const & numDocs,
        base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
        base::StrFltMap const & avgDocLenMap,
        base::StrSizeMap const & queryTermFreqMap,
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights);

    /* BM25f+ */
    /**********/
    static base::FValType queryBm25fplus(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        std::size_t const & numDocs,
        base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
        base::StrFltMap const & avgDocLenMap,
        base::StrSizeMap const & queryTermFreqMap,
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights);

private:
    Okapi() {}
};

}  // namespace lowletorfeats
