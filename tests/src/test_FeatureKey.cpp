#include <iostream>
#include <lowletorfeats/base/FeatureKey.hpp>

int main()
{
    // Test constructors
    lowletorfeats::base::FeatureKey fKey;
    fKey = lowletorfeats::base::FeatureKey(fKey);
    fKey = lowletorfeats::base::FeatureKey("invalid.invalid.invalid");
    fKey = lowletorfeats::base::FeatureKey("invalid", "invalid", "invalid");
    fKey = lowletorfeats::base::FeatureKey("tfidf", "tfidf", "full");

    // Test public methods
    fKey.changeKey("okapi.bm25.body");
    fKey.toString();
    fKey.toHash();

    fKey.getFType();
    fKey.getFName();
    fKey.getFSection();
    fKey.getVType();
    fKey.getVName();
    fKey.getVSection();

    return 0;
}
