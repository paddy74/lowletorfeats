#include <cassert>
#include <lowletorfeats/Tfidf.hpp>

namespace lowletorfeats
{
/**
 * @brief Calculate Term Frequency / Inverse Document Frequency (TF/IDF) for
 *  a single term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring
 * term.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
base::FValType Tfidf::tfidf(
    std::size_t const & docTermFrequency,
    std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
    std::size_t const & numDocsWithTerm)
{
    return tfDoubleNorm(docTermFrequency, docMaxTermFrequency) *
           idfNorm(numDocs, numDocsWithTerm);
}

/**
 * @brief Calculate TF/IDF with the given TF and IDF versions for a single
 * term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
base::FValType Tfidf::tfidf(
    base::FValType (*tfFunction)(std::size_t const &),
    base::FValType (*idfFunction)(std::size_t const &, std::size_t const &),
    std::size_t const & docTermFrequency, std::size_t const & numDocs,
    std::size_t const & numDocsWithTerm)
{
    return (*tfFunction)(docTermFrequency) *
           (*idfFunction)(numDocs, numDocsWithTerm);
}

/**
 * @brief Calculate TF/IDF with the given TF and IDF versions for a single
 * term.
 *
 * @param docTermFrequency The term's term frequency in the given document.
 * @param docMaxTermFrequency Frequency of the document's maximum occuring
 * term.
 * @param numDocs Number of documents in the collection.
 * @param numDocsWithTerm Number of documents in the collection with the term.
 * @return double
 */
base::FValType Tfidf::tfidf(
    base::FValType (*tfFunction)(std::size_t const &, std::size_t const &),
    base::FValType (*idfFunction)(std::size_t const &, std::size_t const &),
    std::size_t const & docTermFrequency,
    std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
    std::size_t const & numDocsWithTerm)
{
    return (*tfFunction)(docTermFrequency, docMaxTermFrequency) *
           (*idfFunction)(numDocs, numDocsWithTerm);
}

/**
 * @brief Calculate the TF-IDF of a document for a group of terms (query).
 *  To calculate the TF-IDF for an entire document (no query) the
 *  `queryTermFreqMap` should be the document's token vector.
 *
 * @param docTermFreqMap `TermFrequencyMap` for the document.
 * @param docMaxTermFrequency Number of times the document's maximum occuring
 *  term appears in the document.
 * @param numDocs Number of documents in the collection.
 * @param docsWithTermFreqMap Number of documents containing each term.
 * @param queryTermFreqMap `TermFrequencyMap` for the query.
 * @return double
 */
base::FValType Tfidf::queryTfidf(
    base::StrSizeMap const & docTermFreqMap,
    std::size_t const & docMaxTermFrequency, std::size_t const & numDocs,
    base::StrSizeMap const & docsWithTermFreqMap,
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
            std::size_t const docTermFrequency = docTermFreqMap.at(term);
            std::size_t const numDocsWithTerm = docsWithTermFreqMap.at(term);

            score += tfidf(
                docTermFrequency, docMaxTermFrequency, numDocs,
                numDocsWithTerm);
        }
    }

    return score;
}

}  // namespace lowletorfeats
