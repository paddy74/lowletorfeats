#include <lowletorfeats/FeatureCollector.hpp>

#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/LMIR.hpp>


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
    base::StrUintMap queryTfMap;
    queryTfMap = FeatureCollector::anlyzToTfMap(queryText);

    // Number of documents
    this->numDocs = docTextMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (auto const & docTextMap : docTextMapVect)
    {
        base::StrUintMap docLenMap;
        base::StructuredTermFrequencyMap StructDocTfMap;
        for (auto const & [sectionKey, sectionText] : docTextMap)
        {
            // Analyze text for this document
            base::StrUintMap sectionTfMap;
            auto const & pair =
                FeatureCollector::anlyzToTfMapLenPair(sectionText);
            sectionTfMap = pair.first;
            docLenMap[sectionKey] = pair.second;

            // Filter for query tokens only
            sectionTfMap = base::Utillf::getIntersection(sectionTfMap, queryTfMap);

            // Add to `StructDocTfMap`
            StructDocTfMap[sectionKey] = sectionTfMap;
        }

        // Create a new document
        StructuredDocument newDoc(docLenMap, StructDocTfMap);
        docVect.push_back(newDoc);
    }

    // Additional info
    calcAvgDocLengths();
    createDocsWithTermMap();

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
    // Query text
    base::StrUintMap queryTfMap;
    queryTfMap = FeatureCollector::anlyzToTfMap(queryText);

    // Number of document
    this->numDocs = docTfMapVect.size();

    // Initialize every document, filtering with `queryTfMap`
    this->docVect.reserve(this->numDocs);
    for (int i = 0; i < this->numDocs; ++i)
    {
        auto const & docLenMap = docLenMapVect.at(i);
        auto docTfMap = docTfMapVect.at(i);

        for (auto & [sectionKey, sectionTfMap] : docTfMap)
        {
            docTfMap[sectionKey] = base::Utillf::getIntersection(
                sectionTfMap, queryTfMap
            );
        }

        // Create a new document
        StructuredDocument newDoc(docLenMap, docTfMap);
        docVect.push_back(newDoc);
    }

    // Additional info
    calcAvgDocLengths();
    createDocsWithTermMap();

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


/* Private class methods */

/**
 * @brief Calculate the average document length for each section.
 *
 */
void FeatureCollector::calcAvgDocLengths()
{
    // TODO:
}


/**
 * @brief Calculate the number of documents containing each term and the total
 *  terms map.
 *
 */
void FeatureCollector::createDocsWithTermMap()
{
    // TODO:

    // Fill the `totalTermsMap`
    for (auto const & [sectionKey, sectionValue] : this->structDocsWithTermMap)
    {
        this->totalTermsMap[sectionKey] =
            base::Utillf::mapValueSum(sectionValue);
    }
}

}
