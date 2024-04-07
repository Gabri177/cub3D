/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/04/07 21:13:38 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks()
{
	system("leaks -q cub3d");
}

static t_vec	init_vec(t_parse parse)
{
	int	ang;

	ang = 0;
	if (parse.starting_position == 'N')
		ang = 270;
	if (parse.starting_position == 'S')
		ang = 90;
	if (parse.starting_position == 'W')
		ang = 180;
	return ((t_vec){parse.width - 1, parse.height, ang}); // menos unos hay que corregir lo sobre parser
}

t_pos	init_ctr_pos(t_mtx matrix)
{
	int	x;
	int	y;

	y = 0;
	while (matrix[0][y])
	{
		x = 0;
		while (matrix[x] && matrix[x][y])
		{
			if (matrix[x][y]->obj == 'N' || matrix[x][y]->obj == 'S'
				|| matrix[x][y]->obj == 'W' || matrix[x][y]->obj == 'E')
			{
				matrix[x][y]->obj = '0';
				return ((t_pos){x * UNI + UNI / 2, y * UNI + UNI / 2});
			}
			x ++;
		}
		y ++;
	}
	return ((t_pos){0, 0});
}

t_bool	map_check(t_mtx mtx, t_size size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (mtx[x][y]->obj == '0')
			{
				if (!mtx[x][y - 1] || mtx[x][y - 1]->obj != '1' && mtx[x][y - 1]->obj != '0')
					return (FALSE);
				if (!mtx[x][y + 1] || mtx[x][y + 1]->obj != '1' && mtx[x][y + 1]->obj != '0')
					return (FALSE);
				if (!mtx[x - 1][y] || mtx[x - 1][y]->obj != '1' && mtx[x - 1][y]->obj != '0')
					return (FALSE);
				if (!mtx[x + 1][y] || mtx[x + 1][y]->obj != '1' && mtx[x + 1][y]->obj != '0')
					return (FALSE);
			}
			x ++;
		}
		y ++;
	}
	return (TRUE);
}

static void	destory_all(t_info *info, t_parse *parse)
{
	free (parse->map);
	matrix_destory (&info->mtx);
	hash_destory(parse->hash_elements);
	mlx_destroy_image (info->mlx, info->tex_down.img);
	mlx_destroy_image (info->mlx, info->tex_up.img);
	mlx_destroy_image (info->mlx, info->tex_left.img);
	mlx_destroy_image (info->mlx, info->tex_right.img);
	if (info->img_info.img)
		mlx_destroy_image (info->mlx, info->img_info.img);
	mlx_destroy_window (info->mlx, info->win);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_parse	parse;

	atexit(leaks);
	if (argc != 2)
		return (printf("Error: Wrong number of arguments, only 1 expected\n"));
	get_dimension(&parse, argv[1]);
	if (map_parsing(&parse, argv[1]) == -1)
		return (-1);
	init_info(&info, parse, init_vec (parse), (t_map){1024, 510});
	if (map_check (info.mtx, info.mtx_size) == FALSE)
	{
		printf ("Cub3d: no cerrar con 1\n");
		destory_all (&info, &parse);
		exit (0);
	}
	//matrix_display (info.mtx, TRUE);
	init_draw (info);
	mlx_hook (info.win, 2, 1L << 0, key_press, &info);
	mlx_hook (info.win, 3, 1L << 1, key_release, &info);
	mlx_loop_hook (info.mlx, (void *)key_move, &info);
	mlx_loop(info.mlx);
	destory_all (&info, &parse);
	return (0);
}
