#pragma once

#include <lowletorfeats/base/stdDef.hpp>

#include <vector>


namespace lowletorfeats
{

class StructuredDocument
{
public:
    /* Public member variables */

    /* Constructors */

    StructuredDocument();

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

    // Copy constructor

    StructuredDocument(StructuredDocument const & other);


    /* Public class methods */

    std::string toString() const;

    void clear();
    void clearSection(std::string const & section);
    void clearFeatureMap();


    /* Getter methods */


    std::size_t getDocLen() const;
    std::size_t getDocLen(std::string const & section) const;

    base::StructuredTermFrequencyMap const &
        getStructuredTermFrequencyMap() const;

    base::StrUintMap const & getTermFrequencyMap() const;

    base::StrUintMap const & getTermFrequencyMap(
        std::string const & section
    ) const;

    std::size_t getMaxTF() const;

    std::size_t getMaxTF(
        std::string const & section
    ) const;

    base::FeatureMap const & getFeatureMap() const;

    std::vector<base::FeatureKey> getFeatureKeys() const &;

    base::FValType const &
        getFeatureValue(base::FeatureKey const & fName) const;


    /* Setters */

    void updateFeature(
        base::FeatureKey const & fKey, base::FValType const & fValue);

private:
    /* Private member variables */

    base::StrUintMap docLenMaps;

    base::StructuredTermFrequencyMap termFrequencyMaps;
    base::StrUintMap maxTermMaps;

    base::FeatureMap featureMap;


    /* Private class methods */

    void fillFullFromOthers();
};

}
