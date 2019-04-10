#pragma once

#include <lowletorfeats/base/utils.hpp>


namespace lowletorfeats
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

    /* Public class methods */
    std::string toString() const;

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
