#include <lowletorfeats/FeatureCollector.hpp>

#include "testData.hpp"

int main()
{
    auto const testData = getTestData();
    auto const queryStr = testData.first;
    auto const structDocMap = testData.second;

    auto fc = lowletorfeats::FeatureCollector(structDocMap, queryStr);
    fc.collectPresetFeatures();

    return 0;
}
