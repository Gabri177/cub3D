/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/03/25 19:33:57 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int main()
{
	t_info info;
	
	init_info(&info, (t_pos){50, 50}, (t_vec){0, 0, 90}, (t_map){1024, 510});
	//在读取地图时, 确定地图的长宽, 从而创建matrix
	info.mtx = matrix_init ((t_vec){8, 8});
	//一般在读取地图数据以后, 以这种方式存储地图的数据
	matrix_push (&info.mtx, "1111111110100001101000011010000110000001100010011010000111111111");
	matrix_display (info.mtx, TRUE);
	
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
