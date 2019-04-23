#pragma once

#include <lowletorfeats/base/stdllf.hpp>

#include <string>
#include <vector>
#include <unordered_map>


std::pair<
    std::string,
    std::vector<std::unordered_map<std::string, std::string>>
> getTestData()
{
    typedef std::unordered_map<std::string, std::string> StrStrMap;

    std::string const queryString = "time to query hello word";

    std::vector<StrStrMap> structDocTextVector
    {
        std::unordered_map<std::string, std::string>
        {
            {
                "full",
                "All our submissions from the Microsoft Research Cambridge (MSRC) team this year continue to explore issues in IR from a perspective very close to that of the original Okapi team, working first at City University of London, and then at MSRC. A summary of the contributions by the team, from TRECs 1 to 7 is presented in [3]. In this work, weighting schemes for ad-hoc retrieval were developed, inspired by a probabilistic interpretation of relevance; this lead, for instance, to the successful BM25 weighting function. These weighting schemes were extended to deal with pseudo relevance feedback (blind feedback). Furthermore, the Okapi team participated in most of the early interactive tracks, and also developed iterative relevance feedback strategies for the routing task. Following up on the routing work, TRECs 7–11 submissions dealt principally with the adaptive filtering task; this work is summarised in [5]. Last year MSRC entered only the HARD track, concentrating on the use of the clarification forms [6]. We hoped to make use of the query expansion methods developed for filtering in the context of feedback on snippets in the clarification forms. However, our methods were not very successful. In this year’s TREC we took part in the HARD and WEB tracks. In HARD, we tried some variations on the process of feature selection for query expansion. On the WEB track, we investigated the combination of information from different content fields and from link-based features. Section 3 briefly describes the system we used. Section 4 describes our HARD participation and Section 5 our TREC participation."
            }
        },
        std::unordered_map<std::string, std::string>
        {
            {
                "full",
                "In this paper, we reveal a common deficiency of the current retrieval models: the component of term frequency (TF) normalization by document length is not lower-bounded properly; as a result, very long documents tend to be overly penalized. In order to analytically diagnose this problem, we propose two desirable formal constraints to capture the heuristic of lower-bounding TF, and use constraint analysis to examine several representative retrieval functions. Analysis results show that all these retrieval functions can only satisfy the constraints for a certain range of parameter values and/or for a particular set of query terms. Empirical results further show that the retrieval performance tends to be poor when the parameter is out of the range or the query term is not in the particular set. To solve this common problem, we propose a general and efficient method to introduce a sufficiently large lower bound for TF normalization which can be shown analytically to fix or alleviate the problem. Our experimental results demonstrate that the proposed method, incurring almost no additional computational cost, can be applied to state-of-the-art retrieval functions, such as Okapi BM25, language models, and the divergence from randomness approach, to significantly improve the average precision, especially for verbose queries."
            }
        }
    };

    return std::pair(queryString, structDocTextVector);
}
