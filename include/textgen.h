// Copyright 2024 UNN
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <random>
#include <stdexcept>

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> prefix;

class TextGenerator {
 private:
    std::map<prefix, std::vector<std::string>> statetab;
    prefix starting_prefix;

 public:
    TextGenerator();
    void train(const std::vector<std::string>& text);
    std::string generate(int max_words = MAXGEN);
    std::map<prefix, std::vector<std::string>> getStatetab() const;
    prefix getStartingPrefix() const;
};
