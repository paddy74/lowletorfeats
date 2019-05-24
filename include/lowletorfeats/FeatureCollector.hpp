#pragma once

#include <lowletorfeats/LMIR.hpp>
#include <lowletorfeats/base/Document.hpp>
#include <textalyzer/Analyzer.hpp>
#include <unordered_set>

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

    FeatureCollector();

    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        std::string const & queryText);

    FeatureCollector(
        std::vector<base::StrStrMap> const & docTextMapVect,
        base::StrUintMap const & queryTfMap);

    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        std::string const & queryText);

    FeatureCollector(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
        base::StrUintMap const & queryTfMap);

    /* Public class methods */

    std::string toString() const;
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
     * @brief Collect the named features for every document.
     *
     * @param fNameVect The features to collect
     */
    void collectFeatures(std::vector<base::FeatureKey> const & fKeyVect);

    /* Getter methods */

    std::size_t getNumDocs() const;
    std::size_t getNumFeatures() const;

    std::vector<StructuredDocument> const & getDocVect() const;

    std::vector<std::vector<base::FValType>> const getFeatureVects() const;

    /* Setter methods */

    void setSectionWeights(
        std::unordered_map<std::string, base::WeightType> const &
            sectionWeights)
    {
        this->sectionWeights = sectionWeights;
    }

    /* Static setter methods */

    static void setAnalyzerFunction(
        textalyzer::AnlyzerFunType<std::string> const & analyzerFunction)
    {
        FeatureCollector::analyzerFun = analyzerFunction;
    }

private:
    /* Private member variables */

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

    textalyzer::AnlyzerFunType<std::string> static analyzerFun;
    uint8_t static const DEFAULT_NGRAMS;

    /* Private class methods */

    void constructLMIR(std::string const & sectionKey);

    void addDoc(StructuredDocument const & newDoc);
    void addDoc(
        base::StrUintMap const & docLenMap,
        base::StructuredTermFrequencyMap const & strucDocTfMap);

    void initDocs(std::vector<base::StrStrMap> const & docTextMapVect);
    void initDocs(
        std::vector<base::StrUintMap> const & docLenMapVect,
        std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect);

    void initNDocsWithTermPerSection(
        std::string const & sectionKey, base::StrUintMap const & sectionTfMap);
    void initNTermsPerSection();

    void initFullFromOthers();

    void clearFeatureMaps();
    void assertProperties();

    /* Private static class methods */

    void static throwUnsupportedFeatureType(std::string const & fType);
    void static throwUnsupportedFeatureName(std::string const & fName);
};

}  // namespace lowletorfeats
