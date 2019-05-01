#include <lowletorfeats/FeatureCollector.hpp>

#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/LMIR.hpp>

#include <lowletorfeats/utils.hpp>

#include <textalyzer/utils.hpp>

#include <cassert>


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
    std::string const & queryText
)
{
    // Query text
    this->queryTfMap = textalyzer::asFrequencyMap(
        FeatureCollector::analyzerFun(
            queryText, FeatureCollector::DEFAULT_NGRAMS).first
        );
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
    base::StrUintMap const & queryTfMap
)
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
    std::string const & queryText
)
{
    // Analyze query text
    this->queryTfMap =
        textalyzer::asFrequencyMap(
            FeatureCollector::analyzerFun(
                queryText, FeatureCollector::DEFAULT_NGRAMS).first
        );
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
    base::StrUintMap const & queryTfMap
)
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
    for (auto const & [sectionKey, sectionVal] : this->avgDocLenMap)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);
    outStr += '\n';

    outStr += "Total Section Terms:";
    for (auto const & [sectionKey, sectionVal] : this->totalTermsMap)
        outStr += "\n\t" + sectionKey + ":" + std::to_string(sectionVal);
    outStr += '\n';

    outStr += '\n';
    outStr += "Document Feature Maps:\n";
    outStr += "----------------------\n";
    for (auto const & doc : this->docVect)
        outStr += doc.toString() + '\n';

    return outStr;
}


void FeatureCollector::collectPresetFeatures()
{
    this->clearFeatureMaps();
    this->collectFeatures(this->PRESET_FEATURES);
}


void FeatureCollector::reCollectFeatures()
{
    try
    {
        // Get vector of keys
        std::vector<base::FeatureKey> keyVect =
            this->docVect.at(0).getFeatureKeys();

        if (keyVect.size() <= 0)
            return;  // No features to collect

        // Clear all feature maps
        this->clearFeatureMaps();

        // Collect featuers from key vector
        this->collectFeatures(keyVect);
    }
    catch(std::out_of_range const & e)  // docVect.size() == 0
    { }  // Do nothing (no features to collect)
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

    switch (fKey.getVType())
    {
        case VTypes::other:
        {
            switch (fKey.getVName())
            {
                case VNames::dl:
                {
                    for (auto & doc : this->docVect)
                    {
                        doc.updateFeature(
                            fKey, doc.getDocLen(fSection));
                    }
                }

                default:
                    break;
            } break;
        }

        case VTypes::tfidf:
        {
            auto const & totalTerms = this->totalTermsMap.at(fSection);

            switch (fKey.getVName())
            {
                case VNames::tflognorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Tfidf::sumTfLogNorm(tfMap);
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfdoublenorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Tfidf::sumTfDoubleNorm(
                            tfMap,
                            doc.getMaxTF()
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfdefault:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Tfidf::idfDefault(
                            this->numDocs,
                            totalTerms
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfsmooth:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Tfidf::idfSmooth(
                            this->numDocs,
                            totalTerms
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfmax:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Tfidf::idfMax(
                            totalTerms,
                            doc.getMaxTF()
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfprob:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Tfidf::idfProb(
                            this->numDocs,
                            totalTerms
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfnorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Tfidf::idfNorm(
                            this->numDocs,
                            totalTerms
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfidf:
                {
                    base::StrUintMap const & docsWithTermMap =
                        this->structDocsWithTermMap.at(fSection);

                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Tfidf::queryTfidf(
                            tfMap,
                            doc.getMaxTF(),
                            this->numDocs,
                            docsWithTermMap,
                            this->queryTfMap
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                default:
                    break;
            } break;
        }

        case VTypes::okapi:
        {
            base::StrUintMap const & docsWithTermMap =
                this->structDocsWithTermMap.at(fSection);
            auto const & avgDocLen = this->avgDocLenMap.at(fSection);

            switch (fKey.getVName())
            {
                case VNames::invalid:
                    break;  // do nothing
                case VNames::bm25:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Okapi::queryBm25(
                            tfMap,
                            this->numDocs,
                            docsWithTermMap,
                            avgDocLen,
                            this->queryTfMap
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::bm25plus:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fSection);

                        base::FValType const fVal = Okapi::queryBm25plus(
                            tfMap,
                            this->numDocs,
                            docsWithTermMap,
                            avgDocLen,
                            this->queryTfMap
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::bm25f:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Okapi::queryBm25f(
                            doc.getStructuredTermFrequencyMap(),
                            this->numDocs,
                            this->structDocsWithTermMap,
                            this->avgDocLenMap,
                            this->queryTfMap,
                            this->sectionWeights
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::bm25fplus:
                {
                    for (auto & doc : this->docVect)
                    {
                        base::FValType const fVal = Okapi::queryBm25fplus(
                            doc.getStructuredTermFrequencyMap(),
                            this->numDocs,
                            this->structDocsWithTermMap,
                            this->avgDocLenMap,
                            this->queryTfMap,
                            this->sectionWeights
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                default:
                    break;
            } break;
        }

        case VTypes::lmir:
        {
            switch (fKey.getVName())
            {
                case VNames::abs:
                {
                    //for (auto & doc : this->docVect)
                    {
                        // TODO:
                    } break;
                }

                case VNames::dir:
                {
                    //for (auto & doc : this->docVect)
                    {
                        // TODO:
                    } break;
                }

                case VNames::jm:
                {
                    //for (auto & doc : this->docVect)
                    {
                        // TODO:
                    } break;
                }

                default:
                    break;
            }
            break;
        }

        default:
            break;
    }
}


/**
 * @brief Collect each feature of the given feature key vector.
 *
 * @param fKeyVect
 */
void FeatureCollector::collectFeatures(
    std::vector<base::FeatureKey> const & fKeyVect
)
{
    for (auto const & fKey : fKeyVect)
        this->collectFeatures(fKey);
}


/* Private static member variables */

/**
 * @brief Analyzer method for a string of text into pair<tokenStrVect, docLen>.
 *
 */
textalyzer::AnlyzerFunType<std::string>
    FeatureCollector::analyzerFun = textalyzer::Analyzer::lowAnalyze;

uint8_t const FeatureCollector::DEFAULT_NGRAMS = 2;


/* Private class methods */

/**
 * @brief Initialize unanalyzed structured documents.
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
        for (auto const & [sectionKey, sectionText] : docTextMap)
        {
            // Analyze text for this document
            base::StrUintMap sectionTfMap;
            auto const & pair =
                FeatureCollector::analyzerFun(
                    sectionText, FeatureCollector::DEFAULT_NGRAMS);
            sectionTfMap = textalyzer::asFrequencyMap(pair.first);
            docLenMap[sectionKey] = pair.second;

            // Filter for query tokens only
            sectionTfMap = utils::getIntersection(
                sectionTfMap, this->queryTfMap);

            // Add to `StructDocTfMap`
            structDocTfMap[sectionKey] = sectionTfMap;

            // Sum in avgDocLengths
            this->avgDocLenMap[sectionKey] += pair.second;

            // `structDocsWithTermMap`
            for (auto const & mapPair : sectionTfMap)
                this->structDocsWithTermMap[sectionKey][mapPair.first]++;
        }

        // Create a new document
        StructuredDocument newDoc(docLenMap, structDocTfMap);
        this->docVect.push_back(newDoc);
    }

    // Calculate avgDocLengths
    for (auto const & [sectionKey, sectionValue] : this->avgDocLenMap)
        this->avgDocLenMap.at(sectionKey) = sectionValue / this->numDocs;

    this->sumTotalTermsPerSection();

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
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect
)
{
    // Set the number of documents
    this->numDocs = docTfMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (std::size_t i = 0; i < this->numDocs; ++i)  // for each document
    {
        base::StrUintMap const & docLenMap = docLenMapVect.at(i);
        base::StructuredTermFrequencyMap docTfMap = docTfMapVect.at(i);

        for (auto const & [sectionKey, sectionTfMap] : docTfMap)  // for each section
        {
            // Filter for query tokens only
            docTfMap.at(sectionKey) = utils::getIntersection(
                sectionTfMap, queryTfMap
            );

            // Sum in avgDocLengths
            this->avgDocLenMap[sectionKey] += docLenMap.at(sectionKey);

            // `structDocsWithTermMap`
            for (auto const & mapPair : sectionTfMap)
                this->structDocsWithTermMap[sectionKey][mapPair.first]++;
        }

        // Create a new document
        StructuredDocument newDoc(docLenMap, docTfMap);
        this->docVect.push_back(newDoc);
    }

    // Calculate avgDocLengths
    for (auto const & [sectionKey, sectionValue] : this->avgDocLenMap)
        this->avgDocLenMap.at(sectionKey) = sectionValue / this->numDocs;

    this->sumTotalTermsPerSection();

    // Ensure everything was done right
    this->assertProperties();
}


/**
 * @brief Calculate the total number of terms per section.
 *
 */
void FeatureCollector::sumTotalTermsPerSection()
{
    // Fill the `totalTermsMap`
    for (auto const & [sectionKey, sectionValue] : this->structDocsWithTermMap)
    {
        this->totalTermsMap[sectionKey] =
            utils::mapValueSum(sectionValue);
    }
}


/**
 * @brief Clear the feature maps of every document.
 *
 */
void FeatureCollector::clearFeatureMaps()
{
    for (auto & doc : this->docVect)
        doc.clearFeatureMap();
}


/**
 * @brief Assert required properties of the feature collector to ensure
 *  acceptable operations.
 *
 */
void FeatureCollector::assertProperties()
{
    // Assert same sections present in:
    //  `avgDocLenMap`, `structDocsWithTermMap`, `totalTermsMap`
    auto sectionKeys =
        utils::getKeyVect(this->avgDocLenMap);
    assert(sectionKeys ==
        utils::getKeyVect(this->structDocsWithTermMap));
    assert(sectionKeys == utils::getKeyVect(this->totalTermsMap));
}

}
