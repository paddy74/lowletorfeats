#pragma once

#include <string>  // string, stoi
#include <functional>  // hash
#include <vector>  // vector


namespace lowletorfeats::base
{

class FeatureKey
{
public:
    /* Public member variables */
    std::string fType;
    std::string fName;
    std::string fSection;

    /* Constructors */
    FeatureKey(std::string const & fKey);
    FeatureKey(
        std::string const & fType,
        std::string const & fName,
        std::string const & fSection
    );

    /* Public class methods */
    std::string toString() const;

    /* Public operators */
    //bool operator== (FeatureKey const & other) const;

    /* Public friend methods */
    friend bool operator== (FeatureKey const & fKey1, FeatureKey const & fKey2);
    friend bool operator!= (FeatureKey const & fKey1, FeatureKey const & fKey2);

private:
    /* Private member variables */

    std::vector<std::string> static const validTypes;
    std::vector<std::string> static const validNames;
    std::vector<std::string> static const validSections;

    /* Private class methods */

    /**
     * @brief Assert that the feature key matches the available options.
     *
     * @return true
     * @return false
     */
    void isValid() const;
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
        return (
            (std::hash<std::string>()(fKey.fType))
            ^ (std::hash<std::string>()(fKey.fName))
            ^ (std::hash<std::string>()(fKey.fSection))
        );
    }
};

}
