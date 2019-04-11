#include <lowletorfeats/base/FeatureKey.hpp>
#include <lowletorfeats/base/Utillf.hpp>

#include <cassert>
#include <algorithm>


namespace lowletorfeats::base
{

/* Constructors */

FeatureKey::FeatureKey(std::string const & fKey)
{
    auto const & fDelim = base::Utillf::strSplit(fKey, '.');

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


FeatureKey::FeatureKey(
    std::string const & fType,
    std::string const & fName,
    std::string const & fSection
)
{
    this->fType = fType;
    this->fName = fName;
    this->fSection = fSection;

    this->isValid();
}


/* Public class methods */

std::string FeatureKey::toString() const
{ return fType + '.' + fName + '.' +fSection; }


/* Public operators */


/* Public friend methods */

bool operator== (FeatureKey const & fKey1, FeatureKey const & fKey2)
{ return (std::hash<FeatureKey>()(fKey1) == std::hash<FeatureKey>()(fKey2)); }

bool operator!= (FeatureKey const & fKey1, FeatureKey const & fKey2)
{ return !(fKey1 == fKey2); }

/* Private member variables */

std::vector<std::string> const FeatureKey::validTypes
{
    "other",
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
