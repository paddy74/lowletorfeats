#pragma once

#include "base/stdllf.hpp"


namespace lowletorfeats
{

/**
 * @brief Collect all low-level features for a given document given the
 *  term-frequency map.
 *
 * @param docTermFrequencies Map of term frequencies for each term in the doc.
 * @return base::DocFeatureMap
 */
base::DocFeatureMap collectDocFeatures(
    base::TermFrequencyMap const & docTermFrequencies
)
{
    base::DocFeatureMap featureMap;

    return featureMap;
}


/**
 * @brief Collect all low-level features for a given document-query pair given
 *  the term-frequency map.
 *
 * @param docTermFrequencies Map of term frequencies for each term in the doc.
 * @param queryTermFrequencies Map of term frequencies for each term in the query.
 * @return base::DocFeatureMap
 */
base::DocFeatureMap collectDocFeatures(
    base::TermFrequencyMap const & docTermFrequencies,
    base::TermFrequencyMap const & queryTermFrequencies
)
{
    base::DocFeatureMap featureMap;

    return featureMap;
}


/**
 * @brief Collect all low-level features for a given document.
 *
 * @param docText The document's raw text.
 * @return base::DocFeatureMap The query's raw text.
 */
base::DocFeatureMap collectDocFeatures(
    std::string const & docText
)
{
    // Step 1: Create the `TermFrequencyMap`
    base::TermFrequencyMap docTermFreqs;

    // Step 2: collectDocFeatures
    return collectDocFeatures(docTermFreqs);
}


/**
 * @brief Collect all low-level features for a given document-query pair.
 *
 * @param docText The document's raw text.
 * @param queryText The query's raw text.
 * @return base::DocFeatureMap
 */
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
