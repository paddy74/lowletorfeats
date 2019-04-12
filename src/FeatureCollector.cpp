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
    //queryTfMap = Analyzer::fullAnalyzeToTfMap(queryText);

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
            //auto pair = Analyzer::fullAnalyzeToTfMap(sectionText, true)  // TODO:
            //sectionTfMap = pair.first;
            //docLenMap[sectionKey] = pair.second;

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
    //queryTfMap = Analyzer::fullAnalyzeToTfMap(queryText);

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
                        double const fVal = Tfidf::sumTfLogNorm(
                            doc.getTermFrequencyMap(fKey.getFSection())
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfdoublenorm:
                {
                    for (auto & doc : this->docVect)
                    {
                        double const fVal = Tfidf::sumTfDoubleNorm(
                            doc.getTermFrequencyMap(fKey.getFSection()),
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
                            base::Utillf::mapValueSum(this->docsWithTermMap)
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
                            base::Utillf::mapValueSum(this->docsWithTermMap)
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::idfmax:
                {
                    for (auto & doc : this->docVect)
                    {
                        double const fVal = Tfidf::idfMax(
                            base::Utillf::mapValueSum(this->docsWithTermMap),
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
                            base::Utillf::mapValueSum(this->docsWithTermMap)
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
                            base::Utillf::mapValueSum(this->docsWithTermMap)
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::tfidf:
                {
                    for (auto & doc : this->docVect)
                    {
                        double const fVal = Tfidf::queryTfidf(
                            doc.getTermFrequencyMap(fKey.getFSection),
                            doc.getMaxTF(),
                            this->numDocs,
                            this->docsWithTermMap,
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
                        double const fVal = Okapi::queryBm25(
                            doc.getTermFrequencyMap(fKey.getFSection()),
                            this->numDocs,
                            this->docsWithTermMap,
                            this->avgDocLenMap[fKey.getFSection()],
                            this->queryTfMap
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::bm25plus:
                {
                    for (auto & doc : this->docVect)
                    {
                        double const fVal = Okapi::queryBm25plus(
                            doc.getTermFrequencyMap(fKey.getFSection()),
                            this->numDocs,
                            this->docsWithTermMap,
                            this->avgDocLenMap[fKey.getFSection()],
                            this->queryTfMap
                        );
                        doc.updateFeature(fKey, fVal);
                    } break;
                }

                case VNames::bm25f:
                {
                    for (auto & doc : this->docVect)
                    {
                        for (auto const & [sectionKey, sectionTfMap]
                            : doc.getStructuredTermFrequencyMap())
                        {
                            double const fVal = Okapi::queryBm25(
                                sectionTfMap,
                                this->numDocs,
                                this->docsWithTermMap,
                                this->avgDocLenMap[sectionKey],
                                this->queryTfMap
                            );
                            doc.updateFeature(fKey, fVal);
                        }

                        // TODO: weighted BM25F
                    }
                }

                case VNames::bm25fplus:
                {
                    for (auto & doc : this->docVect)
                    {
                        for (auto const & [sectionKey, sectionTfMap]
                            : doc.getStructuredTermFrequencyMap())
                        {
                            double const fVal = Okapi::queryBm25plus(
                                sectionTfMap,
                                this->numDocs,
                                this->docsWithTermMap,
                                this->avgDocLenMap[sectionKey],
                                this->queryTfMap
                            );
                            doc.updateFeature(fKey, fVal);
                        }

                        // TODO: weighted BM25F+
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

}
