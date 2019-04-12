#pragma once

#include "stdllf.hpp"
#include "Utillf.hpp"


namespace lowletorfeats
{

class StructuredDocument
{
public:
    /* Public member variables */

    /* Constructors */

    // Preanalyzed
    StructuredDocument(  // The indicated section only
        uint const & docLen,
        base::StrUintMap const & fullTermFrequencyMap,
        std::string const & sectionKey
    );
    StructuredDocument(  // `"full"` section only
        uint const & docLen,
        base::StrUintMap const & fullTermFrequencyMap
    );
    StructuredDocument(  // One or more sections
        base::StrUintMap const & docLenMap,
        base::StructuredTermFrequencyMap const & structuredTermFrequencyMap
    );

    /* Public class methods */

    /* Getter methods */

    /**
     * @brief Get the document length for the full document.
     *
     * @return uint const&
     */
    uint const & getDocLen() const
    { return this->docLenMaps.at("full"); }

    uint const & getDocLen(std::string const & section) const
    { return this->docLenMaps.at(section); }

    /**
     * @brief Get the entire structured term frequency map.
     *
     * @return std::unordered_map<std::string, base::TermFrequencyMap> const&
     */
    base::StructuredTermFrequencyMap const &
        getStructuredTermFrequencyMap() const
    { return this->termFrequencyMaps; }

    /**
     * @brief Get the `TermFrequencyMap` for the full document.
     *
     * @return base::TermFrequencyMap const&
     */
    base::StrUintMap const & getTermFrequencyMap() const
    { return this->termFrequencyMaps.at("full"); }

    /**
     * @brief Get the `TermFrequencyMap` for the given section.
     *
     * @param section
     * @return base::TermFrequencyMap const&
     */
    base::StrUintMap const & getTermFrequencyMap(
        std::string const & section
    ) const
    { return this->termFrequencyMaps.at(section); }

    /**
     * @brief Get the max term frequency for the full document.
     *
     * @return uint const&
     */
    uint const & getMaxTF() const
    { return this->maxTermMaps.at("full"); }

    /**
     * @brief Get the max term frequency for the given section.
     *
     * @param section
     * @return uint const&
     */
    uint const & getMaxTF(
        std::string const & section
    ) const
    { return this->maxTermMaps.at(section); }

    /**
     * @brief Get the entire feature map
     *
     * @return base::DocFeatureMap const&
     */
    base::FeatureMap const & getFeatureMap() const
    { return this->featureMap; }

    /**
     * @brief Get a vector of `featureMap.keys`.
     *
     * @return std::vector<base::FeatureNames> const&
     */
    std::vector<base::FeatureKey> getFeatureKeys() const
    { return base::Utillf::getKeyVect(this->featureMap); }

    /**
     * @brief Get the value of the given feature.
     *
     * @param fName
     * @return double const&
     */
    double const & getFeatureValue(base::FeatureKey const & fName) const
    { return this->featureMap.at(fName); }


    /* Setters */

    /**
     * @brief Create or update a feature in the `featureMap`.
     *
     * @param fKey
     * @param fValue
     */
    void updateFeature(base::FeatureKey const & fKey, double const & fValue)
    { this->featureMap[fKey] = fValue; }

private:
    /* Private member variables */
    base::StrUintMap docLenMaps;

    base::StructuredTermFrequencyMap termFrequencyMaps;
    base::StrUintMap maxTermMaps;

    base::FeatureMap featureMap;

    /* Private class methods */
    void clear();
    void clearSection(std::string const & section);
    void clearFeatureMap();
    void fillFullFromOthers();
};

}
