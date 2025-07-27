# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emma <emma@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 11:25:38 by sthiagar          #+#    #+#              #
#    Updated: 2024/04/15 02:23:44 by emma             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
SOURCE = ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_is_strdigit.c \
	 ft_lstnew.c ft_lstlast.c ft_lstadd_back.c ft_lstsize.c \
	 ft_strlen.c  ft_calloc.c ft_bzero.c ft_memcpy.c \
	 ft_atoi.c ft_split.c ft_strjoin.c ft_strjoin2.c ft_strjoin3.c \
	 ft_strdup.c ft_strncmp.c  ft_strchr.c ft_chrindex.c ft_strchrind.c \
	 ft_substr.c ft_strbef_chr.c ft_strbef_chridx.c ft_strrchr.c \
	 ft_strslice_btwidx.c ft_strslice_btwchr.c \
	 ft_toupper.c ft_is_strequal.c ft_substr_idx.c \
	 ft_putstr_fd.c ft_itoa.c ft_strlcpy.c \
	 ft_strncmp_uc.c  ft_lstnew2.c

OBJECT = ./$(SOURCE:.c=.o)
HEADER = ./libft.h

all: $(NAME)

$(NAME):	$(OBJECT)
			ar rc $(NAME) $(OBJECT)

./%.o: ./%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJECT)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY:= all clean fclean re
