/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:57 by yugao             #+#    #+#             */
/*   Updated: 2024/03/26 02:44:37 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	graph_draw_ray(void *info, t_pos endpoint)
{
	graph_thick_line (info, ((t_info *)info)->ctr_pos, endpoint, 1);
}

void	graph_ray_to_wall(void *info, int range_ang)
{
	int		i;
	double	dis;
	int		ca;
	int		lineh;
	int		lineoff;
	t_posx	hit;
	

	i = - range_ang / 2;
	while (i < range_ang / 2)
	{
		hit = biu_hit_pos (info, i);
		if (hit.side == UPSIDE)
			img_set_color (info, 0xFFB6C1);
		else if (hit.side == DOWNSIDE)
			img_set_color (info, 0x800080);
		else if (hit.side == LEFTSIDE)
			img_set_color (info, 0x4169E1);
		else
			img_set_color (info, 0x3CB371);
		graph_draw_ray (info, trans_posx_to_pos(hit));
		ca = fix_ang (i);
		dis = math_dist2p (((t_info *)info)->ctr_pos, trans_posx_to_pos(hit)) * cos (fix_ang_to_rad(ca));
		lineh = (UNIDAD * 500) / dis;
		if (lineh > 500)
			lineh = 500;
		lineoff = 250 - (lineh >> 1);
		//printf ("dis:%f hit:(%f, %f), lineoff %d\n", dis, hit.x, hit.y, lineoff);
		if (hit.side == UPSIDE)
			img_set_color (info, 0xFFB6C1);
		else if (hit.side == DOWNSIDE)
			img_set_color (info, 0x800080);
		else if (hit.side == LEFTSIDE)
			img_set_color (info, 0x4169E1);
		else
			img_set_color (info, 0x3CB371);
		graph_thick_line(info, trans_2num_to_pos(530 + (i + range_ang / 2) * 8, lineoff), trans_2num_to_pos(530 + (i + range_ang / 2) * 8, lineoff + lineh), 8);
		i += 1;
	}
}
