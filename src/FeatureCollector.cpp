#include <lowletorfeats/base/utillf.hpp>

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
    std::vector<base::FeatureNames> keyVect =
        this->docVect.at(0).getFeatureNames();

    // Clear all feature maps
    this->clearFeatureMaps();

    // Collect featuers from key vector
    this->collectFeatures(keyVect);
}


void FeatureCollector::collectFeatures(base::FeatureNames fName)
{
    switch (fName)
    {
        /* Other */

        case base::FeatureNames::dl:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        /* TF/IDF */

        case base::FeatureNames::tflognorm:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::tfdoublenorm:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::idfdefault:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::idfsmooth:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::idfmax:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::idfprob:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::idfnorm:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::tfidf:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        /* Okapi */

        case base::FeatureNames::bm25:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::bm25plus:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        /* LMIR */

        case base::FeatureNames::abs:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::dir:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        case base::FeatureNames::jm:
        {
            for (auto & doc : docVect)
            {
                double const val = 0;

                doc.updateFeature(fName, val);
            }
            break;
        }

        default:  // Do nothing or feature not supported
            break;
    }
}


void FeatureCollector::collectFeatures(
    std::vector<base::FeatureNames> fNameVect
)
{
    for (auto const & fName : fNameVect)
        this->collectFeatures(fName);
}

/* Private class methods */

}
