# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 21:42:20 by yugao             #+#    #+#              #
#    Updated: 2024/03/18 02:44:25 by javgao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILE = $(addprefix ./srcs/, draw.c matrix.c read_map.c error.c matrix2.c test.c)
OFILE = $(CFILE:.c=.o)
CFLAG = 
LDFLAGS = -framework OpenGL -framework AppKit 
LIBS = -L minilibx -lmlx 
NAME = cub3d

all:libft $(NAME)

$(NAME):$(OFILE)
	gcc $(OFILE) $(LIBS)  -fsanitize=address -L libft -lft $(LDFLAGS)  -o $@

%.o:%.c
	gcc $(CFLAG) -c -Imlx -DGL_SILENCE_DEPRECATION $< -o $@ 

libft:
	$(MAKE) -C libft

clean:
	rm -f $(OFILE)
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) clean -C libft

re:fclean all

.PHONY: fclean clean libft