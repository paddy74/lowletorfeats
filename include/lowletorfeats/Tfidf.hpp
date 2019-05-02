#pragma once

#include <lowletorfeats/base/stdDef.hpp>

namespace lowletorfeats
{
class Tfidf
{
public:
    /* Term frequency */
    static base::FValType tfLogNorm(uint const & docTermFrequency);
    static base::FValType tfDoubleNorm(
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        float const & k);
    static base::FValType tfDoubleNorm(
        uint const & docTermFrequency, uint const & docMaxTermFrequency);
    static base::FValType sumTfLogNorm(
        base::StrUintMap const & docTermFreqMap);
    static base::FValType sumTfDoubleNorm(
        base::StrUintMap const & docTermFreqMap,
        uint const & docMaxTermFrequency);

    /* IDF */
    base::FValType static idfDefault(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfSmooth(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfMax(
        uint const & numDocsWithTerm, uint const & docMaxTermFrequency);
    base::FValType static idfProb(
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static idfNorm(
        uint const & numDocs, uint const & numDocsWithTerm);

    /* TF/IDF */
    base::FValType static tfidf(
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(uint const &),
        base::FValType (*idfFunction)(uint const &, uint const &),
        uint const & docTermFrequency, uint const & numDocs,
        uint const & numDocsWithTerm);
    base::FValType static tfidf(
        base::FValType (*tfFunction)(uint, uint),
        base::FValType (*idfFunction)(uint, uint),
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm);
    base::FValType static queryTfidf(
        base::StrUintMap const & docTermFreqMap,
        uint const & docMaxTermFrequency, uint const & numDocs,
        base::StrUintMap const & docsWithTermFreqMap,
        base::StrUintMap const & queryTermFreqMap);

private:
    Tfidf() {}
};

}  // namespace lowletorfeats
