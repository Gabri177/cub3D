/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 05:03:30 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 21:03:27 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main() {
	t_info info;
	
    init_info(&info, (t_pos){50, 50}, (t_vec){0, 0, 90}, (t_map2d){800, 600, 50});
	graph_thick_line(&info, (t_pos){250, 100}, (t_pos){400, 600}, 10);
	//graph_line(&info, (t_pos){0, 0}, (t_pos){500, 600});
	//graph_square(&info, (t_pos){50, 100}, 50);
	graph_rectangle(&info, (t_pos){50, 50}, (t_pos){300, 300});
	mlx_put_image_to_window (info.mlx, info.win, info.img_info.img, 0, 0);
	//mlx_destroy_image (info.mlx, info.win);
	
	mlx_loop(info.mlx);
}