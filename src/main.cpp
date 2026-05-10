// Copyright 2024 UNN
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/textgen.h"

int main() {
    std::vector<std::string> words;
    std::string word;
    std::ifstream infile("input.txt");

    if (infile.is_open()) {
        while (infile >> word) {
            words.push_back(word);
        }
        infile.close();
    } else {
        std::cout << "File input.txt not found. "
            << "Generation canceled." << std::endl;
        return 1;
    }

    TextGenerator generator;
    generator.train(words);

    std::string generated_text = generator.generate(MAXGEN);

    std::ofstream outfile("result/gen.txt");
    if (outfile.is_open()) {
        outfile << generated_text;
        outfile.close();
        std::cout << "Text successfully generated "
            << "and saved to result/gen.txt" << std::endl;
    } else {
        std::cout << "Failed to open file for writing." << std::endl;
    }

    return 0;
}
