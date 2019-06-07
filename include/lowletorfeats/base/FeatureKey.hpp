#pragma once

#include <string>         // string
#include <unordered_map>  // unordered_map

namespace lowletorfeats::base
{
/**
 * @brief Class for describing a feature key.
 *
 */
class FeatureKey
{
public:
    /* Public type definitions */
    /***************************/

    enum class ValidTypes
    {
        invalid,
        other,
        tfidf,
        okapi,
        lmir
    };

    enum class ValidNames
    {
        invalid,

        // Other
        dl,

        // TF/IDF
        tflognorm,
        tfdoublenorm,
        idfdefault,
        idfsmooth,
        idfmax,
        idfprob,
        idfnorm,
        tfidf,

        // Okapi
        bm25,
        bm25plus,
        bm25f,
        bm25fplus,

        // LMIR
        abs,
        dir,
        jm
    };

    enum class ValidSections
    {
        invalid,
        full,
        body,
        anchor,
        title,
        url
    };

    /* Constructors */
    /****************/

    /**
     * @brief Construct a new Feature Key with "invalid" values.
     *
     */
    FeatureKey();

    /**
     * @brief Construct a new Feature Key from a string "type.name.section".
     *
     * @param fKeyStr A string representation of the `FeatureKey` in the form
     *  "type.name.section".
     */
    FeatureKey(std::string const & fKeyStr);

    /**
     * @brief Construct a new Feature Key from multiple strings.
     *
     * @param fType
     * @param fName
     * @param fSection
     */
    FeatureKey(
        std::string const & fType, std::string const & fName,
        std::string const & fSection);

    /**
     * @brief Copy constructor.
     *
     * @param other
     */
    FeatureKey(FeatureKey const & other);

    /* Public class methods */

    /**
     * @brief Create a string representation of the FeatureKey.
     *
     */
    std::string toString() const;

    /**
     * @brief Create a hashed representation of the FeatureKey.
     *
     */
    std::size_t toHash() const;

    /**
     * @brief Recreates the `FeatureKey` with the given key string.
     *
     * @param newKeyString Str for the new key in format :type.name.section".
     */
    void changeKey(std::string const & newKeyString);

    /* Getters */
    /***********/

    /**
     * @brief Get the string representation of the feature type.
     *
     */
    std::string const & getFType() const { return this->fType; }

    /**
     * @brief Get the string representation of the feature name.
     *
     */
    std::string const & getFName() const { return this->fName; }

    /**
     * @brief Get the string representation of the feature section.
     *
     */
    std::string const & getFSection() const { return this->fSection; }

    /**
     * @brief Get the enum of the feature type.
     *
     */
    ValidTypes const & getVType() const { return this->vType; }

    /**
     * @brief Get the enum of the feature name.
     *
     */
    ValidNames const & getVName() const { return this->vName; }

    /**
     * @brief Get the enum of the feature section.
     *
     */
    ValidSections const & getVSection() const { return this->vSection; }

    /* Public operators */
    /********************/
    // operator std::string() const { return this->toString(); }  // implicit
    // explicit operator std::string*() const { return &(this->toString()); }

    /* Public friend methods */
    friend bool operator==(FeatureKey const & fKey1, FeatureKey const & fKey2);
    friend bool operator!=(FeatureKey const & fKey1, FeatureKey const & fKey2);

private:
    /* Private member variables */
    /****************************/

    // Feature key as a string
    std::string fType;     // Feature type string
    std::string fName;     // Feature name string
    std::string fSection;  // Feature name section

    // Feature key as a enum
    ValidTypes vType;        // Feature type enum
    ValidNames vName;        // Feature name enum
    ValidSections vSection;  // Feature section enum

    /* Private static member variables */
    /***********************************/

    // Valid type maps map enum to string
    std::unordered_map<ValidTypes, std::string> static const validTypeMap;
    std::unordered_map<ValidNames, std::string> static const validNameMap;
    std::unordered_map<
        ValidSections, std::string> static const validSectionMap;

    // Inverse valid type maps map string to enum
    std::unordered_map<
        std::string, ValidTypes> static const inverseValidTypeMap;
    std::unordered_map<
        std::string, ValidNames> static const inverseValidNameMap;
    std::unordered_map<
        std::string, ValidSections> static const inverseValidSectionMap;

    /* Private class methods */
    /*************************/

    /**
     * @brief Apply the enum feature values according to the feature strings.
     *
     */
    void initVKeys();
};

}  // namespace lowletorfeats::base

namespace std
{
/**
 * @brief Define the hash function for the `FeatureKey`
 *
 * @tparam
 */
template <>
struct hash<lowletorfeats::base::FeatureKey>
{
    std::size_t operator()(lowletorfeats::base::FeatureKey const & fKey) const
    {
        return fKey.toHash();
    }
};

}  // namespace std
