/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_2d_bk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:11:55 by yugao             #+#    #+#             */
/*   Updated: 2024/03/25 19:29:04 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//画一个2d的小背景, 根据传入的矩阵数据进行绘画
void	bk_map(void *info)
{
	int	x;
	int	y;
	
	y = -1;
	while (((t_info *)info)->mtx[0][++y])
	{
		x = -1;
		while (((t_info *)info)->mtx[++x])
		{
			if (((t_info *)info)->mtx[x][y]->obj == '1')
				img_set_color (info, 0x2E8B57);
			else
				img_set_color (info, 0xF0FFF0);
			graph_square (info, (t_pos){x * UNIDAD + UNIDAD / 2, y * UNIDAD + UNIDAD / 2}, UNIDAD - 1);
		}
	}
}

//void	bk_razer(void *info, )