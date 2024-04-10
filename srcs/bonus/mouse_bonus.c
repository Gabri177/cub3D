/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:08:51 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/10 17:50:27 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	mouse_move_hook(int x, int y, t_info *info)
{
	(void)y;
	mlx_mouse_move(info->win,  info->map_info.x/ 2,  info->map_info.y/ 2);
	info->ctr_ang = math_projection_vec (info->ctr_ang,
			-(info->map_info.x/ 2 - x) /2, -(info->map_info.x/ 2 - x)/ 2);
	keep_draw (*info);
	return (0);
}
