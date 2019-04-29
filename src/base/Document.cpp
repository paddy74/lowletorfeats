#include <lowletorfeats/base/Document.hpp>

#include <lowletorfeats/base/Utillf.hpp>


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
        base::Utillf::findMaxValuePair(fullTermFrequencyMap).second;
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
            base::Utillf::findMaxValuePair(tfMap).second;
    }

    // Ensure "full" exists, else populate
    try
    {
        auto const & _ = this->termFrequencyMaps.at("full");
    }
    catch(std::out_of_range const & e)
    {
        this->fillFullFromOthers();
    }
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
    this->docLenMaps["full"] = base::Utillf::mapValueSum(this->docLenMaps);

    // Calculate `termFrequencyMap["full"]`
    base::StrUintMap fullTermFreqMap;
    for (auto const & [section, tfMap] : this->termFrequencyMaps)
        base::Utillf::additiveMergeInplace(fullTermFreqMap, tfMap);
    this->termFrequencyMaps["full"] = fullTermFreqMap;

    // Calculate `maxTermMap["full"]`
    this->maxTermMaps["full"] =
        base::Utillf::findMaxValuePair(fullTermFreqMap).second;
}

}
