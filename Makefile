# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnoh <jnoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 14:17:56 by jnoh              #+#    #+#              #
#    Updated: 2022/09/01 11:23:37 by jnoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	cc
CFLAGS	= 	-Wall -Werror -Wextra -I ./include
SRCS	= 	./srcs/pipex.c ./srcs/utils.c ./srcs/get_cmd_argv.c ./srcs/exec.c
HEADERS	=	./include/pipex.h ./libft/libft.h
OBJS	= 	$(SRCS:.c=.o)
LIBFT	= 	libft/libft.a
NAME	= 	pipex
RM 		= 	rm -f

define libft_call
		cd libft && $(MAKE) $(1) && cd ..
endef

$(NAME) : $(OBJS)
			$(call libft_call, all)
			$(CC) -o $(NAME) $(CFLAGS) $(OBJS) -L ./libft -lft

all	: $(NAME)

clean:
	cd libft && make clean && cd ..
	$(RM) $(OBJS)

fclean:
	cd libft && make fclean && cd ..
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

norm: norminette

norminette:
	norminette

.PHONY : all clean fclean re