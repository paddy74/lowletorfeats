#include <lowletorfeats/base/utils.hpp>

#include <lowletorfeats/FeatureCollector.hpp>

#include <lowletorfeats/Tfidf.hpp>
#include <lowletorfeats/Okapi.hpp>
#include <lowletorfeats/LMIR.hpp>


namespace lowletorfeats
{

/* Constructors */



/* Public member functions */

/**
 * @brief Split a string on a delimiter. TODO: Better performance (vector bad)
 *
 * @param str
 * @param delim
 * @return std::vector<std::string>
 */
std::vector<std::string> strSplit(std::string const & str, char const & delim)
{
    std::vector<std::string> out;

    size_t start;
    size_t end = 0;

    while ( (start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}


void FeatureCollector::runFeatureCollection()
{
    this->resetFeatureMap();

    for (auto const & featureName : this->PRESET_FEATURES)
    {

    }
}


void FeatureCollector::collectFeature(base::FeatureNames fName)
{
    for (int i = 0; i < this->numDocs; ++i)
    {
        collectFeature(fName, i);
    }

}


/* Private class methods */

void FeatureCollector::collectFeature(
    base::FeatureNames fName,
    std::size_t docIndex
)
{
    base::DocFeatureMap & singleFeatureMap = this->featureMapVect[docIndex];
    base::TermFrequencyMap const & docTFMap =
        this->docTFVector[docIndex];

    switch (fName)
    {
        /* Other */

        case base::FeatureNames::dl:
        {
            std::string const key = "tfidf.dl";
            double const val = base::mapValueSum(docTFMap);

            singleFeatureMap[key] = val;
            break;
        }

        /* TF/IDF */

        case base::FeatureNames::tflognorm:
        {
            std::string const key = "tfidf.tflognorm";
            double const val = Tfidf::queryTfLogNorm(docTFMap);

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::tfdoublenorm:
        {
            std::string const key = "tfidf.tfdoublenorm";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::idfdefault:
        {
            std::string const key = "tfidf.idfdefault";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::idfsmooth:
        {
            std::string const key = "tfidf.idfsmooth";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::idfmax:
        {
            std::string const key = "tfidf.idfmax";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::idfprob:
        {
            std::string const key = "tfidf.idfprob";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::idfnorm:
        {
            std::string const key = "tfidf.idfnorm";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::tfidf:
        {
            std::string const key = "tfidf.tfidf";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        /* Okapi */

        case base::FeatureNames::bm25:
        {
            std::string const key = "okapi.bm25";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::bm25plus:
        {
            std::string const key = "okapi.bm25plus";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        /* LMIR */

        case base::FeatureNames::abs:
        {
            std::string const key = "lmir.abs";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::dir:
        {
            std::string const key = "lmir.dir";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        case base::FeatureNames::jm:
        {
            std::string const key = "lmir.jm";
            double const val = 0;

            singleFeatureMap[key] = val;
            break;
        }

        default:  // Do nothing or feature not supported
            break;
    }
}


void FeatureCollector::resetFeatureMap()
{
    this->featureMapVect.clear();
    this->featureMapVect.reserve(this->numDocs);
}

}
