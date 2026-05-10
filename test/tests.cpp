// Copyright 2024 UNN
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../include/textgen.h"

TEST(MarkovChainTest, EmptyTextTraining) {
    TextGenerator gen;
    std::vector<std::string> text = {};
    gen.train(text);
    EXPECT_TRUE(gen.getStatetab().empty());
}

TEST(MarkovChainTest, ShortTextTraining) {
    TextGenerator gen;
    std::vector<std::string> text = { "one", "word" };
    gen.train(text);
    EXPECT_TRUE(gen.getStatetab().empty());
}

TEST(MarkovChainTest, PrefixFormation) {
    TextGenerator gen;
    std::vector<std::string> text = { "one", "two", "three" };
    gen.train(text);
    prefix expected_prefix = { "one", "two" };
    EXPECT_EQ(gen.getStartingPrefix(), expected_prefix);
}

TEST(MarkovChainTest, StateTablePopulation) {
    TextGenerator gen;
    std::vector<std::string> text = { "one", "two", "three", "four" };
    gen.train(text);

    auto table = gen.getStatetab();
    prefix pref1 = { "one", "two" };
    EXPECT_EQ(table[pref1].size(), 1);
    EXPECT_EQ(table[pref1][0], "three");
}

TEST(MarkovChainTest, MultipleSuffixesForPrefix) {
    TextGenerator gen;
    std::vector<std::string> text = {
        "one", "two", "three", "one", "two", "four"
    };
    gen.train(text);

    auto table = gen.getStatetab();
    prefix pref = { "one", "two" };
    EXPECT_EQ(table[pref].size(), 2);
    EXPECT_EQ(table[pref][0], "three");
    EXPECT_EQ(table[pref][1], "four");
}

TEST(MarkovChainTest, GenerateSingleSuffixLogic) {
    TextGenerator gen;
    std::vector<std::string> text = { "mama", "washed", "frame" };
    gen.train(text);
    EXPECT_EQ(gen.generate(10), "mama washed frame");
}

TEST(MarkovChainTest, RandomSuffixSelection) {
    TextGenerator gen;
    std::vector<std::string> text = {
        "i", "love", "apples", "i", "love", "pears"
    };
    gen.train(text);

    std::string result = gen.generate(3);
    bool is_valid = (result == "i love apples" || result == "i love pears");
    EXPECT_TRUE(is_valid);
}

TEST(MarkovChainTest, StopWhenNoSuffix) {
    TextGenerator gen;
    std::vector<std::string> text = { "one", "two", "three" };
    gen.train(text);
    std::string result = gen.generate(10);
    EXPECT_EQ(result, "one two three");
}

TEST(MarkovChainTest, MaxLengthRestriction) {
    TextGenerator gen;
    std::vector<std::string> text = { "a", "b", "a", "b", "a" };
    gen.train(text);

    std::string result = gen.generate(4);
    int spaces = 0;
    for (char c : result) {
        if (c == ' ') spaces++;
    }
    EXPECT_EQ(spaces, 3);
}

TEST(MarkovChainTest, CustomTableGeneration) {
    TextGenerator gen;
    std::vector<std::string> text = { "it", "was", "raining", "and", "cold" };
    gen.train(text);

    std::string result = gen.generate(5);
    EXPECT_EQ(result, "it was raining and cold");
}
