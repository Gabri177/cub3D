/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/03/27 23:20:00 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int main()
{
	t_info info;
	int	x, y;
	
	init_info(&info, (t_pos){300, 100}, (t_vec){0, 0, 270}, (t_map){1024, 510});
	
	//在读取地图时, 确定地图的长宽, 从而创建matrix
	//!! 有必要多加一个地图维度向量, 在求交点的时候用来设置循环的深度
	//info.mtx = matrix_init ((t_vec){33, 14});
	info.mtx = matrix_init ((t_vec){8, 8});
	//一般在读取地图数据以后, 以这种方式存储地图的数据
	//matrix_push (&info.mtx, "        1111111111111111111111111        1000000000110000000000001        1011000001110000000000001        100100000000000000000000111111111101100000111000000000000110000000001100000111011111111111111110111111111011100000010001    11110111111111011101010010001    11000000110101011100000010001    10000000000000001100000010001    10000000000000001101010010001    11000001110101011111011110N0111  11110111 1110101 101111010001    11111111 1111111 111111111111    ");
	matrix_push (&info.mtx, "1111111110100001101000011010000110000001100010011010000111111111");
	matrix_display (info.mtx, TRUE);
	info.tex_down.img = mlx_png_file_to_image (info.mlx, "./texture/wood.png", &x, &y);
	info.tex_up.img = mlx_png_file_to_image (info.mlx, "./texture/mossy.png", &x, &y);
	info.tex_left.img = mlx_png_file_to_image (info.mlx, "./texture/greystone.png", &x, &y);
	info.tex_right.img = mlx_png_file_to_image (info.mlx, "./texture/redbrick.png", &x, &y);
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
	return 0;
}
