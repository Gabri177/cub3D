/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:51:23 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 20:52:50 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//这里传入的是一个t_info类型的 但是必须要求t_info里的img_info已经通过new_img函数进行初始化才可以
static void	graph_line(void *info, t_pos p1, t_pos p2)
{
	double	dx;
	double	dy;
	double	e;
	int		i;

	i = -1;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) > fabs(dy))
		e = dx;
	else
		e = dy;
	dx = dx / e;
	dy = dy / e;
	while (++ i < e)
	{
		img_put_pixel(info, (int)(p1.x + 0.5), (int)(p1.y + 0.5), 0x2E8B57);
		//mlx_pixel_put(((t_info *)(info))->mlx, ((t_info *)(info))->win, (int)(p1.x + 0.5), (int)(p1.y + 0.5), 0x2E8B57);
		p1.x += dx;
		p1.y += dy;
	}
}

void	graph_thick_line(void *info, t_pos p1, t_pos p2, double thick)
{
	double	mid;
	int		i;

	if (thick == 0)
		thick = 1;
	mid = (thick / 2);
	i = 0;
	while (i < 2 * mid)
	{
		graph_line (info, (t_pos){p1.x - mid + i, p1.y - mid}, (t_pos){p2.x - mid + i, p2.y - mid});
		i ++;
	}
}

void	graph_square(void *info, t_pos p_center, int len_side)
{
	graph_thick_line (info, (t_pos){p_center.x, p_center.y - (int)(len_side / 2 + 0.5)}, (t_pos){p_center.x, p_center.y + (int)(len_side / 2 + 0.5)}, len_side);
}

void	graph_rectangle(void *info, t_pos p_low_left, t_pos p_up_right)
{
	int	i;

	i = p_low_left.x;
	while (i <= p_up_right.x)
	{
		graph_thick_line (info, (t_pos){p_low_left.x + i, p_low_left.y}, (t_pos){p_low_left.x + i, p_up_right.y}, 1);
		i ++;
	}
}
