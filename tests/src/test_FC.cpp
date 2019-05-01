#include <lowletorfeats/FeatureCollector.hpp>

#include "testData.hpp"

#include <iostream>


int main(int argc, const char * argv[])
{
    auto const testData = getTestData();
    auto const queryStr = testData.first;
    auto const structDocMap = testData.second;

    auto fc = lowletorfeats::FeatureCollector(structDocMap, queryStr);
    fc.collectPresetFeatures();

    std::cout << fc.toString();

    return 0;
}
