#include <lowletorfeats/base/Document.hpp>
#include <lowletorfeats/utils.hpp>

namespace lowletorfeats
{
/* Constructors */

StructuredDocument::StructuredDocument() {}

StructuredDocument::StructuredDocument(
    std::size_t const & docLen, base::StrSizeMap const & fullTermFrequencyMap,
    std::string const & sectionKey)
{
    this->docLenMaps[sectionKey] = docLen;
    this->termFrequencyMaps[sectionKey] = fullTermFrequencyMap;
    this->maxTermMaps[sectionKey] =
        utils::findMaxValuePair(fullTermFrequencyMap).second;
}

StructuredDocument::StructuredDocument(
    std::size_t const & docLen, base::StrSizeMap const & fullTermFrequencyMap)
    : StructuredDocument::StructuredDocument(
          docLen, fullTermFrequencyMap, "full")
{
}

StructuredDocument::StructuredDocument(
    base::StrSizeMap const & docLenMap,
    base::StructuredTermFrequencyMap const & structuredTermFrequencyMap)
{
    this->docLenMaps = docLenMap;
    this->termFrequencyMaps = structuredTermFrequencyMap;

    // Fill maxTermMap
    for (auto const & [sectionKey, tfMap] : this->termFrequencyMaps)
    {
        this->maxTermMaps[sectionKey] = utils::findMaxValuePair(tfMap).second;
    }

    // Ensure "full" exists, else populate
    if (this->termFrequencyMaps.count("full") == 0) this->fillFullFromOthers();
}

StructuredDocument::StructuredDocument(StructuredDocument const & other)
{
    this->docLenMaps = other.docLenMaps;
    this->termFrequencyMaps = other.termFrequencyMaps;
    this->maxTermMaps = other.maxTermMaps;
    this->featureMap = other.featureMap;
}

/* Public class methods */

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
        outStr += "\n\t" + fKey.getFType() + "\t" + fKey.getFName() + "\t" +
                  fKey.getFSection() + "\t: " + std::to_string(fVal);
    }

    outStr += '\n';
    return outStr;
}

void StructuredDocument::clear()
{
    this->docLenMaps.clear();
    this->termFrequencyMaps.clear();
    this->maxTermMaps.clear();
}

void StructuredDocument::clearSection(std::string const & section)
{
    this->docLenMaps.erase(section);
    this->termFrequencyMaps.erase(section);
    this->maxTermMaps.erase(section);
}

void StructuredDocument::clearFeatureMap() { this->featureMap.clear(); }

/* Getter methods */

std::size_t StructuredDocument::getDocLen() const
{
    return this->docLenMaps.at("full");
}

std::size_t StructuredDocument::getDocLen(std::string const & section) const
{
    return this->docLenMaps.at(section);
}

base::StructuredTermFrequencyMap const &
    StructuredDocument::getStructuredTermFrequencyMap() const
{
    return this->termFrequencyMaps;
}

base::StrSizeMap const & StructuredDocument::getTermFrequencyMap() const
{
    return this->termFrequencyMaps.at("full");
}

base::StrSizeMap const & StructuredDocument::getTermFrequencyMap(
    std::string const & section) const
{
    return this->termFrequencyMaps.at(section);
}

std::size_t StructuredDocument::getMaxTF() const
{
    return this->maxTermMaps.at("full");
}

std::size_t StructuredDocument::getMaxTF(std::string const & section) const
{
    return this->maxTermMaps.at(section);
}

base::FeatureMap const & StructuredDocument::getFeatureMap() const
{
    return this->featureMap;
}

std::vector<base::FeatureKey> StructuredDocument::getFeatureKeys() const &
{
    return utils::getKeyVect(this->featureMap);
}

base::FValType const & StructuredDocument::getFeatureValue(
    base::FeatureKey const & fKey) const
{
    return this->featureMap.at(fKey);
}

std::vector<base::FValType> const StructuredDocument::getFeatureVector() const
{
    return utils::getValueVect(this->featureMap);
}

/* Setters */

void StructuredDocument::updateFeature(
    base::FeatureKey const & fKey, base::FValType const & fValue)
{
    this->featureMap[fKey] = fValue;
}

/* Private class methods */

void StructuredDocument::fillFullFromOthers()
{
    // Erase contents of section "full"
    this->clearSection("full");

    // Calculate `docLenMap["full"]`
    this->docLenMaps["full"] = utils::mapValueSum(this->docLenMaps);

    // Calculate `termFrequencyMap["full"]`
    base::StrSizeMap fullTermFreqMap;
    for (auto const & mapPair : this->termFrequencyMaps)
        utils::additiveMergeInplace(fullTermFreqMap, mapPair.second);
    this->termFrequencyMaps["full"] = fullTermFreqMap;

    // Calculate `maxTermMap["full"]`
    this->maxTermMaps["full"] =
        utils::findMaxValuePair(fullTermFreqMap).second;
}

}  // namespace lowletorfeats
