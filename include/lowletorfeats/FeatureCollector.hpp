#pragma once

#include <array>

#include <lowletorfeats/base/stdllf.hpp>

#include "Document.hpp"


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
    void collectFeatures(base::FeatureNames fName);

    /**
     * @brief Collect the named features for every document.
     *
     * @param fNameVect The features to collect
     */
    void collectFeatures(std::vector<base::FeatureNames> fNameVect);

    /* Getter methods */
    uint const getNumDocs() const
    { return this->numDocs; };
    uint const getNumFeatures() const;

private:
    /* Private member variables */
    std::vector<base::FeatureNames> const PRESET_FEATURES =
    {
        base::FeatureNames::dl,
        base::FeatureNames::tfdoublenorm,
        base::FeatureNames::idfdefault,
        base::FeatureNames::tfidf,
        base::FeatureNames::bm25,
        base::FeatureNames::abs,
        base::FeatureNames::dir,
        base::FeatureNames::jm
    };

    uint numDocs;
    base::StrUintMap avgDocLenMap;

    // Vector of term frequencies of structured documents
    std::vector<StructuredDocument> docVect;

    // Number of documents containing a term for every term
    base::StrUintMap docsWithTermMap;

    // `TermFrequencyMap` for the query string
    base::StrUintMap queryTfMap;
    // The query id for the `queryTfMap`
    std::string queryId = "-1";


    /* Private class methods */
    void calcAvgDocLengths();
    void createDocsWithTermMap();
    void clearFeatureMaps();
    void assertProperties();
};

}
