#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/Tfidf.hpp>

namespace lowletorfeats
{
/**
 * @brief Calculate Okapi Best Match 25 (BM25) for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @param avgDocLen Average document length of the collection.
 * @param b
 * @param k1
 * @return double
 */
base::FValType Okapi::bm25(
    std::size_t const & docTermFrequency, std::size_t const & numDocs,
    std::size_t const & numDocsWithTerm, float const & avgDocLen,
    float const & b, float const & k1)
{
    base::FValType const idf = Tfidf::idfNorm(numDocs, numDocsWithTerm);

    base::FValType const numer =
        static_cast<float>(docTermFrequency) * (k1 + 1);
    base::FValType const denom =
        static_cast<base::FValType>(docTermFrequency) +
        (k1 * (1 - b +
               (b * (static_cast<base::FValType>(numDocs) /
                     static_cast<base::FValType>(avgDocLen)))));

    return idf * (numer / denom);
}

/**
 * @brief Calculate Okapi Best Match 25 (BM25) for a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @param avgDocLen Average document length of the collection.
 * @return double
 */
base::FValType Okapi::bm25(
    std::size_t const & docTermFrequency, std::size_t const & numDocs,
    std::size_t const & numDocsWithTerm, float const & avgDocLen)
{
    float const k1 = 1.2f;
    float const b = 0.74f;

    return Okapi::bm25(
        docTermFrequency, numDocs, numDocsWithTerm, avgDocLen, b, k1);
}

/**
 * @brief Calculate the BM25 of a document for a group of terms (query).
 *  To calculate the BM25 for an entire document (no query) the
 *  `queryTermFreqMap` should be the document's token vector.
 *
 * @param docTermFreqMap `TermFrequencyMap` for the document.
 * @param numDocs Number of documents in the collection.
 * @param docsWithTermFreqMap Number of documents containing each term.
 * @param avgDocLen Average document length of the collection.
 * @param queryTermFreqMap `TermFrequencyMap` for the query.
 * @return double
 */
base::FValType Okapi::queryBm25(
    base::StrSizeMap const & docTermFreqMap, std::size_t const & numDocs,
    base::StrSizeMap const & docsWithTermFreqMap, float const & avgDocLen,
    base::StrSizeMap const & queryTermFreqMap)
{
    // Sum the scores for each term
    base::FValType score = 0;
    for (auto const & mapPair : queryTermFreqMap)
    {
        auto const & term = mapPair.first;

        if (!(docTermFreqMap.count(term) == 0 ||
              docsWithTermFreqMap.count(term) == 0))
        {
            auto const docTermFrequency = docTermFreqMap.at(term);
            auto const numDocsWithTerm = docsWithTermFreqMap.at(term);

            score += Okapi::bm25(
                docTermFrequency, numDocs, numDocsWithTerm, avgDocLen);
        }
    }

    return score;
}

}  // namespace lowletorfeats
