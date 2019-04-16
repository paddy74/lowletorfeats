#pragma once

#include <functional>  // function

#include "base/Document.hpp"  // StructuredDocument


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
        std::string const & queryText,
        std::string const & queryId
    );

    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        std::string const & queryText
    );

    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        std::string const & queryText,
        std::string const & queryId
    );

    /* Public class methods */

    /**
     * @brief Collect the predetermined feature set.
     *  Will delete the existing `featureMapVect`.
     *
     */
    void collectPresetFeatures();

    /**
     * @brief Recollect the existing feature set.
     *  Recollect the features for the existing keys in the `featureMapVect`.
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
    uint const getNumDocs() const
    { return this->numDocs; };
    uint const getNumFeatures() const;

    /* Setter methods */
    void setSectionWeights(
        std::unordered_map<std::string, double> const & sectionWeights)
    { this->sectionWeights = sectionWeights; }

    /* Static setter methods */
    static void setAnalyzerFunction(
        std::function<
            std::pair<base::StrUintMap, uint>
            (std::string)
        > analyzerFunction
    )
    { FeatureCollector::anlyzToTfMapLenPair = analyzerFunction; }

private:
    /* Private member variables */
    std::vector<base::FeatureKey> const PRESET_FEATURES =
    {
        base::FeatureKey("other", "dl", "full"),
        base::FeatureKey("tfidf", "tfdoublenorm", "full"),
        base::FeatureKey("tfidf", "idfdefault", "full"),
        base::FeatureKey("tfidf", "tfidf", "full"),
        base::FeatureKey("okapi", "bm25", "full"),
        base::FeatureKey("lmir", "abs", "full"),
        base::FeatureKey("lmir", "dir", "full"),
        base::FeatureKey("lmir", "jm", "full")
    };

    std::unordered_map<std::string, double> sectionWeights =
    {
        {"full", 1},
        {"title", 1},
        {"body", 1},
        {"anchor", 1},
        {"url", 1}
    };

    uint numDocs;
    base::StrUintMap avgDocLenMap;

    // Vector of term frequencies of structured documents
    std::vector<StructuredDocument> docVect;

    // Number of documents containing a term for every term
    base::StructuredTermFrequencyMap structDocsWithTermMap;
    base::StrUintMap totalTermsMap;

    // `TermFrequencyMap` for the query string
    base::StrUintMap queryTfMap;
    // The query id for the `queryTfMap`
    std::string queryId = "-1";


    /* Static private member variables */

    static std::function<
        std::pair<base::StrUintMap, uint>
        (std::string)
    > anlyzToTfMapLenPair;  // TODO: default

    static base::StrUintMap anlyzToTfMap(std::string inputText)
    {
        auto const & tfMapPair =
            FeatureCollector::anlyzToTfMapLenPair(inputText);
        return tfMapPair.first;
    }

    /* Private class methods */
    void sumTotalTermsPerSection();
    void clearFeatureMaps();
    void assertProperties();
};

}
