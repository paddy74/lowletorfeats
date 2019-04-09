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
        base::TermFrequencyMap const & docTermFreqMap,
        uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
        uint const & avgDocLen,
        base::TermFrequencyMap const & queryTermFreqMap
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
        base::TermFrequencyMap const & docTermFreqMap,
        uint const & numDocs, base::TermFrequencyMap const & docsWithTermFreqMap,
        uint const & avgDocLen,
        base::TermFrequencyMap const & queryTermFreqMap
    );

private:
    Okapi() {}
};

}
