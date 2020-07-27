# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 11:41:03 by vkuokka           #+#    #+#              #
#    Updated: 2020/07/01 15:20:19 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a

SRCS =	srcs/arrays/ft_arrfree.c \
		srcs/arrays/ft_arriter.c \
		srcs/ctypes/ft_isalnum.c \
		srcs/ctypes/ft_isalpha.c \
		srcs/ctypes/ft_isascii.c \
		srcs/ctypes/ft_iscntrl.c \
		srcs/ctypes/ft_isdigit.c \
		srcs/ctypes/ft_isgraph.c \
		srcs/ctypes/ft_islower.c \
		srcs/ctypes/ft_isprint.c \
		srcs/ctypes/ft_ispunct.c \
		srcs/ctypes/ft_isspace.c \
		srcs/ctypes/ft_isspace.c \
		srcs/ctypes/ft_isupper.c \
		srcs/ctypes/ft_tolower.c \
		srcs/ctypes/ft_toupper.c \
		srcs/dlst/ft_ddel.c \
		srcs/dlst/ft_dlstadd.c \
		srcs/dlst/ft_dlstaddback.c \
		srcs/dlst/ft_dlstdel.c \
		srcs/dlst/ft_dlstdelone.c \
		srcs/dlst/ft_dlstiter.c \
		srcs/dlst/ft_dlstlen.c \
		srcs/dlst/ft_dlstmap.c \
		srcs/dlst/ft_dlstnew.c \
		srcs/numbers/ft_atoi.c \
		srcs/numbers/ft_count_digits.c \
		srcs/numbers/ft_ftoa.c \
		srcs/numbers/ft_itoa_base.c \
		srcs/numbers/ft_itoa.c \
		srcs/lst/ft_del.c \
		srcs/lst/ft_lstadd.c \
		srcs/lst/ft_lstaddback.c \
		srcs/lst/ft_lstdel.c \
		srcs/lst/ft_lstdelone.c \
		srcs/lst/ft_lstiter.c \
		srcs/lst/ft_lstlen.c \
		srcs/lst/ft_lstmap.c \
		srcs/lst/ft_lstnew.c \
		srcs/memory/ft_bzero.c \
		srcs/memory/ft_memalloc.c \
		srcs/memory/ft_memccpy.c \
		srcs/memory/ft_memchr.c \
		srcs/memory/ft_memcmp.c \
		srcs/memory/ft_memcpy.c \
		srcs/memory/ft_memdel.c \
		srcs/memory/ft_memmove.c \
		srcs/memory/ft_memset.c \
		srcs/print/ft_putchar_fd.c \
		srcs/print/ft_putchar.c \
		srcs/print/ft_putendl_fd.c \
		srcs/print/ft_putendl.c \
		srcs/print/ft_putnbr_fd.c \
		srcs/print/ft_putnbr.c \
		srcs/print/ft_putstr_fd.c \
		srcs/print/ft_putstr.c \
		srcs/printf/ft_dprintf.c \
		srcs/printf/ft_printf.c \
		srcs/printf/parse.c \
		srcs/printf/parse_c.c \
		srcs/printf/parse_s.c \
		srcs/printf/parse_p.c \
		srcs/printf/parse_di.c \
		srcs/printf/parse_o.c \
		srcs/printf/parse_u.c \
		srcs/printf/parse_lower_x.c \
		srcs/printf/parse_upper_x.c \
		srcs/printf/parse_f.c \
		srcs/printf/putprint.c \
		srcs/strings/ft_strcat.c \
		srcs/strings/ft_strchr.c \
		srcs/strings/ft_strclen.c \
		srcs/strings/ft_strclr.c \
		srcs/strings/ft_strcmp.c \
		srcs/strings/ft_strcpy.c \
		srcs/strings/ft_strdel.c \
		srcs/strings/ft_strdup.c \
		srcs/strings/ft_strequ.c \
		srcs/strings/ft_striter.c \
		srcs/strings/ft_striteri.c \
		srcs/strings/ft_strjoin.c \
		srcs/strings/ft_strlcat.c \
		srcs/strings/ft_strlen.c \
		srcs/strings/ft_strmap.c \
		srcs/strings/ft_strmapi.c \
		srcs/strings/ft_strncat.c \
		srcs/strings/ft_strncmp.c \
		srcs/strings/ft_strncpy.c \
		srcs/strings/ft_strnequ.c \
		srcs/strings/ft_strnew.c \
		srcs/strings/ft_strnstr.c \
		srcs/strings/ft_strrchr.c \
		srcs/strings/ft_strreplace.c \
		srcs/strings/ft_strsplit.c \
		srcs/strings/ft_strspn.c \
		srcs/strings/ft_strstr.c \
		srcs/strings/ft_strsub.c \
		srcs/strings/ft_strtrim.c \
		srcs/swap/ft_swap_char.c \
		srcs/swap/ft_swap_str.c \
		srcs/swap/ft_swap.c \
		srcs/get_next_line.c \

OBJ =	$(notdir $(SRCS:.c=.o))

FLAGS = -Wall -Werror -Wextra

INCL =	includes/

all: $(NAME)

$(NAME):
	@echo "Creating object files.."
	@gcc $(FLAGS) -I $(INCL) -c $(SRCS)
	@echo "Creating library..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Done"

clean:
	@echo "Removing object files..."
	@rm -f $(OBJ)
	@echo "Done"

fclean: clean
	@echo "Removing library..."
	@rm -f $(NAME)
	@echo "Done"

re: fclean all
