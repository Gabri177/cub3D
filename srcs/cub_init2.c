/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:33:35 by yugao             #+#    #+#             */
/*   Updated: 2024/04/08 16:18:31 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_draw(t_info info)
{
	img_start_draw (&info);
	draw_sky_and_floor ((t_info *)&info,
		info.color_sky, info.color_floor);
	graph_ray_to_wall (&info);
	bk_map (&info);
	img_set_color ((void *)&info, 0x000000);
	graph_square((void *)&info, (t_pos){info.ctr_pos.x / 64
		* 10, info.ctr_pos.y / 64 * 10}, 4);
	img_set_color (&info, 0x006400);
	graph_thick_line (&info, (t_pos){info.ctr_pos.x / 64 * 10,
		info.ctr_pos.y / 64 * 10}, (t_pos){info.ctr_pos.x / 64 * 10
		+ info.ctr_ang.vx / 2, info.ctr_pos.y / 64 * 10
		+ info.ctr_ang.vy / 2}, 2);
	img_end_draw (&info);
}

void	keep_draw(t_info info)
{
	img_start_draw (&info);
	draw_sky_and_floor ((t_info *)&info,
		info.color_sky, info.color_floor);
	graph_ray_to_wall (&info);
	bk_map (&info);
	img_set_color ((void *)&info, 0x000000);
	graph_square((void *)&info, (t_pos){info.ctr_pos.x / 64
		* 10, info.ctr_pos.y / 64 * 10}, 4);
	img_set_color (&info, 0x006400);
	graph_thick_line (&info, (t_pos){info.ctr_pos.x / 64 * 10,
		info.ctr_pos.y / 64 * 10}, (t_pos){info.ctr_pos.x / 64 * 10
		+ info.ctr_ang.vx * 3 / 2, info.ctr_pos.y / 64 * 10
		+ info.ctr_ang.vy * 3 / 2}, 2);
	img_end_draw (&info);
}

t_vec	init_vec(t_parse parse)
{
	int	ang;

	ang = 0;
	if (parse.starting_position == 'N')
		ang = 270;
	if (parse.starting_position == 'S')
		ang = 90;
	if (parse.starting_position == 'W')
		ang = 180;
	return ((t_vec){parse.width - 1, parse.height, ang});
}
