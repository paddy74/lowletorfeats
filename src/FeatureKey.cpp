#include "FeatureKey.hpp"

#include <cassert>
#include <algorithm>


namespace lowletorfeats
{

/* Constructors */

FeatureKey::FeatureKey(std::string const & fKey)
{
    auto const & fDelim = base::strSplit(fKey, '.');

    this->fType = fDelim.at(0);
    this->fName = fDelim.at(1);

    try
    {
        this->fSection = fDelim.at(3);
    }
    catch(std::out_of_range const & e)
    {
        this->fSection = "full";
    }

    this->isValid();
}

/* Public class methods */

std::string FeatureKey::toString() const
{ return fType + '.' + fName + '.' +fSection; }

/* Private member variables */

std::vector<std::string> const FeatureKey::validTypes
{
    "tfidf",
    "okapi",
    "lmir"
};

std::vector<std::string> const FeatureKey::validNames
{
    // TF/IDF
    "tflognorm", "tfdoublenorm",
    "idfdefault", "idfsmooth", "idfmax", "idfprob", "idfnorm",
    "tfidf",

    // Okapi
    "bm25", "bm25plus",

    // LMIR
    "abs", "dir", "jm"
};

std::vector<std::string> const FeatureKey::validSections
{
    "full",
    "body",
    "anchor",
    "title",
    "url"
};

/* Private class methods */

void FeatureKey::isValid() const
{
    assert(std::binary_search(validTypes.begin(), validTypes.end(),
        this->fType));
    assert(std::binary_search(validNames.begin(), validNames.end(),
        this->fName));
    assert(std::binary_search(validSections.begin(), validSections.end(),
        this->fSection));
}

}
