# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 07:22:39 by tchartie          #+#    #+#              #
#    Updated: 2025/05/10 07:22:39 by tchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME		=	ft_wordle

#========= COMPILATOR =========#

CPP			=	c++

#=========== FLAGS ============#

CFLAGS		=	-Wall -Wextra -Werror -std=c++98	

#=========== COLOR ============#

BASE_COLOR 	=	\033[0;39m
GRAY 		=	\033[0;90m
RED 		=	\033[0;91m
GREEN 		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE 		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN 		=	\033[0;96m
WHITE		=	\033[0;97m

#========== SOURCES ===========#

INC_DIR		=		inc
SRC_DIR		=		src/
OBJS_DIR	=		obj/

INCLUDE		=		$(foreach d, $(INC_DIR), -I$d)
SRCS 		=		main.cpp
OBJS		=		$(SRCS:.cpp=.o)


SRCS_F		=		$(addprefix $(SRCS_DIR),$(SRCS))
OBJS_F		=		$(addprefix $(OBJS_DIR),$(OBJS))

all : 				$(NAME)

$(NAME) :			$(OBJS_F)
					@$(CPP) $(CFLAGS) $(OBJS_F) -o $(NAME) -I$(INC_DIR)
					@echo "$(GREEN)ft_wordle successfully compiled! $(BASE_COLOR)"

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCLUDE)
					@mkdir -p $(OBJS_DIR)
					@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
					@$(CC) $(GFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
					@rm -rf $(OBJS_DIR)
					@echo "$(BLUE)ft_wordle objects files cleanned! $(BASE_COLOR)"

fclean :			clean
					@rm -rf $(NAME)
					@echo "$(CYAN)ft_wordle executable file cleanned! $(BASE_COLOR)"

re :				fclean all

.PHONY :			all clean fclean re