/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/04/04 02:52:39 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	leaks()
{
	//Borrar función,incumple la norminette
	system("leaks -q cub3d");
}

int main(int argc, char **argv)
{
	t_info	info;
	t_parse	parse;
	
	atexit(leaks);		//Borrar, incumple la norminette
	//if (argc != 2)		//Importante descomentar flags al makefile
	// 	return (printf("Error: Wrong number of arguments, only 1 expected\n"));
	// if (map_parsing(&parse, argv[1]) == -1)
	// 	return (-1);
	//下面的t_pos是人物的初始位置, t_vec 是人物的初始方向(前两个参数刚开始我们用来传递地图的长宽, 第三个参数是角度, 而且y轴坐标朝下) t_map是窗口的大小
	// the following t_pos is the initial position of the character, t_vec is the initial direction of the character (the first two parameters are used to pass the length and 
	//width of the map at first, the third is the angle, and the y-axis coordinates are facing down) t_map is the size of the window
	//init_info(&info, (t_pos){700, 100}, (t_vec){33, 14, 270}, (t_map){1024, 510}, &parse);
	init_info(&info, (t_pos){100, 100}, (t_vec){8, 8, 270}, (t_map){1024, 510}, &parse);
	//一般在读取地图数据以后, 以这种方式存储地图的数据
	//Generally after reading the map data, the map data is stored in this way.
	//matrix_push (&info.mtx, "        1111111111111111111111111        1000000000110000000000001        1011000001110000000000001        100100000000000000000000111111111101100000111000000000000110000000001100000111011111111111111110111111111011100000010001    11110111111111011101010010001    11000000110101011100000010001    10000000000000001100000010001    10000000000000001101010010001    11000001110101011111011110N0111  11110111 1110101 101111010001    11111111 1111111 111111111111    ");
	matrix_push (&info.mtx, "1111111110100001101000011010000110000001100010011010000111111111");
	//matrix_push (&info.mtx, parse.map);
	matrix_display (info.mtx, TRUE);
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
	matrix_destory (&info.mtx);
	hash_destory(parse.hash_elements);
	return 0;
}
