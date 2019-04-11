#pragma once

#include <lowletorfeats/base/stdllf.hpp>


namespace lowletorfeats
{

class Tfidf
{
public:
    /* Term frequency */
    static double tfLogNorm(uint const & docTermFrequency);
    static double tfDoubleNorm(
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        float const & k);
    static double tfDoubleNorm(
        uint const & docTermFrequency, uint const & docMaxTermFrequency);
    static double queryTf(
        base::StrUintMap const & docTermFreqMap, uint const & docMaxTermFrequency
    );
    static double sumTfLogNorm(
        base::StrUintMap const & docTermFreqMap
    );
    static double sumTfDoubleNorm(
        base::StrUintMap const & docTermFreqMap, uint const & docMaxTermFrequency
    );

    /* IDF */
    double static idfDefault(uint const & numDocs, uint const & numDocsWithTerm);
    double static idfSmooth(uint const & numDocs, uint const & numDocsWithTerm);
    double static idfMax(uint const & numDocsWithTerm, uint const & docMaxTermFrequency);
    double static idfProb(uint const & numDocs, uint const & numDocsWithTerm);
    double static idfNorm(uint const & numDocs, uint const & numDocsWithTerm);

    /* TF/IDF */
    double static tfidf(
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm
    );
    double static tfidf(
        double (*tfFunction)(uint const &),
        double (*idfFunction)(uint const &, uint const &),
        uint const & docTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm
    );
    double static tfidf(
        double (*tfFunction)(uint, uint),
        double (*idfFunction)(uint, uint),
        uint const & docTermFrequency, uint const & docMaxTermFrequency,
        uint const & numDocs, uint const & numDocsWithTerm
    );
    double static queryTfidf(
        base::StrUintMap const & docTermFreqMap, uint const & docMaxTermFrequency,
        uint const & numDocs, base::StrUintMap const & docsWithTermFreqMap,
        base::StrUintMap const & queryTermFreqMap
    );

private:
    Tfidf() {}
};

}
