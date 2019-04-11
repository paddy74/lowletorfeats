#include <lowletorfeats/base/Document.hpp>

#include <lowletorfeats/base/Utillf.hpp>


namespace lowletorfeats
{

/* Constructors */

/**
 * @brief Construct a new Structured Document object using the raw text of the
 *  full document.
 *  Assigns docLenMap["full"], termFrequencyMap["full"], maxTermMap["full"]
 *
 * @param fullText The raw text string for the full document.
 */
StructuredDocument::StructuredDocument(std::string const & fullText)
{
    //std::vector<std::string> textTokens = tokenize(fullText);
    //this->docLen["full"] = textTokens.size();

    // N-grams, word embeddings, etc.
    //analyze(textTokens);

    // Token vector to map
    //mapTermFreq(textTokens);

    // Assign to map
}


/**
 * @brief Construct a new Structured Document object using the raw text of each
 *  structured section of the document.
 *  Assigns docLenMap, termFrequencyMap, maxTermMap
 *
 * @param textMap Raw text for each structured section of the document.
 */
StructuredDocument::StructuredDocument(base::StrStrMap const & textMap)
{
    for (auto const & [key, text] : textMap)
    {
        //this->termFrequencyMap[key] =
    }
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
)
{
    this->docLenMaps["full"] = docLen;
    this->termFrequencyMaps["full"] = fullTermFrequencyMap;
    this->maxTermMaps["full"] =
        base::Utillf::findMaxValuePair(fullTermFrequencyMap).second;
}


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
    for (auto const & [section, tfMap]: this->termFrequencyMaps)
        this->maxTermMaps[section] = base::Utillf::findMaxValuePair(tfMap).second;

    // Ensure "full" exists, else populate
    try
    {
        this->termFrequencyMaps.at("full");
    }
    catch(std::out_of_range const & e)
    {
        this->fillFullFromOthers();
    }
}


/* Private class methods */

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
