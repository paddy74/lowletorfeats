#pragma once

#include <lowletorfeats/LMIR.hpp>
#include <lowletorfeats/base/Document.hpp>
#include <textalyzer/Analyzer.hpp>
#include <unordered_set>

namespace lowletorfeats
{
/**
 * @brief Conduct feature collection for a query and a collection of documents.
 *
 */
class FeatureCollector
{
public:
    /* Constructors */
    /****************/

    /**
     * @brief Construct an empty Feature Collector.
     *
     */
    FeatureCollector();

    /**
     * @brief Construct a new Feature Collector from raw full text documents.
     *
     * @param docTextMapVect Multiple structured documents of raw text.
     * @param queryText Raw unanalyzed query string.
     */
    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        std::string const & queryText);

    /**
     * @brief Construct a new Feature Collector from raw full text documents.
     *
     * @param docTextMapVect Multiple structured documents of raw text.
     * @param queryTfMap Preanalyzed query string.
     */
    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        base::StrUintMap const & queryTfMap);

    /**
     * @brief Construct a new Feature Collector from preanalyzed structured
     * docs.
     *
     * @param docLenMapVect Multiple structured documents with their length for
     *  each section.
     * @param docTfMapVect Multiple structured documents with analyzed tokens
     * for each section.
     * @param queryText Raw unanalyzed query string.
     */
    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        std::string const & queryText);

    /**
     * @brief Construct a new Feature Collector from preanalyzed structured
     * docs.
     *
     * @param docLenMapVect Multiple structured documents with their length for
     *  each section.
     * @param docTfMapVect Multiple structured documentds with analyzed tokens
     * for each section.
     * @param queryTfMap Preanalyzed query string.
     */
    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        base::StrUintMap const & queryTfMap);

    /* Public class methods */
    /************************/

    /**
     * @brief Get a string representation of the `FeatureCollector`.
     *  This is not intended to be optimized.
     *
     * @return std::string
     */
    std::string toString() const;

    /**
     * @brief Get a string of per-document features.
     *
     */
    std::string getFeatureString() const;

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
     * @brief Collect multiple features using a vector of `FeatureKey`s.
     *
     * @param fNameVect The features to collect
     */
    void collectFeatures(std::vector<base::FeatureKey> const & fKeyVect);

    /* Getter methods */
    /******************/

    std::size_t getNumDocs() const;
    std::size_t getNumFeatures() const;

    std::vector<StructuredDocument> const & getDocVect() const;

    std::vector<std::vector<base::FValType>> const getFeatureVects() const;

    /* Setter methods */
    /******************/

    void setSectionWeights(
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights)
    {
        this->sectionWeights = sectionWeights;
    }

    /* Static setter methods */
    /*************************/

    static void setAnalyzerFunction(
        textalyzer::AnlyzerFunType<std::string> const & analyzerFunction)
    {
        FeatureCollector::analyzerFun = analyzerFunction;
    }

private:
    /* Private member variables */
    /****************************/

    std::unordered_map<std::string, base::WeightType> sectionWeights = {
        {"full", 0.3},   {"title", 1},    {"body", 0.4},
        {"author", 0.9}, {"anchor", 0.5}, {"url", 0.7}};

    // `TermFrequencyMap` for the query string
    base::StrUintMap queryTfMap;

    // Number of documents in the collection
    std::size_t numDocs;

    // Set of the section keys
    std::unordered_set<std::string> sectionKeys;

    // Vector of term frequencies of structured documents
    std::vector<StructuredDocument> docVect;

    // Average document length per section
    base::StrUintMap avgDocLenPerSection;

    // Collection wide term frequency map per section
    base::StructuredTermFrequencyMap tfMapPerSection;

    // Number of documents containing a term for every section
    base::StructuredTermFrequencyMap nDocsWithTermPerSection;

    // Total number of terms per section
    base::StrUintMap nTermsPerSection;

    // For calculating LMIR features
    std::unordered_map<std::string, LMIR> lmirCalculators;

    /* Private static member variables */

    // Analyzer method for a string of text into pair<tokenStrVect, docLen>.
    textalyzer::AnlyzerFunType<std::string> static analyzerFun;
    uint8_t static const DEFAULT_NGRAMS;

    /* Private class methods */
    /*************************/

    /**
     * @brief Construct the lmirCalculator if it is not already constructed.
     *
     */
    void constructLMIR(std::string const & sectionKey);

    /**
     * @brief Add the given document to the docVect.
     *  TODO: Add protections so this can only be called from initDocs.
     *
     * @param newDoc
     */
    void addDoc(StructuredDocument const & newDoc);

    /**
     * @brief Create a new document in the docVect from a preanalyzed map.
     *
     * @param docLenMap
     * @param strucDocTfMap
     */
    void addDoc(
        base::StrUintMap const & docLenMap,
        base::StructuredTermFrequencyMap const & strucDocTfMap);

    /**
     * @brief Initialize unanalyzed structured documents.
     *  TODO: Add protection so it can only be called from a constructor
     *
     * @param docTextMapVect
     */
    void initDocs(std::vector<base::StrStrMap> const & docTextMapVect);

    /**
     * @brief Initialize preanalyzed structured documents.
     *
     * @param docLenMapVect
     * @param docTfMapVect
     */
    void initDocs(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect);

    /**
     * @brief Initialize the `nDocsWithTermPerSection` and `tfMapPerSection`
     * class variables.
     *
     * @param sectionTfMap
     */
    void initNDocsWithTermPerSection(
        std::string const & sectionKey, base::StrUintMap const & sectionTfMap);

    /**
     * @brief Calculate the total number of terms per section in the
     * collection.
     *
     */
    void initNTermsPerSection();

    /**
     * @brief Initialize the full section from contents of other sections.
     *
     */
    void initFullFromOthers();

    /**
     * @brief Clear the feature maps of every document.
     *
     */
    void clearFeatureMaps();

    /**
     * @brief Assert required properties of the feature collector to ensure
     *  acceptable operations.
     *
     */
    void assertProperties();

    /* Private static class methods */
    /********************************/

    /**
     * @brief Throw an error for an unsupported feature type.
     *
     */
    void static throwUnsupportedFeatureType(std::string const & fType);

    /**
     * @brief Throw an error for an unsupported feature name.
     *
     */
    void static throwUnsupportedFeatureName(std::string const & fName);
};

}  // namespace lowletorfeats
