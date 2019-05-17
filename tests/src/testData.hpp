#pragma once

#include <string>
#include <unordered_map>
#include <vector>

std::pair<
    std::string, std::vector<std::unordered_map<std::string, std::string>>>
    getTestData()
{
    typedef std::unordered_map<std::string, std::string> StrStrMap;

    std::string const queryString =
        "Van Helsing's face grow white and purple by turns.";

    // Construct raw data
    std::vector<StrStrMap> structDocTextVector{
        StrStrMap{
            {"id", "00000"},
            {"rscore", "5"},
            {"url", "https://youthere.org"},
            {"title", "October helsing"},
            {"author", "Van Helsing"},
            {"anchor", "helsing@mail.com, https://hello/world.com"},
            {"body",
             "24 October.--A whole week of waiting. Daily telegrams to "
             "Godalming, but only the same story: Not yet reported. Mina's "
             "morning and evening hypnotic answer is unvaried: lapping waves, "
             "rushing water, and creaking masts. 25 October.--How I miss my "
             "phonograph! To write diary with a pen is irksome to me; but Van "
             "Helsing says I must. We were all wild with excitement yesterday "
             "when Godalming got his telegram from Lloyd's. I know now what "
             "men feel in battle when the call to action is heard. Mrs. "
             "Harker, alone of our party, did not show any signs of emotion. "
             "After all, it is not strange that she did not; for we took "
             "special care not to let her know anything about it, and we all "
             "tried not to show any excitement when we were in her presence. "
             "In old days she would, I am sure, have noticed, no matter how "
             "we might have tried to conceal it; but in this way she is "
             "greatly changed during the past three weeks. The lethargy grows "
             "upon her, and though she seems strong and well, and is getting "
             "back some of her colour, Van Helsing and I are not satisfied. "
             "We talk of her often; we have not, however, said a word to the "
             "others. It would break poor Harker's heart--certainly his "
             "nerve--if he knew that we had even a suspicion on the subject. "
             "Van Helsing examines, he tells me, her teeth very carefully, "
             "whilst she is in the hypnotic condition, for he says that so "
             "long as they do not begin to sharpen there is no active danger "
             "of a change in her. If this change should come, it would be "
             "necessary to take steps!... We both know what those steps would "
             "have to be, though we do not mention our thoughts to each "
             "other. We should neither of us shrink from the task--awful "
             "though it be to contemplate. Euthanasia is an excellent and a "
             "comforting word! I am grateful to whoever invented it."}},
        StrStrMap{
            {"id", "00001"},
            {"rscore", "3"},
            {"url", "https://randomhello.com"},
            {"title", "There are such beings as vampires"},
            {"author", "Vampire"},
            {"anchor", "madamMina@fallen.com"},
            {"body",
             "So we came down this road; when we meet other ways--not always "
             "were we sure that they were roads at all, for they be neglect "
             "and light snow have fallen--the horses know and they only. I "
             "give rein to them, and they go on so patient. By-and-by we find "
             "all the things which Jonathan have note in that wonderful diary "
             "of him. Then we go on for long, long hours and hours. At the "
             "first, I tell Madam Mina to sleep; she try, and she succeed. "
             "She sleep all the time; till at the last, I feel myself to "
             "suspicious grow, and attempt to wake her. But she sleep on, and "
             "I may not wake her though I try. I do not wish to try too hard "
             "lest I harm her; for I know that she have suffer much, and "
             "sleep at times be all-in-all to her. I think I drowse myself, "
             "for all of sudden I feel guilt, as though I have done "
             "something; I find myself bolt up, with the reins in my hand, "
             "and the good horses go along jog, jog, just as ever. I look "
             "down and find Madam Mina still sleep. It is now not far off "
             "sunset time, and over the snow the light of the sun flow in big "
             "yellow flood, so that we throw great long shadow on where the "
             "mountain rise so steep. For we are going up, and up; and all is "
             "oh! so wild and rocky, as though it were the end of the world. "
             "Then I arouse Madam Mina. This time she wake with not much "
             "trouble, and then I try to put her to hypnotic sleep. But she "
             "sleep not, being as though I were not. Still I try and try, "
             "till all at once I find her and myself in dark; so I look "
             "round, and find that the sun have gone down. Madam Mina laugh, "
             "and I turn and look at her. She is now quite awake, and look so "
             "well as I never saw her since that night at Carfax when we "
             "first enter the Count's house. I am amaze, and not at ease "
             "then; but she is so bright and tender and thoughtful for me "
             "that I forget all fear. I light a fire, for we have brought "
             "supply of wood with us, and she prepare food while I undo the "
             "horses and set them, tethered in shelter, to feed. Then when I "
             "return to the fire she have my supper ready. I go to help her; "
             "but she smile, and tell me that she have eat already--that she "
             "was so hungry that she would not wait. I like it not, and I "
             "have grave doubts; but I fear to affright her, and so I am "
             "silent of it. She help me and I eat alone; and then we wrap in "
             "fur and lie beside the fire, and I tell her to sleep while I "
             "watch. But presently I forget all of watching; and when I "
             "sudden remember that I watch, I find her lying quiet, but "
             "awake, and looking at me with so bright eyes. Once, twice more "
             "the same occur, and I get much sleep till before morning. When "
             "I wake I try to hypnotise her; but alas! though she shut her "
             "eyes obedient, she may not sleep. The sun rise up, and up, and "
             "up; and then sleep come to her too late, but so heavy that she "
             "will not wake. I have to lift her up, and place her sleeping in "
             "the carriage when I have harnessed the horses and made all "
             "ready. Madam still sleep, and she look in her sleep more "
             "healthy and more redder than before. And I like it not. And I "
             "am afraid, afraid, afraid!--I am afraid of all things--even to "
             "think but I must go on my way. The stake we play for is life "
             "and death, or more than these, and we must not flinch."}},
        StrStrMap{
            {"id", "00002"},
            {"rscore", "1"},
            {"url", "https://uncleanvampire.com"},
            {"title", "Unclean vampire. Dr. Van Helsing"},
            {"author", "Seward"},
            {"anchor", "https://whatisyourname.com/index.html"},
            {"body",
             "In God's name what does this mean? Harker cried out. Dr. "
             "Seward, Dr. Van Helsing, what is it? What has happened? What is "
             "wrong? Mina, dear, what is it? What does that blood mean? My "
             "God, my God! has it come to this! and, raising himself to his "
             "knees, he beat his hands wildly together. Good God help us! "
             "help her! oh, help her! With a quick movement he jumped from "
             "bed, and began to pull on his clothes,--all the man in him "
             "awake at the need for instant exertion. What has happened? Tell "
             "me all about it! he cried without pausing. Dr. Van Helsing, you "
             "love Mina, I know. Oh, do something to save her. It cannot have "
             "gone too far yet. Guard her while I look for him! His wife, "
             "through her terror and horror and distress, saw some sure "
             "danger to him: instantly forgetting her own grief, she seized "
             "hold of him and cried out: No! no! Jonathan, you must not leave "
             "me. I have suffered enough to-night, God knows, without the "
             "dread of his harming you. You must stay with me. Stay with "
             "these friends who will watch over you! Her expression became "
             "frantic as she spoke; and, he yielding to her, she pulled him "
             "down sitting on the bed side, and clung to him fiercely. Van "
             "Helsing and I tried to calm them both. The Professor held up "
             "his little golden crucifix, and said with wonderful calmness: "
             "Do not fear, my dear. We are here; and whilst this is close to "
             "you no foul thing can approach. You are safe for to-night; and "
             "we must be calm and take counsel together. She shuddered and "
             "was silent, holding down her head on her husband's breast. When "
             "she raised it, his white night-robe was stained with blood "
             "where her lips had touched, and where the thin open wound in "
             "her neck had sent forth drops. The instant she saw it she drew "
             "back, with a low wail, and whispered, amidst choking sobs: "
             "Unclean, unclean! I must touch him or kiss him no more. Oh, "
             "that it should be that it is I who am now his worst enemy, and "
             "whom he may have most cause to fear. To this he spoke out "
             "resolutely: Nonsense, Mina. It is a shame to me to hear such a "
             "word. I would not hear it of you; and I shall not hear it from "
             "you. May God judge me by my deserts, and punish me with more "
             "bitter suffering than even this hour, if by any act or will of "
             "mine anything ever come between us! He put out his arms and "
             "folded her to his breast; and for a while she lay there "
             "sobbing. He looked at us over her bowed head, with eyes that "
             "blinked damply above his quivering nostrils; his mouth was set "
             "as steel. After a while her sobs became less frequent and more "
             "faint, and then he said to me, speaking with a studied calmness "
             "which I felt tried his nervous power to the utmost:-- And now, "
             "Dr. Seward, tell me all about it. Too well I know the broad "
             "fact; tell me all that has been. I told him exactly what had "
             "happened, and he listened with seeming impassiveness; but his "
             "nostrils twitched and his eyes blazed as I told how the "
             "ruthless hands of the Count had held his wife in that terrible "
             "and horrid position, with her mouth to the open wound in his "
             "breast. It interested me, even at that moment, to see, that, "
             "whilst the face of white set passion worked convulsively over "
             "the bowed head, the hands tenderly and lovingly stroked the "
             "ruffled hair. Just as I had finished, Quincey and Godalming "
             "knocked at the door. They entered in obedience to our summons. "
             "Van Helsing looked at me questioningly. I understood him to "
             "mean if we were to take advantage of their coming to divert if "
             "possible the thoughts of the unhappy husband and wife from each "
             "other and from themselves; so on nodding acquiescence to him he "
             "asked them what they had seen or done. To which Lord Godalming "
             "answered: I could not see him anywhere in the passage, or in "
             "any of our rooms. I looked in the study but, though he had been "
             "there, he had gone. He had, however---- He stopped suddenly, "
             "looking at the poor drooping figure on the bed. Van Helsing "
             "said gravely:--"}}};

    // Construct analyzed data

    return std::pair(queryString, structDocTextVector);
}
