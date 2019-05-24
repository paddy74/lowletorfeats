#include <lowletorfeats/FeatureCollector.hpp>

#include "testData.hpp"

int main()
{
    // Get test data
    auto const testData = getTestData();
    auto const queryStr = testData.first;
    auto const structDocMap = testData.second;

    // Test constructors
    lowletorfeats::FeatureCollector fc;
    fc = lowletorfeats::FeatureCollector();
    fc = lowletorfeats::FeatureCollector(structDocMap, queryStr);
    //
    //
    //

    // Test public methods
    fc.toString();
    fc.getFeatureString();

    fc.collectPresetFeatures();
    fc.reCollectFeatures();
    fc.collectFeatures(lowletorfeats::base::FeatureKey("tfidf.tfidf.full"));

    // Getter methods
    fc.getNumDocs();
    fc.getNumFeatures();
    fc.getDocVect();
    fc.getFeatureVects();

    // Setter methods
    std::unordered_map<std::string, float> newSectionWeights = {
        {"full", 0.3},   {"title", 1},    {"body", 0.4},
        {"author", 0.9}, {"anchor", 0.5}, {"url", 0.7}};
    fc.setSectionWeights(newSectionWeights);
    // fc.setAnalyzerFunction(lowletorfeats::FeatureCollector::analyzerFun);

    return 0;
}
