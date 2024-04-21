#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <string>
#include <unordered_map>

#include "homework3.hpp"

// (1 + 2) * 3 / 4 + 5 * (6 - 7)

// 1. Токенизация
// 2. Парсер (построение дерева разбора выражения)

// +, -, *, /, %

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
    int value;
};

struct UnknownToken {
    std::string value;
};

struct MinToken {};

struct MaxToken {};

struct AbsToken {};

struct SqrToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

using Token = 
    std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken,
        MaxToken, AbsToken, SqrToken, Plus, Minus, Multiply, Modulo, Divide>;

// 1234

const std::unordered_map<char, Token> kSymbol2Token{
    {'+', Plus{}}, 
    {'-', Minus{}}, 
    {'*', Multiply{}}, 
    {'/', Divide{}}, 
    {'%', Modulo{}},
    {'(', OpeningBracket{}},
    {')', ClosingBracket{}}
};

using Name = std::string;
const std::unordered_map<Name, Token> kCommand2Token{
    {"max", MaxToken{}},
    {"min", MinToken{}},
    {"abs", AbsToken{}},
    {"sqr", SqrToken{}},
};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{ value };
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string name;
    name.reserve(3);
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isalpha(symbol)) {
        if (pos == input.size() - 1) {
            break;
        }
        name += symbol;
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (kCommand2Token.find(name) != kCommand2Token.end())
    {
        return kCommand2Token.at(name);
    }

    return UnknownToken(name);
}

std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
        }
        else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        }
        else if (std::isalpha(symbol)) {
            tokens.emplace_back(ParseName(input, pos));
        }
        else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
            ++pos;
        }
    }
    return tokens;
}

void homework3::testHomework3()
{
    std::string epxression = "(1 + 2) + 3 * sqr(4) + abs(-1)";
    auto tokens = Tokenize(epxression);
}