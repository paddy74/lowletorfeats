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
 * @param docTextMapVect
 * @param queryText
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrStrMap> const & docTextMapVect,
    std::string const & queryText
)
{
    this->numDocs = docTextMapVect.size();

    // Initialize every document
    this->docVect.reserve(this->numDocs);
    for (int i = 0; i < this->numDocs; ++i)
    {
        StructuredDocument newDoc(docTextMapVect.at(i));
        docVect.push_back(newDoc);
    }

    // Additional info
    calcAvgDocLengths();
    createDocsWithTermMap();

    // Query text
    //Analyzer::fullAnalyzeToTfMap(queryText);

    // Ensure everything was done right
    this->assertProperties();
}


/**
 * @brief Construct a new Feature Collector from raw full text documents with
 *  a query id.
 *
 * @param docTextMapVect
 * @param queryText
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
 * @param docLenMapVect
 * @param docTfMapVect
 * @param queryText
 */
FeatureCollector::FeatureCollector(
    std::vector<base::StrUintMap> const & docLenMapVect,
    std::vector<base::StructuredTermFrequencyMap> const & docTfMapVect,
    std::string const & queryText
)
{
    this->numDocs = docTfMapVect.size();

    // Initialize every document
    this->docVect.reserve(this->numDocs);
    for (int i = 0; i < this->numDocs; ++i)
    {
        StructuredDocument newDoc(docLenMapVect.at(i), docTfMapVect.at(i));
        docVect.push_back(newDoc);
    }

    // Additional info
    calcAvgDocLengths();
    createDocsWithTermMap();

    // Query text
    //Analyzer::fullAnalyzeToTfMap(queryText);

    // Ensure everything was done right
    this->assertProperties();
}


/**
 * @brief Construct a new Feature Collector from preanalyzed structured docs
 *  with a query id.
 *
 * @param docLenMapVect
 * @param docTfMapVect
 * @param queryText
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

                    break;

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
                    /* code */
                    break;

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
                    /* code */
                    break;

                case VNames::bm25plus:
                    break;

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
                    /* code */
                    break;

                case VNames::dir:
                    /* code */
                    break;

                case VNames::jm:
                    /* code */
                    break;

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
