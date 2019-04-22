#include <lowletorfeats/FeatureCollector.hpp>

#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/LMIR.hpp>

#include <textalyzer/Analyzer.hpp>


namespace lowletorfeats
{

/* Constructors */

/**
 * @brief Construct a new Feature Collector from raw full text documents.
 *
 * @param docTextMapVect Multiple structured documents of raw text.
 * @param queryText
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrStrMap> const & docTextMapVect,
    std::string const & queryText
)
{
    // Query text
    this->queryTfMap =
        base::Utillf::asFrequencyMap(
            FeatureCollector::analyzerFun(queryText).first
        );

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
                FeatureCollector::analyzerFun(queryText);
            sectionTfMap = base::Utillf::asFrequencyMap(pair.first);
            docLenMap[sectionKey] = pair.second;

            // Filter for query tokens only
            sectionTfMap = base::Utillf::getIntersection(
                sectionTfMap, this->queryTfMap);

            // Add to `StructDocTfMap`
            structDocTfMap[sectionKey] = sectionTfMap;

            // Sum in avgDocLengths
            this->avgDocLenMap[sectionKey] += pair.second;

            // `structDocsWithTermMap`
            for (auto const & [term, tf] : sectionTfMap)
                this->structDocsWithTermMap[sectionKey][term]++;
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
 * @brief Construct a new Feature Collector from raw full text documents with
 *  a query id.
 *
 * @param docTextMapVect Multiple structured documents of raw text.
 * @param queryText Raw unanalyzed query string.
 * @param queryId
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrStrMap> const & docTextMapVect,
    std::string const & queryText,
    std::string const & queryId
)
: FeatureCollector::FeatureCollector(docTextMapVect, queryText)
{ this->queryId = queryId; }


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
        base::Utillf::asFrequencyMap(
            FeatureCollector::analyzerFun(queryText).first
        );

    // Set the number of documents
    this->numDocs = docTfMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (int i = 0; i < this->numDocs; ++i)  // for each document
    {  // TODO: Iterate
        base::StrUintMap const & docLenMap = docLenMapVect.at(i);
        base::StructuredTermFrequencyMap docTfMap = docTfMapVect.at(i);

        for (auto const & [sectionKey, sectionTfMap] : docTfMap)  // for each section
        {
            // Filter for query tokens only
            docTfMap.at(sectionKey) = base::Utillf::getIntersection(
                sectionTfMap, queryTfMap
            );

            // Sum in avgDocLengths
            this->avgDocLenMap[sectionKey] += docLenMap.at(sectionKey);

            // `structDocsWithTermMap`
            for (auto const & [term, tf] : sectionTfMap)
                this->structDocsWithTermMap[sectionKey][term]++;
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
 * @brief Construct a new Feature Collector from preanalyzed structured docs
 *  with a query id.
 *
 * @param docLenMapVect Multiple structured documents with their length for
 *  each section.
 * @param docTfMapVect Multiple structured documents with analyzed tokens for
 *  each section.
 * @param queryText Raw unanalyzed query string.
 * @param queryId
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrUintMap> const & docLenMapVect,
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
    std::string const & queryText,
    std::string const & queryId
)
: FeatureCollector::FeatureCollector(docLenMapVect, docTfMapVect, queryText)
{ this->queryId = queryId; }


/* Public class methods */

void FeatureCollector::collectPresetFeatures()
{
    this->collectFeatures(this->PRESET_FEATURES);
}


void FeatureCollector::reCollectFeatures()
{
    // Get vector of keys
    std::vector<base::FeatureKey> keyVect =
        this->docVect.at(0).getFeatureKeys();

    // Clear all feature maps
    this->clearFeatureMaps();

    // Collect featuers from key vector
    this->collectFeatures(keyVect);
}


void FeatureCollector::collectFeatures(base::FeatureKey const & fKey)
{
    typedef base::FeatureKey::ValidTypes VTypes;
    typedef base::FeatureKey::ValidNames VNames;
    typedef base::FeatureKey::ValidSections VSections;

    std::string const & fSection = fKey.getFSection();
    auto const & docsWithTermMap = this->structDocsWithTermMap.at(fSection);
    uint const & avgDocLen = this->avgDocLenMap.at(fSection);
    uint const & totalTerms = this->totalTermsMap.at(fSection);


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
                            fKey, doc.getDocLen(fKey.getFSection()));
                    }
                }

                default:
                    break;
            }
            break;
        }

        case VTypes::tfidf:
        {
            switch (fKey.getVName())
            {
                case VNames::tflognorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fKey.getFSection());

                        double const fVal = Tfidf::sumTfLogNorm(tfMap);
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfdoublenorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fKey.getFSection());

                        double const fVal = Tfidf::sumTfDoubleNorm(
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
                        double const fVal = Tfidf::idfDefault(
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
                        double const fVal = Tfidf::idfSmooth(
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
                        double const fVal = Tfidf::idfMax(
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
                        double const fVal = Tfidf::idfProb(
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
                        double const fVal = Tfidf::idfNorm(
                            this->numDocs,
                            totalTerms
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfidf:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fKey.getFSection());

                        double const fVal = Tfidf::queryTfidf(
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
            }
            break;
        }

        case VTypes::okapi:
        {
            switch (fKey.getVName())
            {
                case VNames::bm25:
                {
                    for (auto & doc : this->docVect)
                    {
                        auto const & tfMap =
                            doc.getTermFrequencyMap(fKey.getFSection());

                        double const fVal = Okapi::queryBm25(
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
                            doc.getTermFrequencyMap(fKey.getFSection());

                        double const fVal = Okapi::queryBm25plus(
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
                        double const fVal = Okapi::queryBm25f(
                            doc.getStructuredTermFrequencyMap(),
                            this->numDocs,
                            this->structDocsWithTermMap,
                            this->avgDocLenMap,
                            this->queryTfMap,
                            this->sectionWeights
                        );
                        doc.updateFeature(fKey, fVal);
                    }
                }

                case VNames::bm25fplus:
                {
                    for (auto & doc : this->docVect)
                    {
                        double const fVal = Okapi::queryBm25fplus(
                            doc.getStructuredTermFrequencyMap(),
                            this->numDocs,
                            this->structDocsWithTermMap,
                            this->avgDocLenMap,
                            this->queryTfMap,
                            this->sectionWeights
                        );
                        doc.updateFeature(fKey, fVal);
                    }
                }

                default:
                    break;
            }
            break;
        }

        case VTypes::lmir:
        {
            switch (fKey.getVName())
            {
                case VNames::abs:
                {
                    for (auto & doc : this->docVect)
                    {
                        // TODO:
                    } break;
                }

                case VNames::dir:
                {
                    for (auto & doc : this->docVect)
                    {
                        // TODO:
                    } break;
                }

                case VNames::jm:
                {
                    for (auto & doc : this->docVect)
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


void FeatureCollector::collectFeatures(
    std::vector<base::FeatureKey> const & fKeyVect
)
{
    for (auto const & fKey : fKeyVect)
        this->collectFeatures(fKey);
}


/* Private member variables */

std::vector<base::FeatureKey> const FeatureCollector::PRESET_FEATURES =
{
    base::FeatureKey("other", "dl", "full"),
    base::FeatureKey("tfidf", "tfdoublenorm", "full"),
    base::FeatureKey("tfidf", "idfdefault", "full"),
    base::FeatureKey("tfidf", "tfidf", "full"),
    base::FeatureKey("okapi", "bm25", "full"),
    base::FeatureKey("lmir", "abs", "full"),
    base::FeatureKey("lmir", "dir", "full"),
    base::FeatureKey("lmir", "jm", "full")
};


/**
 * @brief Analyzer method for a string of text into pair<tokenStrVect, docLen>.
 *
 */
std::function<std::pair<std::vector<std::string>, std::size_t>(std::string)>
    FeatureCollector::analyzerFun = textalyzer::Analyzer::simpleAnalyze;


/* Private class methods */

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
            base::Utillf::mapValueSum(sectionValue);
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

void FeatureCollector::assertProperties()
{
    // Assert same sections present in:
    //  `avgDocLenMap`, `structDocsWithTermMap`, `totalTermsMap`
    auto fullKeyVector =
        base::Utillf::getKeyVect(this->avgDocLenMap);
    fullKeyVector = base::Utillf::getIntersection(
        fullKeyVector, base::Utillf::getKeyVect(this->structDocsWithTermMap));
    fullKeyVector = base::Utillf::getIntersection(
        fullKeyVector, base::Utillf::getKeyVect(this->totalTermsMap));

    for (auto const & sectionKey : fullKeyVector)
    {
        avgDocLenMap.at(sectionKey);
        structDocsWithTermMap.at(sectionKey);
        totalTermsMap.at(sectionKey);
    }
}

}
