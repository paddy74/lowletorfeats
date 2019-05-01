#include <lowletorfeats/base/Document.hpp>

#include <lowletorfeats/utils.hpp>


namespace lowletorfeats
{

/* Constructors */

StructuredDocument::StructuredDocument() {}


/**
 * @brief Construct a new Structured Document object using a preanalyzed
 *  document length and `TermFrequencyMap` for the full document text.
 *
 * @param docLen The full document's length.
 * @param fullTermFrequencyMap Preanalyzed `TermFrequencyMap` for the full doc.
 */
StructuredDocument::StructuredDocument(
    uint const & docLen,
    base::StrUintMap const & fullTermFrequencyMap,
    std::string const & sectionKey
)
{
    this->docLenMaps[sectionKey] = docLen;
    this->termFrequencyMaps[sectionKey] = fullTermFrequencyMap;
    this->maxTermMaps[sectionKey] =
        utils::findMaxValuePair(fullTermFrequencyMap).second;
}


/**
 * @brief Construct a new Structured Document object using a preanalyzed
 *  document length and `TermFrequencyMap` for the full document text.
 *
 * @param docLen The full document's length.
 * @param fullTermFrequencyMap Preanalyzed `TermFrequencyMap` for the full doc.
 */
StructuredDocument::StructuredDocument(
    uint const & docLen,
    base::StrUintMap const & fullTermFrequencyMap
) : StructuredDocument::StructuredDocument(
        docLen, fullTermFrequencyMap, "full") {}


/**
 * @brief Construct a new Structured Document object using a preanalyzed
 *  document length map and `TermFrequencyMap`.
 *
 * @param docLenMap The document lengths for each structured section.
 * @param structuredTermFrequencyMap Preanalyzed `TermFrequencyMap`s for each
 *  structured section.
 */
StructuredDocument::StructuredDocument(
    base::StrUintMap const & docLenMap,
    base::StructuredTermFrequencyMap const & structuredTermFrequencyMap
)
{
    this->docLenMaps = docLenMap;
    this->termFrequencyMaps = structuredTermFrequencyMap;

    // Fill maxTermMap
    for (auto const & [sectionKey, tfMap]: this->termFrequencyMaps)
    {
        this->maxTermMaps[sectionKey] =
            utils::findMaxValuePair(tfMap).second;
    }

    // Ensure "full" exists, else populate
    if (!(this->termFrequencyMaps.count("full")))
        this->fillFullFromOthers();
}


/**
 * @brief Copy constructor.
 *
 * @param other
 */
StructuredDocument::StructuredDocument(StructuredDocument const & other)
{
    this->docLenMaps = other.docLenMaps;
    this->termFrequencyMaps = other.termFrequencyMaps;
    this->maxTermMaps = other.maxTermMaps;
    this->featureMap = other.featureMap;
}


/* Public class methods */

/**
 * @brief Get a string representation of the `StructuredDocument`.
 *  This is not intended to be optimized.
 *
 * @return std::string
 */
std::string StructuredDocument::toString() const
{
    std::string outStr = "";

    outStr += "Document Section Lengths:";
    for (auto const & [sectionKey, sectionVal] : this->docLenMaps)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);

    outStr += "\nMax Section Terms:";
    for (auto const & [sectionKey, sectionVal] : this->maxTermMaps)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);

    outStr += "\nFeature Map:";
    for (auto const & [fKey, fVal] : this->featureMap)
    {
        outStr += "\n\t" + fKey.getFType()
            + "\t" + fKey.getFName()
            + "\t" + fKey.getFSection()
            + "\t: " + std::to_string(fVal);
    }

    outStr += '\n';
    return outStr;
}

/**
 * @brief Clear all sections from the document.
 *
 */
void StructuredDocument::clear()
{
    this->docLenMaps.clear();
    this->termFrequencyMaps.clear();
    this->maxTermMaps.clear();
}

/**
 * @brief Removes the indicated section from the document.
 *
 * @param section
 */
void StructuredDocument::clearSection(std::string const & section)
{
    this->docLenMaps.erase(section);
    this->termFrequencyMaps.erase(section);
    this->maxTermMaps.erase(section);
}


/**
 * @brief Clear the document's feature map.
 *
 */
void StructuredDocument::clearFeatureMap()
{
    this->featureMap.clear();
}


/* Getter methods */

/**
 * @brief Get the document length for the full document.
 *
 * @return std::size_t
 */
std::size_t StructuredDocument::getDocLen() const
{ return this->docLenMaps.at("full"); }


/**
 * @brief Get the document length for the document.
 *
 * @param section
 * @return std::size_t const&
 */
std::size_t StructuredDocument::getDocLen(std::string const & section) const
{ return this->docLenMaps.at(section); }


/**
 * @brief Get the entire structured term frequency map.
 *
 * @return std::unordered_map<std::string, base::TermFrequencyMap> const&
 */
base::StructuredTermFrequencyMap const &
    StructuredDocument::getStructuredTermFrequencyMap() const
{ return this->termFrequencyMaps; }


/**
 * @brief Get the `TermFrequencyMap` for the full document.
 *
 * @return base::TermFrequencyMap const&
 */
base::StrUintMap const & StructuredDocument::getTermFrequencyMap() const
{ return this->termFrequencyMaps.at("full"); }


/**
 * @brief Get the `TermFrequencyMap` for the given section.
 *
 * @param section
 * @return base::TermFrequencyMap const&
 */
base::StrUintMap const & StructuredDocument::getTermFrequencyMap(
    std::string const & section
) const
{ return this->termFrequencyMaps.at(section); }


/**
 * @brief Get the max term frequency for the full document.
 *
 * @return std::size_t
 */
std::size_t StructuredDocument::getMaxTF() const
{ return this->maxTermMaps.at("full"); }


/**
 * @brief Get the max term frequency for the given section.
 *
 * @param section
 * @return std::size_t
 */
std::size_t StructuredDocument::getMaxTF(
    std::string const & section
) const
{ return this->maxTermMaps.at(section); }


/**
 * @brief Get the entire feature map
 *
 * @return base::DocFeatureMap const&
 */
base::FeatureMap const & StructuredDocument::getFeatureMap() const
{ return this->featureMap; }


/**
 * @brief Get a vector of `featureMap.keys`.
 *
 * @return std::vector<base::FeatureNames> const&
 */
std::vector<base::FeatureKey> StructuredDocument::getFeatureKeys() const &
{ return utils::getKeyVect(this->featureMap); }


/**
 * @brief Get the value of the given feature.
 *
 * @param fName
 * @return FValType const&
 */
base::FValType const & StructuredDocument::getFeatureValue(
    base::FeatureKey const & fName) const
{ return this->featureMap.at(fName); }


/* Setters */

/**
 * @brief Create or update a feature in the `featureMap`.
 *
 * @param fKey
 * @param fValue
 */
void StructuredDocument::updateFeature(
    base::FeatureKey const & fKey, base::FValType const & fValue)
{ this->featureMap[fKey] = fValue; }


/* Private class methods */

/**
 * @brief Fill the "full" sections based on other existing sections.
 *  Assigns docLenMap["full"], termFrequencyMap["full"], maxTermMap["full"].
 *
 */
void StructuredDocument::fillFullFromOthers()
{
    // Erase contents of section "full"
    this->clearSection("full");

    // Calculate `docLenMap["full"]`
    this->docLenMaps["full"] = utils::mapValueSum(this->docLenMaps);

    // Calculate `termFrequencyMap["full"]`
    base::StrUintMap fullTermFreqMap;
    for (auto const & mapPair : this->termFrequencyMaps)
        utils::additiveMergeInplace(fullTermFreqMap, mapPair.second);
    this->termFrequencyMaps["full"] = fullTermFreqMap;

    // Calculate `maxTermMap["full"]`
    this->maxTermMaps["full"] =
        utils::findMaxValuePair(fullTermFreqMap).second;
}

}
