/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 21:28:14 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main() {
	t_info info;
	
	init_info(&info, (t_pos){50, 50}, (t_vec){0, 0, 90}, (t_map2d){800, 600, 50});
	//=======================
	img_start_draw (&info); 
	//=======================

	
	graph_thick_line(&info, (t_pos){250, 100}, (t_pos){400, 600}, 10);
	graph_rectangle(&info, (t_pos){50, 50}, (t_pos){300, 300});

	
	//=======================
	img_end_draw (&info);
	//=======================
	mlx_hook (info.win, 2, 1L<<0, key_press, &info);
	mlx_hook (info.win, 3, 1L<<1, key_release, &info);
	mlx_loop_hook (info.mlx, (void *)key_move, &info);
	mlx_loop(info.mlx);
}