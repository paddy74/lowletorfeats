#pragma once

#include <array>

#include <lowletorfeats/base/stdllf.hpp>


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
    std::array<std::string, 8> const PRESET_FEATURES
    {
        "tfidf.tf",  // Term frequency
        "tfidf.idf",  // Inverse document frequency
        "tfidf.tfidf",  // TF/IDF
        "dl",  // Document length
        "okapi.bm25",
        "lmir.abs",
        "lmir.dir",
        "lmir.jm"
    };

    /* Constructors */
    FeatureCollector(
        std::vector<std::string> const & docTextVector,
        std::string const & queryText
    );
    FeatureCollector(
        std::vector<std::string> const & docTextVector,
        std::string const & queryText,
        std::string const & queryId
    );

    /* Public class methods */

    /**
     * @brief Collect the predetermined feature set.
     *  Will delete the existing `featureMapVect`.
     *
     */
    void runFeatureCollection();

    /**
     * @brief Recollect the existing feature set.
     *  Recollect the features for the existing keys in the `featureMapVect`.
     */
    void rerunFeatureCollection();

    /**
     * @brief Collect the named feature and store to the same key.
     *
     * @param featureName Name of the feature to collect.
     */
    void collectNamedFeature(std::string const & featureName);

    /**
     * @brief Collect a vector of named features and store to the same key.
     *
     * @param featureNameVect
     */
    void collectNamedFeature(std::vector<std::string> const & featureNameVect);

    void saveFeatureMap(std::string const & saveFile);
    void saveFeatureMap(std::string const & saveFile, std::string queryId);

    /* Getter methods */
    std::vector<base::DocFeatureMap> getFeatureMapVect() const;
    uint getNumFeatures() const;

protected:
    /* Private member variables */
    std::vector<base::DocFeatureMap> featureMapVect;
    std::string queryId = "-1";
};


/**
 * @brief Conduct feature collection for a collection of structured documents.
 *
 */
class StructuredFeatureCollector : FeatureCollector
{
public:
    /* Public member variables */
    std::array<std::string, 41> const PRESET_FEATURES
    {
        "tfidf.tf.full",  // Term frequency
        "tfidf.tf.body",
        "tfidf.tf.anchor",
        "tfidf.tf.title",
        "tfidf.tf.url",

        "tfidf.idf.full",  // Inverse document frequency
        "tfidf.idf.body",
        "tfidf.idf.anchor",
        "tfidf.idf.title",
        "tfidf.idf.url",

        "tfidf.tfidf.full",  // TF/IDF
        "tfidf.tfidf.body",
        "tfidf.tfidf.anchor",
        "tfidf.tfidf.title",
        "tfidf.tfidf.url",

        "dl.full",  // Document length
        "dl.body",
        "dl.anchor",
        "dl.title",
        "dl.url",

        "okapi.bm25f",  // BM25F

        "okapi.bm25.full",  // BM25
        "okapi.bm25.body",
        "okapi.bm25.anchor",
        "okapi.bm25.title",
        "okapi.bm25.url",

        "lmir.abs.full",  // Absolute discount smoothing
        "lmir.abs.body",
        "lmir.abs.anchor",
        "lmir.abs.title",
        "lmir.abs.url",

        "lmir.dir.full",  // Bayesian smoothing using Dirichlet priors
        "lmir.dir.body",
        "lmir.dir.anchor",
        "lmir.dir.title",
        "lmir.dir.url",

        "lmir.jm.full",  // Jelinkey-Mercer smoothing
        "lmir.jm.body",
        "lmir.jm.anchor",
        "lmir.jm.title",
        "lmir.jm.url",
    };

    /* Constructors */
    StructuredFeatureCollector(
        std::vector<std::map<std::string, std::string>> const & docTextVector,
        std::string const & queryText
    );
    StructuredFeatureCollector(
        std::vector<std::map<std::string, std::string>> const & docTextVector,
        std::string const & queryText,
        std::string const & queryId
    );
};

}
