#include <lowletorfeats/base/Utillf.hpp>
#include <lowletorfeats/base/FeatureKey.hpp>


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

    this->vType = FeatureKey::inverseValidTypeMap.at(this->fType);
    //this->vName = FeatureKey::inverseValidNameMap.at(this->fName);
    //this->vSection = FeatureKey::inverseValidSectionMap.at(this->fSection);
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
}


/* Public class methods */

std::string FeatureKey::toString() const
{ return fType + '.' + fName + '.' +fSection; }

std::size_t FeatureKey::toHash() const
{
    return (
        (std::hash<std::string>()(this->fType))
        ^ (std::hash<std::string>()(this->fName))
        ^ (std::hash<std::string>()(this->fSection))
    );
}


/* Public operators */


/* Public friend methods */

bool operator== (FeatureKey const & fKey1, FeatureKey const & fKey2)
{ return (std::hash<FeatureKey>()(fKey1) == std::hash<FeatureKey>()(fKey2)); }

bool operator!= (FeatureKey const & fKey1, FeatureKey const & fKey2)
{ return !(fKey1 == fKey2); }

/* Private member variables */

std::unordered_map<FeatureKey::ValidTypes, std::string>
    const FeatureKey::validTypeMap
{
    { FeatureKey::ValidTypes::other, "tfidf" },
    { FeatureKey::ValidTypes::tfidf, "tfidf" },
    { FeatureKey::ValidTypes::okapi, "okapi" },
    { FeatureKey::ValidTypes::lmir, "lmir" }
};

std::unordered_map<std::string, FeatureKey::ValidTypes>
    const FeatureKey::inverseValidTypeMap
{
    { "other", FeatureKey::ValidTypes::other },
    { "tfidf", FeatureKey::ValidTypes::tfidf },
    { "okapi", FeatureKey::ValidTypes::okapi },
    { "lmir", FeatureKey::ValidTypes::lmir}
};


std::unordered_map<FeatureKey::ValidNames, std::string>
    const FeatureKey::validNameMap
{
    // Other
    { FeatureKey::ValidNames::dl, "dl"},

    // TF/IDF
    { FeatureKey::ValidNames::tflognorm, "tflognorm" },
    { FeatureKey::ValidNames::tfdoublenorm, "tfdoublenorm" },
    { FeatureKey::ValidNames::idfdefault, "idfdefault" },
    { FeatureKey::ValidNames::idfmax, "idfmax" },
    { FeatureKey::ValidNames::idfprob, "idfprob" },
    { FeatureKey::ValidNames::idfnorm, "idfnorm" },
    { FeatureKey::ValidNames::tfidf, "tfidf" },

    // Okapi
    { FeatureKey::ValidNames::bm25, "bm25" },
    { FeatureKey::ValidNames::bm25plus, "bm25plus" },

    // LMIR
    { FeatureKey::ValidNames::abs, "abs" },
    { FeatureKey::ValidNames::dir, "dir" },
    { FeatureKey::ValidNames::jm, "jm" }
};

std::unordered_map<std::string, FeatureKey::ValidNames>
    const FeatureKey::inverseValidNameMap =
{
    // Other
    { "dl", FeatureKey::ValidNames::dl },

    // TF/IDF
    { "tflognorm", FeatureKey::ValidNames::tflognorm },
    { "tfdoubleNorm", FeatureKey::ValidNames::tfdoublenorm },
    { "idfdefault", FeatureKey::ValidNames::idfdefault },
    { "idfmax", FeatureKey::ValidNames::idfmax },
    { "idfprob", FeatureKey::ValidNames::idfprob },
    { "idfnorm", FeatureKey::ValidNames::idfnorm },

    // Okapi
    { "bm25", FeatureKey::ValidNames::bm25 },
    { "bm25plus", FeatureKey::ValidNames::bm25plus },

    // LMIR
    { "abs", FeatureKey::ValidNames::abs },
    { "dir", FeatureKey::ValidNames::dir },
    { "jm", FeatureKey::ValidNames::jm }
};


std::unordered_map<FeatureKey::ValidSections, std::string>
    const FeatureKey::validSectionMap
{
    { FeatureKey::ValidSections::full, "full" },
    { FeatureKey::ValidSections::body, "body" },
    { FeatureKey::ValidSections::anchor, "anchor" },
    { FeatureKey::ValidSections::title, "title" },
    { FeatureKey::ValidSections::url, "url" }
};

std::unordered_map<std::string, FeatureKey::ValidSections>
    const FeatureKey::inverseValidSectionMap
{
    { "full", FeatureKey::ValidSections::full },
    { "body", FeatureKey::ValidSections::body },
    { "anchor", FeatureKey::ValidSections::anchor },
    { "url", FeatureKey::ValidSections::url }
};

}
