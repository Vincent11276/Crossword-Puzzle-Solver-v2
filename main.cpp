#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
using namespace std;

constexpr unsigned int DEFAULT_MIN_WORD_LENGTH = 3;


class Point
{
public:
    int x;
    int y;

    Point(const int x_, const int y_) 
        : x(x_), y(y_) { }
};


class Vocabulary
{
public:
    std::unordered_set<std::string> words;
 
    Vocabulary()
    {
        // default..
    }

    Vocabulary(const std::string &filePath)
    {
        std::string tempStr;

        std::ifstream file(filePath);
        while(std::getline(file, tempStr))
            words.emplace(tempStr);
    }

    bool contains(const std::string &word)
    {
        return words.find(word) != words.end();
    }
};


template<typename T>
std::vector<T> subArr(const std::vector<T> &a, int start, int end)
{
    return std::vector<T>(a.begin() + start, a.begin() + end);
}


std::string charArrToStr(const std::vector<char> a)
{
    return std::string(a.begin(), a.end());
}


std::vector<std::tuple<std::string, int, int>> getAllCombi(const std::vector<char> &arr, const unsigned int minWordLength = DEFAULT_MIN_WORD_LENGTH)
{
    std::vector<std::tuple<std::string, int, int>> combinations;

    for (int wordLength = minWordLength; wordLength <= arr.size(); wordLength++)
    {
        for (int x = 0; x < arr.size() - wordLength + 1; x++)
        {
            combinations.push_back(std::make_tuple(charArrToStr(subArr<char>(arr, x, x + wordLength)), x, x + wordLength));
        }
    }
    return combinations;
}


std::vector<std::tuple<std::string, int, int>> getAllValidWords(std::vector<std::tuple<std::string, int, int>> &words, Vocabulary &vocab)
{
    std::vector<std::tuple<std::string, int, int>> validWords;
    
    for (const auto &word: words)
    {
        if (vocab.contains(std::get<0>(word)))
        {
            validWords.push_back(word);
        }
    }
    return validWords;
}


int main()
{
    bool contrary = false;

    Vocabulary validWordsVocab("words_alpha.txt");

    std::vector<std::vector<char>> puzzle 
    {
        {'d', 'a', 't', 'g', 't', 'g'}, 
        {'f', 'a', 's', 't', 't', 'g'}, 
        {'c', 'h', 'm', 'o', 't', 'g'}, 
        {'e', 'i', 'i', 'p', 't', 'g'},
        {'f', 'c', 'u', 'p', 't', 'g'},
        {'f', 'c', 'u', 'p', 't', 'g'}
    };



    auto validWords = getAllValidWords(getAllCombi(puzzle[0]), validWordsVocab);

    for (const auto &word: validWords)
    {
        auto [content, start, end] = word;
        std::cout << content << " {" << start << ", " << end << "}" << std::endl;
    }

    return EXIT_SUCCESS;
}