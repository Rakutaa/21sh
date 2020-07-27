# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 12:10:34 by vkuokka           #+#    #+#              #
#    Updated: 2020/07/27 14:55:16 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = srcs/config_termcaps.c \
       srcs/init_history.c \
       srcs/main.c \
       srcs/program_exit.c \
       srcs/save_history.c \
       srcs/utils.c \
       srcs/input/browse_history.c \
       srcs/input/config_signal.c \
       srcs/input/config_terminal.c \
       srcs/input/cursor_movement_1.c \
       srcs/input/cursor_movement_2.c \
       srcs/input/init_input.c \
       srcs/input/listen_keys.c \
       srcs/input/print_input.c \
       srcs/input/search_action.c \
       srcs/input/shell_clipboard.c \
       srcs/input/start_editor.c \
       srcs/interpreter/buildin_helpers.c \
       srcs/interpreter/cd.c \
       srcs/interpreter/echo.c \
       srcs/interpreter/envs.c \
       srcs/interpreter/init_lexer.c \
       srcs/interpreter/lexer_helper.c \
       srcs/interpreter/parse_tokens.c \
       srcs/interpreter/ast_utils1.c \
       srcs/interpreter/ast_utils2.c \
       srcs/interpreter/ast_utils3.c \
       srcs/interpreter/ast_helpers.c \
       srcs/interpreter/dollar_tilde_utils.c \
       srcs/interpreter/struct_for_exit.c \
       srcs/interpreter/re_ag.c \
       srcs/interpreter/re_ag_dub.c \
       srcs/interpreter/re_ag_dub2.c \
       srcs/interpreter/helpers.c \
       srcs/interpreter/free_ast.c \
       srcs/interpreter/free_env.c \
       srcs/interpreter/free_parse.c \
       srcs/interpreter/free_tokens.c \
       srcs/interpreter/parser_utils.c \
       srcs/interpreter/token_syntax.c \
       srcs/interpreter/tokenize.c \
       srcs/interpreter/helper_parser_redir_aggre.c

INCL = includes/

LIB = ft
LIBFOL = libft/
LIBINCL = libft/includes/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)
$(NAME):
	@echo "Building library..."
	@make -C libft/
	@echo "Compiling program..."
	@gcc $(FLAGS) -I $(INCL) -I $(LIBINCL) $(SRCS) -L$(LIBFOL) -l$(LIB) -ltermcap -o $(NAME)
	@echo "Done"
clean:
	-@make -C libft/ clean
fclean: clean
	-@make -C libft/ fclean
	@echo "Removing binary..."
	@rm -f $(NAME)
	@echo "Done"
re: fclean all