/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:32:13 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/10 07:32:13 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Wordle.hpp"

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

int main( int argc, char **argv )
{
    Wordle  game;
    size_t  attempt = 1;
    str     word;

    srand( time(NULL) );

    switch (argc) {
        case 1:
            game.addDictionary("", "");
            break;
        case 2:
            if (argv[2])
                game.addDictionary(str(argv[2]), "");
            break;
        case 3:
            if (argv[2] && argv[3])
                game.addDictionary(str(argv[2]), str(argv[3]));
            break;
        default:
            return (1);
    }
    if (game.getLaDictionary().empty() || game.getTaDictionary().empty())
        return (2);
    game.chooseWord();
    Clear();
    game.displayGrid();
    while (std::cin.eof() != 1) {
        std::cout << "> ";
        std::getline(std::cin, word);
        if (game.checkWord(word)) {
            game.askWord(word);
            game.analyseWord(word);
            Clear();
            game.displayGrid();
            if (game.isWon() || attempt > 5)
                break;
            ++attempt;
        }
        else
            PRINT RED "Not a real word" CENDL;
        if (game.isWon())
            PRINT GREEN "GG" CENDL;
    }
    return (0);
}