import nltk

nltk.download('punkt')
nltk.download('reuters')
nltk.download('gutenberg')
nltk.download('averaged_perceptron_tagger')
nltk.download('universal_tagset')

# Task 1 (1 mark)
from collections import Counter


def stem_counter(text):
    """Return a Python Counter of stems
    >>> c1 = stem_counter("Here is sentence 1. Here is sentence 2.")
    >>> sorted(c1.most_common())
    [('.', 2), ('1', 1), ('2', 1), ('here', 2), ('is', 2), ('sentenc', 2)]
    >>> emma = nltk.corpus.gutenberg.raw('austen-emma.txt')
    >>> c2 = stem_counter(emma[:1000])
    >>> sorted(c2.most_common(4))
    [(',', 13), ('had', 7), ('of', 12), ('the', 7)]
    >>> c2['had']
    7
    """

    #create NLTK porter stemmer
    ps = nltk.PorterStemmer()

    #list which holds word stems
    word_stems = []

    for sentence in nltk.sent_tokenize(text):
        for word in nltk.word_tokenize(sentence):
            #add the stemmed word (in lower case) to the word stems list
            word_stems.append(ps.stem(word.lower()))

    counter = Counter(word_stems)
    return counter


# Task 2 (1 mark)
def distinct_words_of_pos(text, pos):
    """Return the sorted list of distinct words with a given part of speech
    >>> emma = nltk.corpus.gutenberg.raw('austen-emma.txt')
    >>> d = distinct_words_of_pos(emma[:1000], 'NOUN')
    >>> len(d)
    42
    >>> d[:10]
    ['[', ']', 'affection', 'austen', 'between', 'blessings', 'caresses', 'clever', 'consequence', 'daughters']
    """

    INDEX_WORD = 0
    INDEX_POS = 1

    #sorted list
    sorted_list = []

    #text to sentences
    text_sentences = [nltk.word_tokenize(s) for s in nltk.sent_tokenize(text)]

    #give words pos tags (within sentences)
    text_sentences_tags = nltk.pos_tag_sents((text_sentences), tagset='universal')

    for tst_list in text_sentences_tags:
        for element in tst_list:
            #if tag matches pos
            if element[INDEX_POS] == pos:
                #ensure no duplicates
                if element[INDEX_WORD] not in sorted_list:
                    #add the word only
                    sorted_list.append(element[INDEX_WORD])

    #convert words to lower case
    sorted_list = [x.lower() for x in sorted_list]

    #sort the list alphabetically
    sorted_list.sort()

    return sorted_list


# Task 3 (1 mark)
def most_common_pos_bigram(text):
    """Return the most common PoS bigram
    >>> most_common_pos_bigram("I saw the man with a telescope")
    ('DET', 'NOUN')
    >>> emma = nltk.corpus.gutenberg.raw('austen-emma.txt')
    >>> most_common_pos_bigram(emma[:1000])
    ('NOUN', '.')
    """

    import collections

    INDEX_POS = 1
    FIRST_ELEMENT = 0


    bigram_list = []

    # text to sentences
    text_sentences = [nltk.word_tokenize(s) for s in nltk.sent_tokenize(text)]

    # give words pos tags (within sentences)
    text_sentences_tags = nltk.pos_tag_sents((text_sentences), tagset='universal')

    for tst_list in text_sentences_tags:
        for element in tst_list:
            bigram_list.append(element[INDEX_POS])


    bigrams = list(nltk.bigrams(bigram_list))
    bigrams_count = collections.Counter(bigrams)

    return (bigrams_count.most_common(1)[FIRST_ELEMENT][FIRST_ELEMENT])


# Task 4 (2 marks)
import re


def my_tokeniser(text):
    """Return the tokens
    >>> my_tokeniser("This is a sentence")
    ['This', 'is', 'a', 'sentence']
    """

    regexp = r'''([\w]+([-/.,']*[\w])*)'''

    items = []

    for all in re.findall(regexp, text):
        items.append(all[0])

    return items

# - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # - # -
# DO NOT MODIFY THE CODE BELOW
def baseline_tokeniser(text):
    "A baseline tokeniser"
    regexp = r'''[^\s]+'''
    return re.findall(regexp, text)


def false_negatives(tokens, target):
    """Return false negatives
    False negatives are items from the target that were not detected
    as tokens"""
    return list(set(target) - set(tokens))


def false_positives(tokens, target):
    """Return the false positives
    False positives are the items that were wrongly identified as tokens"""
    return list(set(tokens) - set(target))


def my_score(raw, tokens, target):
    fn = false_negatives(tokens, target)
    fp = false_positives(tokens, target)
    score = len(fn) / len(target) + len(fp) / len(target)
    baseline_results = baseline_tokeniser(raw)
    fn_baseline = false_negatives(baseline_results, target)
    fp_baseline = false_positives(baseline_results, target)
    score_baseline = len(fn_baseline) / len(target) + len(fp_baseline) / len(target)
    return max(0, 2 * (score_baseline - score) / score_baseline)


if __name__ == "__main__":
    import doctest

    doctest.testmod()
    raw_reuters = nltk.corpus.reuters.raw(categories="corn")
    words_reuters = [w for s in nltk.sent_tokenize(raw_reuters)
                     for w in nltk.word_tokenize(s)]

    score = my_score(raw_reuters, my_tokeniser(raw_reuters), words_reuters)
    if score <= 0:
        rounded_score = 0
    elif score > 0 and score <= 0.5:
        rounded_score = 0.5
    elif score > 0.5 and score <= 1:
        rounded_score = 1
    elif score > 1 and score <= 1.5:
        rounded_score = 1.5
    else:
        rounded_score = 2

    print("Score of your tokeniser: %1.3f Rounded: %1.1f" % (score,
                                                             rounded_score))
