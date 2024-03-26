/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:57 by yugao             #+#    #+#             */
/*   Updated: 2024/03/26 01:45:02 by yugao            ###   ########.fr       */
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
	t_pos	hit;
	

	i = - range_ang / 2;
	while (i < range_ang / 2)
	{
		hit = biu_hit_pos (info, i);
		img_set_color (info, 0x666666);
		graph_draw_ray (info, hit);
		ca = fix_ang (((t_info *)info)->ctr_ang.ang + i);
		dis = math_dist2p (((t_info *)info)->ctr_pos, hit) ;
		lineh = (UNIDAD * 320) / dis;
		if (lineh > 320)
			lineh = 320;
		lineoff = 160 - (lineh >> 1);
		printf ("dis:%f hit:(%f, %f), lineoff %d\n", dis, hit.x, hit.y, lineoff);
		img_set_color (info, 0xFFCC33);
		graph_thick_line(info, (t_pos){1024 / 3 * 2 + i * 8, lineoff}, (t_pos){1024 / 3 * 2 + i * 8, lineoff + lineh}, 8);
		i += 1;
	}
}
