/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:53:08 by yugao             #+#    #+#             */
/*   Updated: 2024/03/25 21:10:18 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_info(t_info *info, t_pos ori_pos, t_vec ori_ang, t_map map)
{
	info->mlx = mlx_init ();
	info->win = mlx_new_window (info->mlx, map.x, map.y, "cub3D");
	info->map_info = map;
	info->ctr_ang = ori_ang;
	info->ctr_ang.vx = cos (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_ang.vy = sin (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_pos = ori_pos;
	info->key.up = 0;
	info->key.down = 0;
	info->key.left = 0;
	info->key.right = 0;
	info->mtx = NULL;
	info->color = 0xFFFFFF;
}
