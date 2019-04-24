#pragma once

#include "base/Document.hpp"  // StructuredDocument

#include <textalyzer/Analyzer.hpp>

#include <functional>  // function


namespace lowletorfeats
{

/**
 * @brief Conduct feature collection for a collection of documents.
 *
 */
class FeatureCollector
{
public:
    /* Public member variables */

    /* Constructors */

    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        std::string const & queryText
    );

    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        base::StrUintMap const & queryTfMap
    );


    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        std::string const & queryText
    );

    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        base::StrUintMap const & queryTfMap
    );


    /* Public class methods */

    std::string toString() const;

    /**
     * @brief Collect the predetermined feature set.
     *  Will delete the existing `featureMapVect`.
     *
     */
    void collectPresetFeatures();

    /**
     * @brief Recollect the existing feature set.
     *  Recollect the features for the existing keys in the `featureMapVect`.
     *  Will delete the existing values of `featureMapVect`.
     */
    void reCollectFeatures();

    /**
     * @brief Collect the named feature for every document
     *
     * @param fName The feature to collect.
     */
    void collectFeatures(base::FeatureKey const & fKey);

    /**
     * @brief Collect the named features for every document.
     *
     * @param fNameVect The features to collect
     */
    void collectFeatures(std::vector<base::FeatureKey> const & fKeyVect);


    /* Getter methods */

    std::size_t const getNumDocs() const
    { return this->numDocs; };
    std::size_t const getNumFeatures() const;

    std::vector<StructuredDocument> const & getDocVect() const
    { return this->docVect; }


    /* Setter methods */

    void setSectionWeights(
        std::unordered_map<std::string, double> const & sectionWeights)
    { this->sectionWeights = sectionWeights; }


    /* Static setter methods */

    static void setAnalyzerFunction(
        textalyzer::AnlyzerFunType<std::string> analyzerFunction
    )
    { FeatureCollector::analyzerFun = analyzerFunction; }

private:
    /* Private member variables */

    std::unordered_map<std::string, double> sectionWeights =
    {
        {"full", 1},
        {"title", 1},
        {"body", 1},
        {"anchor", 1},
        {"url", 1}
    };

    std::size_t numDocs;
    base::StrUintMap avgDocLenMap;

    // Vector of term frequencies of structured documents
    std::vector<StructuredDocument> docVect;

    // Number of documents containing a term for every term
    base::StructuredTermFrequencyMap structDocsWithTermMap;
    base::StrUintMap totalTermsMap;

    // `TermFrequencyMap` for the query string
    base::StrUintMap queryTfMap;


    /* Static private member variables */

    std::vector<base::FeatureKey> static const PRESET_FEATURES;

    static textalyzer::AnlyzerFunType<std::string> analyzerFun;
    uint8_t static const DEFAULT_NGRAMS;


    /* Private class methods */
    void initDocs(std::vector<base::StrStrMap> const & docTextMapVect);
    void initDocs(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect
    );

    void sumTotalTermsPerSection();
    void clearFeatureMaps();
    void assertProperties();
};

}
