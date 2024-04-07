/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/04/07 17:51:57 by yugao            ###   ########.fr       */
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

int main(int argc, char **argv)
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
	init_info(&info, parse, init_vec (parse), (t_map){1024, 510});
	//init_info(&info, (t_pos){100, 100}, (t_vec){8, 8, 270}, (t_map){1024, 510}, &parse);

	//matrix_display (info.mtx, TRUE);
	info.tex_down.img = mlx_png_file_to_image (info.mlx, "./texture/wood.png", &info.tex_down.tex_x, &info.tex_down.tex_y);
	info.tex_up.img = mlx_png_file_to_image (info.mlx, "./texture/eagle.png", &info.tex_up.tex_x, &info.tex_up.tex_y);
	info.tex_left.img = mlx_png_file_to_image (info.mlx, "./texture/colorstone.png", &info.tex_left.tex_x, &info.tex_left.tex_y);
	info.tex_right.img = mlx_png_file_to_image (info.mlx, "./texture/redbrick.png", &info.tex_right.tex_x, &info.tex_right.tex_y);
	// info.tex_down.img = mlx_xpm_file_to_image(info.mlx, "./texture/blue_stone.xpm", &x, &y);
	// info.tex_up.img = mlx_xpm_file_to_image(info.mlx, "./texture/grey_stone.xpm", &x, &y);
	// info.tex_left.img = mlx_xpm_file_to_image(info.mlx, "./texture/purple_stone.xpm", &x, &y);
	// info.tex_right.img = mlx_xpm_file_to_image(info.mlx, "./texture/wood.xpm", &x, &y);
	
	info.tex_down.addr = mlx_get_data_addr (info.tex_down.img, &(info.tex_down.bits_per_pixel), &(info.tex_down.len_line), &(info.tex_down.endian));
	info.tex_up.addr = mlx_get_data_addr (info.tex_up.img, &(info.tex_up.bits_per_pixel), &(info.tex_up.len_line), &(info.tex_up.endian));
	info.tex_left.addr = mlx_get_data_addr (info.tex_left.img, &(info.tex_left.bits_per_pixel), &(info.tex_left.len_line), &(info.tex_left.endian));
	info.tex_right.addr = mlx_get_data_addr (info.tex_right.img, &(info.tex_right.bits_per_pixel), &(info.tex_right.len_line), &(info.tex_right.endian));
	//=======================
	img_start_draw (&info); //||
	//=======================
	bk_map (&info);
	img_set_color (&info, 0xF08080);
	graph_square(&info, info.ctr_pos, 10);
	img_set_color (&info, 0x2F4F4F);
	graph_thick_line (&info, info.ctr_pos, (t_pos){info.ctr_pos.x + info.ctr_ang.vx * 1.5, info.ctr_pos.y + info.ctr_ang.vy * 1.5}, 2);
	//=======================
	img_end_draw (&info);//||
	//=======================

	mlx_hook (info.win, 2, 1L<<0, key_press, &info);
	mlx_hook (info.win, 3, 1L<<1, key_release, &info);
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
