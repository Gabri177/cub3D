/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_2d_bk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:11:55 by yugao             #+#    #+#             */
/*   Updated: 2024/03/24 00:13:09 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void	bk_map(void *info) // dibujar el background 
{
	int	x;
	int	y;
	
	//img_start_draw (info);
	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
		{
			if (map[y * 8 + x] == 1)
				img_set_color (info, 0x2E8B57);
			else
				img_set_color (info, 0xF0FFF0);
			graph_square (info, (t_pos){x * UNIDAD + UNIDAD / 2, y * UNIDAD + UNIDAD / 2}, 63);
		}
	}
	//img_end_draw (info);
}