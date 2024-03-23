# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 21:42:20 by yugao             #+#    #+#              #
#    Updated: 2024/03/23 23:00:18 by yugao            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILE = $(addprefix ./srcs/, cub_fix.c cub_graph.c cub_img.c cub_init.c cub_key.c cub_main.c cub_math.c cub_vec.c)
OFILE = $(CFILE:.c=.o)
CFLAG = 
LDFLAGS = -framework OpenGL -framework AppKit 
LIBS = -L minilibx -lmlx 
NAME = cub3d

#all:libft $(NAME)
all: $(NAME)

$(NAME):$(OFILE)
#	gcc $(OFILE) $(LIBS)  -fsanitize=address -L libft -lft $(LDFLAGS)  -o $@
	gcc $(OFILE) $(LIBS)  -fsanitize=address $(LDFLAGS)  -o $@
%.o:%.c
	gcc $(CFLAG) -c -Imlx -DGL_SILENCE_DEPRECATION $< -o $@ 

#libft:
#	$(MAKE) -C libft

clean:
	rm -f $(OFILE)
	$(MAKE) fclean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) clean -C libft

re:fclean all

.PHONY: fclean clean libft