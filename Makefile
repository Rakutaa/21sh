# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtran <vtran@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 12:10:34 by vkuokka           #+#    #+#              #
#    Updated: 2020/06/10 16:37:20 by vtran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = srcs/main.c \
       srcs/config_signal.c \
       srcs/config_terminal.c \
       srcs/program_exit.c \
       srcs/utils.c \
       srcs/input/browse_history.c \
       srcs/input/cursor_movement_1.c \
       srcs/input/cursor_movement_2.c \
       srcs/input/init_input.c \
       srcs/input/print_input.c \
       srcs/input/search_action.c \
       srcs/interpreter/init_lexer.c \
       srcs/interpreter/parse_tokens.c \
       srcs/interpreter/ast_utils1.c \
       srcs/interpreter/ast_utils2.c \
       srcs/interpreter/ast_utils3.c \
       srcs/interpreter/ast_helpers.c \
       srcs/interpreter/dollar_tilde_utils.c \
       srcs/interpreter/helpers.c \
       srcs/interpreter/free_ast.c \
       srcs/interpreter/free_parse.c \
       srcs/interpreter/free_tokens.c \
       srcs/interpreter/parser_utils.c \
       srcs/interpreter/helper_parser_redir_aggre.c

INCL =	includes/
INCL1 = libftprintf/includes
INCL2 = libftprintf/libft/includes

LIB = ftprintf
LIBFOL = libftprintf/

all: $(NAME)
$(NAME):
	#make -C libftprintf/
	gcc -Wall -Werror -Wextra -I $(INCL) -I $(INCL1) -I $(INCL2) $(SRCS) -L$(LIBFOL) -l$(LIB) -ltermcap -o $(NAME)
clean:
	#make -C libftprintf/ clean

fclean: clean
	#make -C libftprintf/ fclean
	rm -f $(NAME)

re: fclean all
