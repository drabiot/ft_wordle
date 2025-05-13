/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:32:13 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/13 21:37:08 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Wordle.hpp"

void Clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

int main( int argc, char **argv )
{
    if (argc == 2 && argv[1] && str(argv[1]) == "help") {
        NLINE;
        PRINT YELLOW "How to use: ft_wordle" CENDL;
        NLINE;
        PRINT CYAN "To use this program, do: " MAGENTA "./ft_wordle " CYAN "to have a classic wordle with the built-in dictionary" CENDL;
        PRINT CYAN "You can also use: " MAGENTA "./ft_wordle <path_to_your_dictionary> " CYAN "or " MAGENTA "./ft_wordle <path_to_your_answer_dictionary> <path_to_all_correct_answer_dictionary>" CENDL;
        NLINE;
        PRINT YELLOW "And have fun :D" CENDL;
        NLINE;
        return (0);
    }

    Wordle  game;
    size_t  attempt = 1;
    str     word;

    srand( time(NULL) );

    switch (argc) {
        case 1:
            if (!game.addDictionary("", ""))
                return (2);
            break;
        case 2:
            if (argv[1])
                if (!game.addDictionary(str(argv[1]), ""))
                    return (2);
            break;
        case 3:
            if (argv[1] && argv[2])
                if (!game.addDictionary(str(argv[1]), str(argv[2])))
                    return (2);
            break;
        default:
            return (1);
    }
    if (game.getLaDictionary().empty() || game.getTaDictionary().empty()) {
        PRINT "test" ENDL;
        return (2);
        }
    game.chooseWord();
    Clear();
    game.displayGrid();
    while (std::cin.eof() != 1) {
        std::cout << "> ";
        std::getline(std::cin, word);
        if (word.size() != 5)
            PRINT RED "Input error: Need to be a 5 charater word" CENDL;
        else if (game.checkWord(word)) {
            game.askWord(word);
            game.analyseWord(word);
            Clear();
            game.displayGrid();
            if (game.isWon() || attempt > 5)
                break;
            ++attempt;
        }
        else
            PRINT RED "Input error: Not a real word" CENDL;
    }
    game.final();
    return (0);
}