#include <lowletorfeats/base/FeatureKey.hpp>
#include <lowletorfeats/utils.hpp>
#include <vector>

namespace lowletorfeats::base
{
/* Constructors */

/**
 * @brief Construct a new Feature Key with "invalid" values.
 *
 */
FeatureKey::FeatureKey()
{
    this->fType = "invalid";
    this->fName = "invalid";
    this->fSection = "invalid";

    this->vType = FeatureKey::ValidTypes::invalid;
    this->vName = FeatureKey::ValidNames::invalid;
    this->vSection = FeatureKey::ValidSections::invalid;
}

/**
 * @brief Construct a new Feature Key from a string "type.name.section".
 *
 * @param fKeyStr A string representation of the `FeatureKey` in the form
 *  "type.name.section".
 */
FeatureKey::FeatureKey(std::string const & fKeyStr)
{
    std::vector<std::string> const & fDelim = utils::strSplit(fKeyStr, '.');

    switch (fDelim.size())
    {
        case 2:
        {
            this->fType = fDelim.at(0);
            this->fName = fDelim.at(1);
            this->fSection = "full";
            break;
        }

        case 3:
        {
            this->fType = fDelim.at(0);
            this->fName = fDelim.at(1);
            this->fSection = fDelim.at(2);
            break;
        }

        default:
        {
            this->fType = "invalid";
            this->fName = "invalid";
            this->fSection = "invalid";
        }
    }

    this->initVKeys();
}

/**
 * @brief Construct a new Feature Key from multiple strings.
 *
 * @param fType
 * @param fName
 * @param fSection
 */
FeatureKey::FeatureKey(
    std::string const & fType, std::string const & fName,
    std::string const & fSection)
{
    this->fType = fType;
    this->fName = fName;
    this->fSection = fSection;

    this->initVKeys();
}

/**
 * @brief Copy constructor.
 *
 * @param other
 */
FeatureKey::FeatureKey(FeatureKey const & other)
{
    this->fType = other.fType;
    this->fName = other.fName;
    this->fSection = other.fSection;

    this->vType = other.vType;
    this->vName = other.vName;
    this->vSection = other.vSection;
}

/* Public class methods */

std::string FeatureKey::toString() const
{
    return fType + '.' + fName + '.' + fSection;
}

std::size_t FeatureKey::toHash() const
{
    return (
        (std::hash<std::string>()(this->fType)) ^
        (std::hash<std::string>()(this->fName)) ^
        (std::hash<std::string>()(this->fSection)));
}

/**
 * @brief Recreates the `FeatureKey` with the given key string.
 *
 * @param newKeyString Str for the new key in format :type.name.section".
 */
void FeatureKey::changeKey(std::string const & newKeyString)
{
    *(this) = FeatureKey(newKeyString);
}

/* Public operators */

/* Public friend methods */

bool operator==(FeatureKey const & fKey1, FeatureKey const & fKey2)
{
    return (std::hash<FeatureKey>()(fKey1) == std::hash<FeatureKey>()(fKey2));
}

bool operator!=(FeatureKey const & fKey1, FeatureKey const & fKey2)
{
    return !(fKey1 == fKey2);
}

/* Private static member variables */

std::unordered_map<FeatureKey::ValidTypes, std::string> const
    FeatureKey::validTypeMap{{FeatureKey::ValidTypes::invalid, "invalid"},
                             {FeatureKey::ValidTypes::other, "other"},
                             {FeatureKey::ValidTypes::tfidf, "tfidf"},
                             {FeatureKey::ValidTypes::okapi, "okapi"},
                             {FeatureKey::ValidTypes::lmir, "lmir"}};

std::unordered_map<std::string, FeatureKey::ValidTypes> const
    FeatureKey::inverseValidTypeMap{
        {"invalid", FeatureKey::ValidTypes::invalid},
        {"other", FeatureKey::ValidTypes::other},
        {"tfidf", FeatureKey::ValidTypes::tfidf},
        {"okapi", FeatureKey::ValidTypes::okapi},
        {"lmir", FeatureKey::ValidTypes::lmir}};

std::unordered_map<FeatureKey::ValidNames, std::string> const
    FeatureKey::validNameMap{
        {FeatureKey::ValidNames::invalid, "invalid"},

        // Other
        {FeatureKey::ValidNames::dl, "dl"},

        // TF/IDF
        {FeatureKey::ValidNames::tflognorm, "tflognorm"},
        {FeatureKey::ValidNames::tfdoublenorm, "tfdoublenorm"},
        {FeatureKey::ValidNames::idfdefault, "idfdefault"},
        {FeatureKey::ValidNames::idfmax, "idfmax"},
        {FeatureKey::ValidNames::idfprob, "idfprob"},
        {FeatureKey::ValidNames::idfnorm, "idfnorm"},
        {FeatureKey::ValidNames::tfidf, "tfidf"},

        // Okapi
        {FeatureKey::ValidNames::bm25, "bm25"},
        {FeatureKey::ValidNames::bm25plus, "bm25plus"},

        // LMIR
        {FeatureKey::ValidNames::abs, "abs"},
        {FeatureKey::ValidNames::dir, "dir"},
        {FeatureKey::ValidNames::jm, "jm"}};

std::unordered_map<std::string, FeatureKey::ValidNames> const
    FeatureKey::inverseValidNameMap = {
        {"invalid", FeatureKey::ValidNames::invalid},

        // Other
        {"dl", FeatureKey::ValidNames::dl},

        // TF/IDF
        {"tflognorm", FeatureKey::ValidNames::tflognorm},
        {"tfdoublenorm", FeatureKey::ValidNames::tfdoublenorm},
        {"idfdefault", FeatureKey::ValidNames::idfdefault},
        {"idfmax", FeatureKey::ValidNames::idfmax},
        {"idfprob", FeatureKey::ValidNames::idfprob},
        {"idfnorm", FeatureKey::ValidNames::idfnorm},
        {"tfidf", FeatureKey::ValidNames::tfidf},

        // Okapi
        {"bm25", FeatureKey::ValidNames::bm25},
        {"bm25plus", FeatureKey::ValidNames::bm25plus},
        {"bm25f", FeatureKey::ValidNames::bm25f},
        {"bm25fplus", FeatureKey::ValidNames::bm25fplus},

        // LMIR
        {"abs", FeatureKey::ValidNames::abs},
        {"dir", FeatureKey::ValidNames::dir},
        {"jm", FeatureKey::ValidNames::jm}};

std::unordered_map<FeatureKey::ValidSections, std::string> const
    FeatureKey::validSectionMap{
        {FeatureKey::ValidSections::invalid, "invalid"},
        {FeatureKey::ValidSections::full, "full"},
        {FeatureKey::ValidSections::body, "body"},
        {FeatureKey::ValidSections::anchor, "anchor"},
        {FeatureKey::ValidSections::title, "title"},
        {FeatureKey::ValidSections::url, "url"}};

std::unordered_map<std::string, FeatureKey::ValidSections> const
    FeatureKey::inverseValidSectionMap{
        {"invalid", FeatureKey::ValidSections::invalid},
        {"full", FeatureKey::ValidSections::full},
        {"body", FeatureKey::ValidSections::body},
        {"anchor", FeatureKey::ValidSections::anchor},
        {"title", FeatureKey::ValidSections::title},
        {"url", FeatureKey::ValidSections::url}};

/* Private class methods */

void FeatureKey::initVKeys()
{
    try
    {
        this->vType = FeatureKey::inverseValidTypeMap.at(this->fType);
        this->vName = FeatureKey::inverseValidNameMap.at(this->fName);
        this->vSection = FeatureKey::inverseValidSectionMap.at(this->fSection);
    }
    catch (std::out_of_range const & e)  // Invalid key name
    {
        std::string ewhat = "_Map_base::at, Invalid `FeatureKey`: ";

        if (FeatureKey::inverseValidTypeMap.count(this->fType) == 0)
            ewhat += "FeatureKey::ValidType::" + this->fType + " ";
        if (FeatureKey::inverseValidNameMap.count(this->fName) == 0)
            ewhat += "FeatureKey::ValidName::" + this->fName + " ";
        if (FeatureKey::inverseValidSectionMap.count(this->fSection) == 0)
            ewhat += "FeatureKey::ValidSection::" + this->fSection + " ";

        throw std::out_of_range(ewhat);
    }
}

}  // namespace lowletorfeats::base
