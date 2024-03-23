/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:32:37 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 22:45:58 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    key_move(void *info)
{
	t_info	*tem;

	tem = ((t_info *)info);
	if (tem->key.up)
	{
		tem->ctr_pos.x += tem->ctr_ang.vx;
		tem->ctr_pos.y += tem->ctr_ang.vy;
	}
	if (tem->key.down)
	{
		tem->ctr_pos.x -= tem->ctr_ang.vx;
		tem->ctr_pos.y -= tem->ctr_ang.vy;
	}
	if (tem->key.left)
	{
		tem->ctr_ang.ang = fix_ang (tem->ctr_ang.ang + 5);
		tem->ctr_ang.vx = cos (fix_ang_to_rad (tem->ctr_ang.ang)) * 15;
		tem->ctr_ang.vy = - sin (fix_ang_to_rad (tem->ctr_ang.ang)) * 15;
	}
	if (tem->key.right)
	{
		tem->ctr_ang.ang = fix_ang (tem->ctr_ang.ang - 5);
		tem->ctr_ang.vx = cos (fix_ang_to_rad (tem->ctr_ang.ang)) * 15;
		tem->ctr_ang.vy = - sin (fix_ang_to_rad (tem->ctr_ang.ang)) * 15;
	}
	img_start_draw (info);
	img_set_color (info, 0x00FF7F);
	graph_square(info, tem->ctr_pos, 10);
	img_set_color (info, 0x48D1CC);
	graph_thick_line (info, tem->ctr_pos, (t_pos){tem->ctr_pos.x + tem->ctr_ang.vx * 1.5, tem->ctr_pos.y + tem->ctr_ang.vy * 1.5}, 2);
	img_end_draw (info);
}

int	key_press(int keycode, void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (keycode == 53) // Esc key to quit
		exit(0);
	if (keycode == 126) // Up arrow
		tem->key.up = 1;
	if (keycode == 125) // Down arrow
		tem->key.down = 1;
	if (keycode == 123) // Left arrow
		tem->key.left = 1;
	if (keycode == 124) // Right arrow
		tem->key.right = 1;
	return (0);
}

int	key_release(int keycode, void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (keycode == 126) // Up arrow
		tem->key.up = 0;
	if (keycode == 125) // Down arrow
		tem->key.down = 0;
	if (keycode == 123) // Left arrow
		tem->key.left = 0;
	if (keycode == 124) // Right arrow
		tem->key.right = 0;
	return (0);
}