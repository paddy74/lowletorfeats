#pragma once

#include <lowletorfeats/base/stdDef.hpp>

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
        },
        std::unordered_map<std::string, std::string>
        {
            {
                "full",
                "Being rare or ‘exotic’ is a relative phenomenon. From a Samoan point of view Burushaski is an extremely exotic language, but from the point of view of Telugu much less so. In this brief note we want to look a how different and how similar languages turn out to be in pairwise comparisons and the role that genealogical relatedness plays in this regard. We are interested in knowing whether there is a cut-off point Shigh in the amount of similarities such that we can be sure that language pairs that  have more than Shigh similarities are all generally thought to be related and also whether there is a cut-of point Slow at the other end of the scale such that all languages having less similarities than Slow are thought to be unrelated. In other words, if a language is ‘normal’ relative to some other language (as Burushaski is to Telugu), does this imply that the two languages are related according to commonly accepted classifications? Or, if two languages are mutually very exotic (as Burushaski and Samoan), does this imply that they are not thought to be related in commonly accepted classifications?"
            }
        },
        std::unordered_map<std::string, std::string>
        {
            {
                "full",
                "Classical  oscillator  differential  equation  is  replaced  by  the  corresponding  (finite  time)  difference equation. The equation is, then, symmetrized so that it remains invariant under the  change  dÆ-d,  where  d  is  the  smallest  span  of  time.  This  symmetric  equation  has  solutions, which come in reciprocally related pairs. One member of a pair agrees with the classical solution and the other is an oscillating solution and does not converge to a limit as dÆ0. This solution contributes to oscillator energy a term which is a multiple of half-integers."
            }
        },
        std::unordered_map<std::string, std::string>
        {
            {
                "full",
                "Single-transverse-spin asymmetries (SSAs) in high-energy hadronicreactions with one transversely polarized hadron were first observed more than three decadesago [1]. The ratio of thedifference and the sum of (differential) cross sections when the hadron’s spin vector is flipped. Recent experimental measurements of SSAs both in polarized hadronic collisions[2, 3] and in semi-inclusive lepton-nucleon deep inelastic scattering (SIDIS) [4] have renewedthe interest in investigating the origin of SSAs in Quantum Chromodynamics (QCD) [5].It is believed that some SSAs are a consequence of the partons’ transverse motion insidethe polarized hadron. The momentum scale of this transverse motion is a typical hadronicscale. For observables with onlyonehard scaleQ≫ΛQCD, the SSAshould be proportional to [6, 7]. Such observables only probe an averaged effect ofthe partons’ transverse motion. However, for observables characterized by more than onephysical scale, SSAs may directly probe the partons’ transversemotion. For example, inthe case of Drell-Yan hadronic production of a lepton pair of large invariant massQandtransverse momentumq⊥≪Q, the pair probes the (anti-) quark’s transverse motion at thescaleq⊥, while the invariant massQof the pair sets the hard scale of the collision [8]. Inthis letter, we study the SSA in hadronic production of two jets: [9, 10, 11].Unlike in the Drell-Yan process or in SIDIS, the SSA in di-jet production can be generatedby both initial- and final-state interactions. We emphasize that measurements of the SSAfor di-jet production have begun at RHIC [12], complementing the measurements in SIDIS."
            }
        }
    };

    return std::pair(queryString, structDocTextVector);
}
