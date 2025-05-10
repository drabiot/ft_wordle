/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wordle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:28:12 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/10 12:28:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WORDLE_HPP
# define WORDLE_HPP

# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <fstream>
# include <algorithm>
# include <cctype>
# include "color.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

class Wordle {
    public:
        Wordle( void );
        ~Wordle( void );

        std::vector<str>    getLaDictionary( void );
        std::vector<str>    getTaDictionary( void );
        bool                isWon( void );

        void                addDictionary( str dictioLaPath, str dictioTaPath );
        void                chooseWord( void );
        bool                checkWord( str word );
        void                askWord( str testedWord );
        void                analyseWord( str word );
        void                displayGrid( void );

    private:
        std::vector<str>    _LaDictionary;
        std::vector<str>    _TaDictionary;
        str                 _word;
        bool                _win;
        char                _board[6][5];
        char                _check[6][5];
        size_t              _index;
    };

#endif //WORDLE_HPP