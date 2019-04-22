#pragma once

#include <string>  // string
#include <unordered_map>  // unordered_map


namespace lowletorfeats::base
{


class FeatureKey
{
public:
    /* Public type definitions */

    enum class ValidTypes { other, tfidf, okapi,  lmir };

    enum class ValidNames
    {
        // Other
        dl,

        // TF/IDF
        tflognorm, tfdoublenorm,
        idfdefault, idfsmooth, idfmax, idfprob, idfnorm,
        tfidf,

        // Okapi
        bm25, bm25plus, bm25f, bm25fplus,

        // LMIR
        abs, dir, jm
    };

    enum class ValidSections { full, body, anchor, title, url };

    /* Constructors */

    FeatureKey(std::string const & fKey);
    FeatureKey(
        std::string const & fType,
        std::string const & fName,
        std::string const & fSection
    );


    /* Public class methods */
    std::string toString() const;
    std::size_t toHash() const;

    /* Getters */

    std::string const & getFType() const { return this->fType; }
    std::string const & getFName() const { return this->fName; }
    std::string const & getFSection() const { return this->fSection; }

    ValidTypes const & getVType() const { return this->vType; }
    ValidNames const & getVName() const { return this->vName; }
    ValidSections const & getVSection() const { return this->vSection; }

    /* Setters */

    /**
     * @brief Recreates the `FeatureKey` with the given key string.
     *
     * @param newKeyString Str for the new key in format :type.name.section".
     */
    void setNewKey(std::string const & newKeyString)
    { *(this) = FeatureKey(newKeyString); }

    /* Public operators */
    //operator std::string() const { return this->toString(); }  // implicit
    //explicit operator std::string*() const { return &(this->toString()); }

    /* Public friend methods */
    friend bool operator== (FeatureKey const & fKey1, FeatureKey const & fKey2);
    friend bool operator!= (FeatureKey const & fKey1, FeatureKey const & fKey2);

private:
    /* Private member variables */

    // Feature key as a string
    std::string fType;
    std::string fName;
    std::string fSection;

    // Feature key as a enum
    ValidTypes vType;
    ValidNames vName;
    ValidSections vSection;

    // Valid type maps
    std::unordered_map<ValidTypes, std::string>
        static const validTypeMap;
    std::unordered_map<ValidNames, std::string>
        static const validNameMap;
    std::unordered_map<ValidSections, std::string>
        static const validSectionMap;

    // Inverse valid type maps
    std::unordered_map<std::string, ValidTypes>
        static const inverseValidTypeMap;
    std::unordered_map<std::string, ValidNames>
        static const inverseValidNameMap;
    std::unordered_map<std::string, ValidSections>
        static const inverseValidSectionMap;
};

}


namespace std
{

/**
 * @brief Define the hash function for the `FeatureKey`
 *
 * @tparam
 */
template<>
struct hash<lowletorfeats::base::FeatureKey>
{
    std::size_t operator() (lowletorfeats::base::FeatureKey const & fKey) const
    {
        return fKey.toHash();
    }
};

}
