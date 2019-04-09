#include <lowletorfeats/collectDocFeatures.hpp>


namespace lowletorfeats
{

base::DocFeatureMap collectDocFeatures(
    base::TermFrequencyMap const & docTermFrequencies
)
{
    base::DocFeatureMap featureMap;

    return featureMap;
}


base::DocFeatureMap collectDocFeatures(
    base::TermFrequencyMap const & docTermFrequencies,
    base::TermFrequencyMap const & queryTermFrequencies
)
{
    base::DocFeatureMap featureMap;

    return featureMap;
}


base::DocFeatureMap collectDocFeatures(
    std::string const & docText
)
{
    // Step 1: Create the `TermFrequencyMap`
    base::TermFrequencyMap docTermFreqs;

    // Step 2: collectDocFeatures
    return collectDocFeatures(docTermFreqs);
}


base::DocFeatureMap collectDocFeatures(
    std::string const & docText,
    std::string const & queryText
)
{
    // Step 1: Create the `TermFrequencyMap`
    base::TermFrequencyMap docTermFreqs;
    base::TermFrequencyMap queryTermFreqs;

    // Step 2: collectDocFeatures
    return collectDocFeatures(docTermFreqs);
}

}
