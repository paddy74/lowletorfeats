#include <lowletorfeats/base/FeatureKey.hpp>

#include <iostream>


int main()
{
    lowletorfeats::base::FeatureKey fKey;
    lowletorfeats::base::FeatureKey fKey2(fKey);

    fKey = lowletorfeats::base::FeatureKey("invalid.invalid.invalid");
    fKey = lowletorfeats::base::FeatureKey("invalid", "invalid", "invalid");
    fKey = lowletorfeats::base::FeatureKey("agnh", "alds", "ibsfdg");

    std::cout << fKey.toString() << std::endl;

    return 0;
}
