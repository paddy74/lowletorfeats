#pragma once

#include <lowletorfeats/base/stdllf.hpp>


namespace lowletorfeats
{

class Okapi
{
public:
    /* BM25 */
    static double bm25(
        uint const & docTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm,
        uint const & avgDocLen,
        float const & b, float const & k1
    );
    static double bm25(
        uint const & docTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm,
        uint const & avgDocLen
    );
    static double queryBm25(
        base::StrUintMap const & docTermFreqMap,
        uint const & numDocs, base::StrUintMap const & docsWithTermFreqMap,
        uint const & avgDocLen,
        base::StrUintMap const & queryTermFreqMap
    );

    /* BM25+ */
    static double bm25plus(
        uint const & docTermFrequency,
        uint const & numDocs, uint numDocsWithTerm,
        uint const & avgDocLen,
        float const & b, float const & k1, float const & delta
    );
    static double bm25plus(
        uint const & docTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm,
        uint const & avgDocLen
    );
    static double queryBm25plus(
        base::StrUintMap const & docTermFreqMap,
        uint const & numDocs, base::StrUintMap const & docsWithTermFreqMap,
        uint const & avgDocLen,
        base::StrUintMap const & queryTermFreqMap
    );

    /* BM25f */
    static double queryBm25f(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        uint const & numDocs,
        base::StructuredTermFrequencyMap structDocsWithTermFreqMap,
        base::StrUintMap const & avgDocLenMap,
        base::StrUintMap const & queryTermFreqMap,
        std::unordered_map<std::string, double> structWeights
    );

    /* BM25f+ */
    static double queryBm25fplus(
        base::StructuredTermFrequencyMap const & structDocTermFreqMap,
        uint const & numDocs,
        base::StructuredTermFrequencyMap structDocsWithTermFreqMap,
        base::StrUintMap const & avgDocLenMap,
        base::StrUintMap const & queryTermFreqMap,
        std::unordered_map<std::string, double> structWeights
    );

private:
    Okapi() {}
};

}
