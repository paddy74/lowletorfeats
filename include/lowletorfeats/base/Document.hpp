#pragma once

#include <lowletorfeats/base/stdDef.hpp>
#include <vector>

namespace lowletorfeats
{
/**
 * @brief Stores structured term frequencies and feature values for a
 *  structured document.
 *
 */
class StructuredDocument
{
public:
    /* Constructors */
    /****************/

    /**
     * @brief Empty constructor.
     *
     */
    StructuredDocument();

    // Preanalyzed

    /**
     * @brief Construct a new Structured Document object using a preanalyzed
     *  document length and `TermFrequencyMap` for the full document text.
     *
     * @param docLen The full document's length.
     * @param fullTermFrequencyMap Preanalyzed `TermFrequencyMap` for the full
     * doc.
     */
    StructuredDocument(  // The indicated section only
        uint const & docLen, base::StrUintMap const & fullTermFrequencyMap,
        std::string const & sectionKey);

    /**
     * @brief Construct a new Structured Document object using a preanalyzed
     *  document length and `TermFrequencyMap` for the full document text.
     *
     * @param docLen The full document's length.
     * @param fullTermFrequencyMap Preanalyzed `TermFrequencyMap` for the full
     * doc.
     */
    StructuredDocument(  // `"full"` section only
        uint const & docLen, base::StrUintMap const & fullTermFrequencyMap);

    /**
     * @brief Construct a new Structured Document object using a preanalyzed
     *  document length map and `TermFrequencyMap`.
     *
     * @param docLenMap The document lengths for each structured section.
     * @param structuredTermFrequencyMap Preanalyzed `TermFrequencyMap`s for
     * each structured section.
     */
    StructuredDocument(  // One or more sections
        base::StrUintMap const & docLenMap,
        base::StructuredTermFrequencyMap const & structuredTermFrequencyMap);

    // Copy constructor

    /**
     * @brief Copy constructor.
     *
     * @param other
     */
    StructuredDocument(StructuredDocument const & other);

    /* Public class methods */
    /************************/

    /**
     * @brief Get a string representation of the `StructuredDocument`.
     *  This is not intended to be optimized.
     *
     * @return std::string
     */
    std::string toString() const;

    /**
     * @brief Clear all sections from the document.
     *
     */
    void clear();

    /**
     * @brief Removes the indicated section from the document.
     *
     * @param section
     */
    void clearSection(std::string const & section);

    /**
     * @brief Clear the document's feature map.
     *
     */
    void clearFeatureMap();

    /* Getter methods */

    /**
     * @brief Get the document length for the full document.
     *
     * @return std::size_t
     */
    std::size_t getDocLen() const;

    /**
     * @brief Get the document length for the document.
     *
     * @param section
     * @return std::size_t const&
     */
    std::size_t getDocLen(std::string const & section) const;

    /**
     * @brief Get the entire structured term frequency map.
     *
     * @return std::unordered_map<std::string, base::TermFrequencyMap> const&
     */
    base::StructuredTermFrequencyMap const & getStructuredTermFrequencyMap()
        const;

    /**
     * @brief Get the `TermFrequencyMap` for the full document.
     *
     * @return base::TermFrequencyMap const&
     */
    base::StrUintMap const & getTermFrequencyMap() const;

    /**
     * @brief Get the `TermFrequencyMap` for the given section.
     *
     * @param section
     * @return base::TermFrequencyMap const&
     */
    base::StrUintMap const & getTermFrequencyMap(
        std::string const & section) const;

    /**
     * @brief Get the max term frequency for the full document.
     *
     * @return std::size_t
     */
    std::size_t getMaxTF() const;

    /**
     * @brief Get the max term frequency for the given section.
     *
     * @param section
     * @return std::size_t
     */
    std::size_t getMaxTF(std::string const & section) const;

    /**
     * @brief Get the entire feature map
     *
     * @return base::DocFeatureMap const&
     */
    base::FeatureMap const & getFeatureMap() const;

    /**
     * @brief Get a vector of `featureMap.keys`.
     *
     * @return std::vector<base::FeatureNames> const&
     */
    std::vector<base::FeatureKey> getFeatureKeys() const &;

    /**
     * @brief Get the value of the given feature.
     *
     * @param fName
     * @return FValType const&
     */
    base::FValType const & getFeatureValue(
        base::FeatureKey const & fKey) const;

    /**
     * @brief Get a vector of the feature values.
     *
     */
    std::vector<base::FValType> const getFeatureVector() const;

    /* Setters */
    /***********/

    /**
     * @brief Create or update a feature in the `featureMap`.
     *
     * @param fKey
     * @param fValue
     */
    void updateFeature(
        base::FeatureKey const & fKey, base::FValType const & fValue);

private:
    /* Private member variables */
    /****************************/

    base::StrUintMap docLenMaps;

    base::StructuredTermFrequencyMap termFrequencyMaps;
    base::StrUintMap maxTermMaps;

    base::FeatureMap featureMap;

    /* Private class methods */
    /*************************/

    /**
     * @brief Fill the "full" sections based on other existing sections.
     *  Assigns docLenMap["full"], termFrequencyMap["full"],
     * maxTermMap["full"].
     *
     */
    void fillFullFromOthers();
};

}  // namespace lowletorfeats
