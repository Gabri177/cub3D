/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/04/07 19:08:08 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks()
{
	//Borrar función,incumple la norminette
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
			if (matrix[x][y]->obj == 'N' || matrix[x][y]->obj == 'S' || matrix[x][y]->obj == 'W' || matrix[x][y]->obj == 'E')
			{
				matrix[x][y]->obj = '0';
				//printf ("==========(x : %d, y %d)========\n", x * UNI - UNI / 2, y * UNI - UNI / 2);
				return ((t_pos){x * UNI + UNI / 2, y * UNI + UNI / 2});
			}
			x ++;
		}
		y ++;
	}
	return ((t_pos){0, 0});
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_parse	parse;

	atexit(leaks);		//Borrar, incumple la norminette
	if (argc != 2)		//Importante descomentar flags al makefile
		return (printf("Error: Wrong number of arguments, only 1 expected\n"));
	get_dimension(&parse, argv[1]);
	if (map_parsing(&parse, argv[1]) == -1)
		return (-1);
	//下面的t_pos是人物的初始位置, t_vec 是人物的初始方向(前两个参数刚开始我们用来传递地图的长宽, 第三个参数是角度, 而且y轴坐标朝下) t_map是窗口的大小
	// the following t_pos is the initial position of the character, t_vec is the initial direction of the character (the first two parameters are used to pass the length and 
	//width of the map at first, the third is the angle, and the y-axis coordinates are facing down) t_map is the size of the window
	printf ("w:%d h:%d start_pos: %c\n", parse.width, parse.height, parse.starting_position);
	printf ("rgb: %u\n\n\n", trans_rgb_to_dig(strdup("255,204,0")));
	init_info(&info, parse, init_vec (parse), (t_map){1024, 510});

	//matrix_display (info.mtx, TRUE);

	//=======================
	img_start_draw (&info); //||
	//=======================
	bk_map (&info);
	img_set_color (&info, 0xF08080);
	graph_square(&info, info.ctr_pos, 10);
	draw_ceiling_and_floor_from_middle (&info, info.color_sky, info.color_floor);
	graph_ray_to_wall (&info);
	img_set_color (&info, 0x2F4F4F);
	graph_thick_line (&info, info.ctr_pos, (t_pos){info.ctr_pos.x + info.ctr_ang.vx * 1.5, info.ctr_pos.y + info.ctr_ang.vy * 1.5}, 2);
	//=======================
	img_end_draw (&info);//||
	//=======================

	mlx_hook (info.win, 2, 1L << 0, key_press, &info);
	mlx_hook (info.win, 3, 1L << 1, key_release, &info);
	mlx_loop_hook (info.mlx, (void *)key_move, &info);
	mlx_loop(info.mlx);
	free (parse.map);
	matrix_destory (&info.mtx);
	hash_destory(parse.hash_elements);
	mlx_destroy_image (info.mlx, info.tex_down.img);
	mlx_destroy_image (info.mlx, info.tex_up.img);
	mlx_destroy_image (info.mlx, info.tex_left.img);
	mlx_destroy_image (info.mlx, info.tex_right.img);
	mlx_destroy_image (info.mlx, info.img_info.img);
	mlx_destroy_window (info.mlx, info.win);
	return (0);
}
