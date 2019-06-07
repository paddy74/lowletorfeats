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
        uint const & docTermFrequency, uint const & numDocs,
        uint const & numDocsWithTerm, uint const & avgDocLen, float const & b,
        float const & k1);
    static base::FValType bm25(
        uint const & docTermFrequency, uint const & numDocs,
        uint const & numDocsWithTerm, uint const & avgDocLen);
    static base::FValType queryBm25(
        base::StrUintMap const & docTermFreqMap, uint const & numDocs,
        base::StrUintMap const & docsWithTermFreqMap, uint const & avgDocLen,
        base::StrUintMap const & queryTermFreqMap);

    /* BM25+ */
    /*********/
    static base::FValType bm25plus(
        uint const & docTermFrequency, uint const & numDocs,
        uint numDocsWithTerm, uint const & avgDocLen, float const & b,
        float const & k1, float const & delta);
    static base::FValType bm25plus(
        uint const & docTermFrequency, uint const & numDocs,
        uint const & numDocsWithTerm, uint const & avgDocLen);
    static base::FValType queryBm25plus(
        base::StrUintMap const & docTermFreqMap, uint const & numDocs,
        base::StrUintMap const & docsWithTermFreqMap, uint const & avgDocLen,
        base::StrUintMap const & queryTermFreqMap);

    /* BM25f */
    /*********/
    static base::FValType queryBm25f(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        uint const & numDocs,
        base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
        base::StrUintMap const & avgDocLenMap,
        base::StrUintMap const & queryTermFreqMap,
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights);

    /* BM25f+ */
    /**********/
    static base::FValType queryBm25fplus(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        uint const & numDocs,
        base::StructuredTermFrequencyMap const & structDocsWithTermFreqMap,
        base::StrUintMap const & avgDocLenMap,
        base::StrUintMap const & queryTermFreqMap,
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights);

private:
    Okapi() {}
};

}  // namespace lowletorfeats
