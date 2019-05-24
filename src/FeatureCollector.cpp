#include <cassert>
#include <iomanip>
#include <lowletorfeats/FeatureCollector.hpp>
#include <lowletorfeats/LMIR.hpp>
#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/utils.hpp>
#include <textalyzer/utils.hpp>

namespace lowletorfeats
{
/* Constructors */

/**
 * @brief Construct an empty Feature Collector.
 *
 */
FeatureCollector::FeatureCollector() {}

/**
 * @brief Construct a new Feature Collector from raw full text documents.
 *
 * @param docTextMapVect Multiple structured documents of raw text.
 * @param queryText Raw unanalyzed query string.
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrStrMap> const & docTextMapVect,
    std::string const & queryText)
{
    // Query text
    this->queryTfMap = textalyzer::asFrequencyMap(
        FeatureCollector::analyzerFun(
            queryText, FeatureCollector::DEFAULT_NGRAMS)
            .first);
    // Initialize documents
    this->initDocs(docTextMapVect);
}

/**
 * @brief Construct a new Feature Collector from raw full text documents.
 *
 * @param docTextMapVect Multiple structured documents of raw text.
 * @param queryTfMap Preanalyzed query string.
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrStrMap> const & docTextMapVect,
    base::StrUintMap const & queryTfMap)
{
    // Query text
    this->queryTfMap = queryTfMap;
    // Initialize documents
    this->initDocs(docTextMapVect);
}

/**
 * @brief Construct a new Feature Collector from preanalyzed structured docs.
 *
 * @param docLenMapVect Multiple structured documents with their length for
 *  each section.
 * @param docTfMapVect Multiple structured documents with analyzed tokens for
 *  each section.
 * @param queryText Raw unanalyzed query string.
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrUintMap> const & docLenMapVect,
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
    std::string const & queryText)
{
    // Analyze query text
    this->queryTfMap = textalyzer::asFrequencyMap(
        FeatureCollector::analyzerFun(
            queryText, FeatureCollector::DEFAULT_NGRAMS)
            .first);
    // Initialize documents
    this->initDocs(docLenMapVect, docTfMapVect);
}

/**
 * @brief Construct a new Feature Collector from preanalyzed structured docs.
 *
 * @param docLenMapVect Multiple structured documents with their length for
 *  each section.
 * @param docTfMapVect Multiple structured documentds with analyzed tokens for
 *  each section.
 * @param queryTfMap Preanalyzed query string.
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrUintMap> const & docLenMapVect,
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
    base::StrUintMap const & queryTfMap)
{
    // Query text
    this->queryTfMap = queryTfMap;
    // Initialize documents
    this->initDocs(docLenMapVect, docTfMapVect);
}

/* Public class methods */

/**
 * @brief Get a string representation of the `FeatureCollector`.
 *  This is not intended to be optimized.
 *
 * @return std::string
 */
std::string FeatureCollector::toString() const
{
    std::string outStr = "";

    outStr += "----------------\n";
    outStr += "FeatureCollector\n";
    outStr += "----------------\n";
    outStr += "Number of Documents: " + std::to_string(this->numDocs) + '\n';

    outStr += "Avg Section Lengths:";
    for (auto const & [sectionKey, sectionVal] : this->avgDocLenPerSection)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);
    outStr += '\n';

    outStr += "Total Section Terms:";
    for (auto const & [sectionKey, sectionVal] : this->nTermsPerSection)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);
    outStr += '\n';

    outStr += '\n';
    outStr += "Document Feature Maps:\n";
    outStr += "----------------------\n";
    for (auto const & doc : this->docVect) outStr += doc.toString() + '\n';

    return outStr;
}

std::string FeatureCollector::getFeatureString() const
{
    if (this->numDocs <= 0) return "";

    std::string outStr = "";

    // Construct header
    outStr += "Feature Vectors\n";

    auto const featKeys = this->docVect.at(0).getFeatureKeys();
    for (auto const & fKey : featKeys) outStr += "|" + fKey.toString();
    outStr += "\n";

    // Per document features
    for (auto const & doc : this->docVect)
    {
        auto const & fMap = doc.getFeatureMap();

        for (auto const & fKey : featKeys)
            outStr += "|" + std::to_string(fMap.at(fKey));
        outStr += "\n";
    }

    outStr += "\n";
    return outStr;
}

void FeatureCollector::collectPresetFeatures()
{
    this->clearFeatureMaps();

    std::vector<base::FeatureKey> static const PRESET_FEATURES = {
        base::FeatureKey("tfidf", "tfdoublenorm", "body"),
        base::FeatureKey("tfidf", "tfdoublenorm", "anchor"),
        base::FeatureKey("tfidf", "tfdoublenorm", "title"),
        base::FeatureKey("tfidf", "tfdoublenorm", "url"),
        base::FeatureKey("tfidf", "tfdoublenorm", "full"),
        base::FeatureKey("tfidf", "idfdefault", "body"),
        base::FeatureKey("tfidf", "idfdefault", "anchor"),
        base::FeatureKey("tfidf", "idfdefault", "title"),
        base::FeatureKey("tfidf", "idfdefault", "url"),
        base::FeatureKey("tfidf", "idfdefault", "full"),
        base::FeatureKey("tfidf", "tfidf", "body"),
        base::FeatureKey("tfidf", "tfidf", "anchor"),
        base::FeatureKey("tfidf", "tfidf", "title"),
        base::FeatureKey("tfidf", "tfidf", "url"),
        base::FeatureKey("tfidf", "tfidf", "full"),
        base::FeatureKey("other", "dl", "body"),
        base::FeatureKey("other", "dl", "anchor"),
        base::FeatureKey("other", "dl", "title"),
        base::FeatureKey("other", "dl", "url"),
        base::FeatureKey("other", "dl", "full"),
        base::FeatureKey("okapi", "bm25", "body"),
        base::FeatureKey("okapi", "bm25", "anchor"),
        base::FeatureKey("okapi", "bm25", "title"),
        base::FeatureKey("okapi", "bm25", "url"),
        base::FeatureKey("okapi", "bm25", "full"),
        base::FeatureKey("lmir", "abs", "body"),
        base::FeatureKey("lmir", "abs", "anchor"),
        base::FeatureKey("lmir", "abs", "title"),
        base::FeatureKey("lmir", "abs", "url"),
        base::FeatureKey("lmir", "abs", "full"),
        base::FeatureKey("lmir", "dir", "body"),
        base::FeatureKey("lmir", "dir", "anchor"),
        base::FeatureKey("lmir", "dir", "title"),
        base::FeatureKey("lmir", "dir", "url"),
        base::FeatureKey("lmir", "dir", "full"),
        base::FeatureKey("lmir", "jm", "body"),
        base::FeatureKey("lmir", "jm", "anchor"),
        base::FeatureKey("lmir", "jm", "title"),
        base::FeatureKey("lmir", "jm", "url"),
        base::FeatureKey("lmir", "jm", "full")};

    this->collectFeatures(PRESET_FEATURES);
}

void FeatureCollector::reCollectFeatures()
{
    try
    {
        // Get vector of keys
        std::vector<base::FeatureKey> keyVect =
            this->docVect.at(0).getFeatureKeys();

        if (keyVect.size() <= 0) return;  // No features to collect

        // Clear all feature maps
        this->clearFeatureMaps();

        // Collect featuers from key vector
        this->collectFeatures(keyVect);
    }
    catch (std::out_of_range const & e)  // docVect.size() == 0
    {
    }  // Do nothing (no features to collect)
}

/**
 * @brief Conduct feature collection for the given feature.
 *
 * @param fKey
 */
void FeatureCollector::collectFeatures(base::FeatureKey const & fKey)
{
    // QOL typedefs
    typedef base::FeatureKey::ValidTypes VTypes;
    typedef base::FeatureKey::ValidNames VNames;

    std::string const & fSection = fKey.getFSection();
    // Handle non-existent section
    if (this->sectionKeys.count(fSection) == 0)
    {
        // throw std::out_of_range("Invalid section key '" + fSection + "'");
        for (auto & doc : this->docVect) doc.updateFeature(fKey, 0);
        return;
    }

    switch (fKey.getVType())
    {
        case VTypes::other:
        {
            switch (fKey.getVName())
            {
                case VNames::dl:
                {
                    for (auto & doc : this->docVect)
                        doc.updateFeature(fKey, doc.getDocLen(fSection));
                    break;
                }

                default:
                    FeatureCollector::throwUnsupportedFeatureName(
                        fKey.getFName());
                    break;
            }
            break;
        }

        case VTypes::tfidf:
        {
            auto const & totalTerms = this->nTermsPerSection.at(fSection);

            switch (fKey.getVName())
            {
                case VNames::tflognorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap = doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Tfidf::sumTfLogNorm(tfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::tfdoublenorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap = doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal =
                            Tfidf::sumTfDoubleNorm(tfMap, doc.getMaxTF());
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::idfdefault:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal =
                            Tfidf::idfDefault(this->numDocs, totalTerms);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::idfsmooth:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal =
                            Tfidf::idfSmooth(this->numDocs, totalTerms);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::idfmax:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal =
                            Tfidf::idfMax(totalTerms, doc.getMaxTF());
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::idfprob:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal =
                            Tfidf::idfProb(this->numDocs, totalTerms);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::idfnorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal =
                            Tfidf::idfNorm(this->numDocs, totalTerms);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::tfidf:
                {
                    base::StrUintMap const & docsWithTermMap =
                        this->nDocsWithTermPerSection.at(fSection);

                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap = doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Tfidf::queryTfidf(
                            tfMap, doc.getMaxTF(), this->numDocs,
                            docsWithTermMap, this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                default:
                    FeatureCollector::throwUnsupportedFeatureName(
                        fKey.getFName());
                    break;
            }
            break;
        }

        case VTypes::okapi:
        {
            base::StrUintMap const & docsWithTermMap =
                this->nDocsWithTermPerSection.at(fSection);
            auto const & avgDocLen = this->avgDocLenPerSection.at(fSection);

            switch (fKey.getVName())
            {
                case VNames::invalid:
                    break;  // do nothing
                case VNames::bm25:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap = doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Okapi::queryBm25(
                            tfMap, this->numDocs, docsWithTermMap, avgDocLen,
                            this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::bm25plus:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap = doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Okapi::queryBm25plus(
                            tfMap, this->numDocs, docsWithTermMap, avgDocLen,
                            this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::bm25f:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Okapi::queryBm25f(
                            doc.getStructuredTermFrequencyMap(), this->numDocs,
                            this->nDocsWithTermPerSection,
                            this->avgDocLenPerSection, this->queryTfMap,
                            this->sectionWeights);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::bm25fplus:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Okapi::queryBm25fplus(
                            doc.getStructuredTermFrequencyMap(), this->numDocs,
                            this->nDocsWithTermPerSection,
                            this->avgDocLenPerSection, this->queryTfMap,
                            this->sectionWeights);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                default:
                    FeatureCollector::throwUnsupportedFeatureName(
                        fKey.getFName());
                    break;
            }
            break;
        }

        case VTypes::lmir:
        {
            this->constructLMIR(fSection);
            auto const & lime = this->lmirCalculators.at(fSection);

            switch (fKey.getVName())
            {
                case VNames::abs:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & docTfMap =
                            doc.getTermFrequencyMap(fSection);
                        auto const & docLen = doc.getDocLen();

                        base::FValType const fVal = lime.absolute_discount(
                            docTfMap, docLen, this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::dir:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & docTfMap =
                            doc.getTermFrequencyMap(fSection);
                        auto const & docLen = doc.getDocLen();

                        base::FValType const fVal =
                            lime.dirichlet(docTfMap, docLen, this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                case VNames::jm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & docTfMap =
                            doc.getTermFrequencyMap(fSection);
                        auto const & docLen = doc.getDocLen();

                        base::FValType const fVal = lime.jelinek_mercer(
                            docTfMap, docLen, this->queryTfMap);
                        doc.updateFeature(fKey, fVal);
                    }
                    break;
                }

                default:
                    FeatureCollector::throwUnsupportedFeatureName(
                        fKey.getFName());
                    break;
            }
            break;
        }

        default:
            FeatureCollector::throwUnsupportedFeatureType(fKey.getFName());
            break;
    }
}

/**
 * @brief Collect multiple features using a vector of `FeatureKey`s.
 *
 * @param fKeyVect
 */
void FeatureCollector::collectFeatures(
    std::vector<base::FeatureKey> const & fKeyVect)
{
    for (auto const & fKey : fKeyVect) this->collectFeatures(fKey);
}

/* Getter methods */

std::size_t FeatureCollector::getNumDocs() const { return this->numDocs; }

std::size_t FeatureCollector::getNumFeatures() const
{
    if (this->docVect.size() > 0)
    {
        auto doc = *docVect.begin();
        return doc.getFeatureMap().size();
    }
    return 0;
}

std::vector<StructuredDocument> const & FeatureCollector::getDocVect() const
{
    return this->docVect;
}

std::vector<std::vector<base::FValType>> const
    FeatureCollector::getFeatureVects() const
{
    std::vector<std::vector<base::FValType>> outVect;
    outVect.reserve(this->numDocs);

    for (auto const & doc : this->docVect)
        outVect.push_back(doc.getFeatureVector());

    return outVect;
}

/* Private static member variables */

/**
 * @brief Analyzer method for a string of text into pair<tokenStrVect, docLen>.
 *
 */
textalyzer::AnlyzerFunType<std::string> FeatureCollector::analyzerFun =
    textalyzer::Analyzer::medAnalyze;

uint8_t const FeatureCollector::DEFAULT_NGRAMS = 2;

/* Private class methods */

/**
 * @brief Construct the lmirCalculator if it is not already constructed.
 *
 */
void FeatureCollector::constructLMIR(std::string const & sectionKey)
{
    if (this->lmirCalculators.count(sectionKey) != 0)  // Already constructed
        return;

    // Else construct
    this->lmirCalculators[sectionKey] =
        LMIR(this->tfMapPerSection.at(sectionKey));
}

/**
 * @brief Add the given document to the docVect.
 *  TODO: Add protections so this can only be called from initDocs.
 *
 * @param newDoc
 */
void FeatureCollector::addDoc(StructuredDocument const & newDoc)
{
    // For each section,
    //  setup `nDocsWithTermPerSection` and `avgDocLenPerSection`
    for (auto const & [sectionKey, sectionTfMap] :
         newDoc.getStructuredTermFrequencyMap())
    {
        this->avgDocLenPerSection[sectionKey] += newDoc.getDocLen(sectionKey);
        this->initNDocsWithTermPerSection(sectionKey, sectionTfMap);
    }

    // Add the new document
    this->docVect.push_back(newDoc);
}

/**
 * @brief Create a new document in the docVect from a preanalyzed map.
 *
 * @param docLenMap
 * @param strucDocTfMap
 */
void FeatureCollector::addDoc(
    base::StrUintMap const & docLenMap,
    base::StructuredTermFrequencyMap const & strucDocTfMap)
{
    // Create a new document, ensures `full` sectionKey
    StructuredDocument newDoc(docLenMap, strucDocTfMap);

    // For each section,
    //  setup `nDocsWithTermPerSection` and `avgDocLenPerSection`
    for (auto const & [sectionKey, sectionTfMap] :
         newDoc.getStructuredTermFrequencyMap())
    {
        this->avgDocLenPerSection[sectionKey] += newDoc.getDocLen(sectionKey);
        this->initNDocsWithTermPerSection(sectionKey, sectionTfMap);
    }

    // Add the new document
    this->docVect.push_back(newDoc);
}

/**
 * @brief Initialize unanalyzed structured documents.
 *  TODO: Add protection so it can only be called from a constructor
 *
 * @param docTextMapVect
 */
void FeatureCollector::initDocs(
    std::vector<base::StrStrMap> const & docTextMapVect)
{
    // Number of documents
    this->numDocs = docTextMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (auto const & docTextMap : docTextMapVect)  // for each document
    {
        base::StrUintMap docLenMap;
        base::StructuredTermFrequencyMap structDocTfMap;

        // For each section
        for (auto const & [sectionKey, sectionText] : docTextMap)
        {
            // Analyze text for this document
            base::StrUintMap sectionTfMap;
            auto const & pair = FeatureCollector::analyzerFun(
                sectionText, FeatureCollector::DEFAULT_NGRAMS);
            sectionTfMap = textalyzer::asFrequencyMap(pair.first);
            docLenMap[sectionKey] = pair.second;

            // Filter for query tokens only
            sectionTfMap =
                utils::getIntersection(sectionTfMap, this->queryTfMap);

            // Add to `structDocTfMap`
            structDocTfMap[sectionKey] = sectionTfMap;
        }

        this->addDoc(docLenMap, structDocTfMap);
    }

    // Calculate avgDocLengths
    for (auto const & [sectionKey, sectionValue] : this->avgDocLenPerSection)
        this->avgDocLenPerSection.at(sectionKey) =
            sectionValue / this->numDocs;

    this->initNTermsPerSection();

    // Ensure everything was done right
    this->assertProperties();
}

/**
 * @brief Initialize preanalyzed structured documents.
 *
 * @param docLenMapVect
 * @param docTfMapVect
 */
void FeatureCollector::initDocs(
    std::vector<base::StrUintMap> const & docLenMapVect,
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect)
{
    // Set the number of documents
    this->numDocs = docTfMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (std::size_t docIdx = 0; docIdx < this->numDocs;
         ++docIdx)  // for each document
    {
        base::StrUintMap const & docLenMap = docLenMapVect.at(docIdx);
        base::StructuredTermFrequencyMap strucDocTfMap =
            docTfMapVect.at(docIdx);

        // For each section, setup docTfMap for the document
        for (auto const & [sectionKey, sectionTfMap] :
             strucDocTfMap)  // for each section
        {
            // Filter for query tokens only
            strucDocTfMap.at(sectionKey) =
                utils::getIntersection(sectionTfMap, queryTfMap);
        }

        this->addDoc(docLenMap, strucDocTfMap);
    }

    // Calculate avgDocLengths
    for (auto const & [sectionKey, sectionValue] : this->avgDocLenPerSection)
        this->avgDocLenPerSection.at(sectionKey) =
            sectionValue / this->numDocs;

    // Total collection terms for each section
    this->initNTermsPerSection();

    // Ensure everything was done right
    this->assertProperties();
}

/**
 * @brief Initialize the `nDocsWithTermPerSection` and `tfMapPerSection` class
 *  variables.
 *
 * @param sectionTfMap
 */
void FeatureCollector::initNDocsWithTermPerSection(
    std::string const & sectionKey, base::StrUintMap const & sectionTfMap)
{
    // Create the sectionKey key
    if (this->nDocsWithTermPerSection.count(sectionKey) == 0)
        this->nDocsWithTermPerSection[sectionKey] = base::StrUintMap();
    if (this->tfMapPerSection.count(sectionKey) == 0)
        this->tfMapPerSection[sectionKey] = base::StrUintMap();

    for (auto const & mapPair : sectionTfMap)
    {
        std::string termKey = mapPair.first;

        // Create the term count at 0
        if (this->nDocsWithTermPerSection.at(sectionKey).count(termKey) == 0)
            this->nDocsWithTermPerSection.at(sectionKey)[termKey] = 0;

        // Increment the term count
        this->nDocsWithTermPerSection.at(sectionKey).at(termKey)++;
        this->tfMapPerSection.at(sectionKey)[termKey] += mapPair.second;
    }
}

/**
 * @brief Calculate the total number of terms per section in the collection.
 *
 */
void FeatureCollector::initNTermsPerSection()
{
    // Fill the `nTermsPerSection`
    for (auto const & [sectionKey, sectionValue] :
         this->nDocsWithTermPerSection)
    {
        this->nTermsPerSection[sectionKey] = utils::mapValueSum(sectionValue);
    }
}

void FeatureCollector::initFullFromOthers() {}

/**
 * @brief Clear the feature maps of every document.
 *
 */
void FeatureCollector::clearFeatureMaps()
{
    for (auto & doc : this->docVect) doc.clearFeatureMap();
}

/**
 * @brief Assert required properties of the feature collector to ensure
 *  acceptable operations.
 *
 */
void FeatureCollector::assertProperties()
{
    // Assert same sectionKeys present in:
    //  `avgDocLenPerSection`, `nDocsWithTermPerSection`, `nTermsPerSection`
    this->sectionKeys = utils::getKeyUnorderedSet(this->avgDocLenPerSection);

    assert(
        this->sectionKeys ==
        utils::getKeyUnorderedSet(this->avgDocLenPerSection));
    assert(
        this->sectionKeys == utils::getKeyUnorderedSet(this->tfMapPerSection));
    assert(
        this->sectionKeys ==
        utils::getKeyUnorderedSet(this->nDocsWithTermPerSection));
    assert(
        this->sectionKeys ==
        utils::getKeyUnorderedSet(this->nTermsPerSection));
}

/* Private static class methods */

void FeatureCollector::throwUnsupportedFeatureType(std::string const & fType)
{
    throw std::runtime_error("Unsupported feature type '" + fType + "'");
}

void FeatureCollector::throwUnsupportedFeatureName(std::string const & fName)
{
    throw std::runtime_error("Unsupported feature name '" + fName + "'");
}

}  // namespace lowletorfeats
