/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:33:35 by yugao             #+#    #+#             */
/*   Updated: 2024/04/07 20:53:22 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_draw(t_info info)
{
	img_start_draw (&info);
	bk_map (&info);
	img_set_color (&info, 0xF08080);
	graph_square(&info, info.ctr_pos, 10);
	draw_sky_and_floor ((t_info *)&info,
		info.color_sky, info.color_floor);
	graph_ray_to_wall (&info);
	img_set_color (&info, 0x2F4F4F);
	graph_thick_line (&info, info.ctr_pos, (t_pos){info.ctr_pos.x
		+ info.ctr_ang.vx * 1.5, info.ctr_pos.y + info.ctr_ang.vy * 1.5}, 2);
	img_end_draw (&info);
}
