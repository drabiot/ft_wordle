/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wordle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:32:18 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/13 21:36:42 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wordle.hpp"

static std::vector<str> createDictio( str path );
static str trim( cref(str) s );

Wordle::Wordle( void ) {
    this->_win      = false;
    this->_index    = 0;

    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            this->_board[i][j] = '_';
            this->_check[i][j] = '_';
        }
    }
    PRINT GREEN "Creating Wordle Grid" CENDL;
}


Wordle::~Wordle( void ) {
    PRINT GREEN "Destroy Wordle Grid" CENDL;
}

std::vector<str>    Wordle::getLaDictionary( void ) {
    return (this->_LaDictionary);
}

std::vector<str>    Wordle::getTaDictionary( void ) {
    return (this->_TaDictionary);
}

bool    Wordle::isWon( void ) {
    return (this->_win);
}

bool    Wordle::addDictionary( str dictioLaPath, str dictioTaPath ) {
    std::vector<str>    LaPath;
    std::vector<str>    TaPath;

    if (dictioLaPath.empty() && dictioTaPath.empty()) {
        LaPath = createDictio("dictionary/wordle-La.txt");
        TaPath = createDictio("dictionary/wordle-Ta.txt");
    }
    else if (dictioTaPath.empty()) {
        LaPath = createDictio(dictioLaPath);
        TaPath = LaPath;
    }
    else {
        LaPath = createDictio(dictioLaPath);
        TaPath = createDictio(dictioTaPath);
    }
    if (LaPath.empty()) {
        PRINT RED "Dictionary error: A word isn't 5 character long" CENDL;
        return (false);
    }
    this->_LaDictionary = LaPath;
    if (TaPath.empty()) {
        PRINT RED "Dictionary error: A word isn't 5 character long" CENDL;
        return (false);
    }
    this->_TaDictionary = TaPath;
    return (true);

}

void    Wordle::chooseWord( void ) {
    size_t  sizeDictio = getLaDictionary().size();
    size_t  index      = rand() % sizeDictio;

    this->_word = getLaDictionary()[index];
}

bool    Wordle::checkWord( str word ) {
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    bool foundInLa = std::find(this->_LaDictionary.begin(), this->_LaDictionary.end(), word) != this->_LaDictionary.end();
    bool foundInTa = std::find(this->_TaDictionary.begin(), this->_TaDictionary.end(), word) != this->_TaDictionary.end();

    return (foundInLa || foundInTa);
}

void Wordle::askWord( str testedWord ) {
    if (testedWord == this->_word)
        this->_win = true;
}

void Wordle::analyseWord(str word) {
    size_t index = 0;
    char c;

    std::map<char, int> count_in_word;
    std::map<char, int> validated;

    for (size_t i = 0; i < this->_word.size(); ++i)
        count_in_word[this->_word[i]]++;
    for (index = 0; index < word.size(); ++index) {
        c = word[index];
        this->_board[this->_index][index] = c;

        if (c == this->_word[index]) {
            this->_check[this->_index][index] = 'v';
            validated[c]++;
        } else if (this->_word.find(c) == std::string::npos) {
            this->_check[this->_index][index] = 'x';
        } else {
            this->_check[this->_index][index] = 'p';
        }
    }
    std::map<char, int> used;
    for (index = 0; index < word.size(); ++index) {
        c = word[index];
        if (this->_check[this->_index][index] == 'p') {
            used[c] = validated[c];
            for (size_t j = 0; j < index; ++j) {
                if (word[j] == c && this->_check[this->_index][j] == 'p')
                    used[c]++;
            }
            if (used[c] < count_in_word[c]) {
                validated[c]++;
            } else {
                this->_check[this->_index][index] = 'x';
            }
        }
    }
    this->_index++;
}

void    Wordle::displayGrid( void ) {
    size_t  index   = 0;

PRINT MAGENTA "    ______                             ____        " CENDL;
PRINT MAGENTA "   / __/ /_   _      ______  _________/ / ___      " CENDL;
PRINT MAGENTA "  / /_/ __/  | | /| / / __ \\/ ___/ __  / / _ \\   " CENDL;
PRINT MAGENTA " / __/ /_    | |/ |/ / /_/ / /  / /_/ / /  __/     " CENDL;
PRINT MAGENTA "/_/  \\_______|__/|__/\\____/_/   \\__,_/_/\\___/  " CENDL;
PRINT MAGENTA "       /_____/                                     " CENDL;

NLINE;


    for (; index < 6; ++index) {
        size_t  word    = 0;
        for (size_t space = 0; space < 18; ++space)
                PRINT " ";
        for (; word < 5; ++word) {
            PRINT " ";
            if (this->_check[index][word] == 'v')
                PRINT GREEN AND this->_board[index][word] AND BASE_COLOR;
            else if (this->_check[index][word] == 'p')
                PRINT YELLOW AND this->_board[index][word] AND BASE_COLOR;
            else if (this->_check[index][word] == 'x')
                PRINT GRAY AND this->_board[index][word] AND BASE_COLOR;
            else
                PRINT "_";
        }
        NLINE;
    }
}

void    Wordle::final( void ) {
    if (this->isWon()) {
        NLINE;
        PRINT CYAN "Congrats! You manage to found the word " AND MAGENTA AND this->_word AND CYAN " in only " AND MAGENTA AND this->_index AND CYAN " try" CENDL;
        NLINE;
    }
    else {
        NLINE;
        PRINT CYAN "Better Luck next time... The word was: " AND MAGENTA AND this->_word CENDL;
        NLINE;
    }
}

static std::vector<str> createDictio( str path ) {
    std::ifstream        file;
    std::vector<str>     dictio;
    str                  line;

    file.open(path.c_str());
    if (file.is_open()) {
        while (std::getline(file, line)) {
            line = trim(line);
            if (!line.empty())
                dictio.push_back(line);
            if (line.size() != 5) {
                dictio.clear();
                return (dictio);
            }
        }
        file.close();
    }
    return (dictio);
}

static str trim( cref(str) s ) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
        ++start;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;
    return s.substr(start, end - start);
}
