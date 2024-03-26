/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:32:37 by yugao             #+#    #+#             */
/*   Updated: 2024/03/26 00:22:22 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//上下左右箭头 左右箭头控制视角, 上下箭头控制前进和后退
void    key_move(void *info)
{
	t_info	*tem;

	tem = ((t_info *)info);
	if (tem->key.up)
		tem->ctr_pos = vec_trans (tem->ctr_pos, tem->ctr_ang, TRUE);
	if (tem->key.down)
		tem->ctr_pos = vec_trans (tem->ctr_pos, tem->ctr_ang, FALSE);
	if (tem->key.left)
		tem->ctr_ang = math_projection_vec (tem->ctr_ang, -5, 5);
	if (tem->key.right)
		tem->ctr_ang = math_projection_vec (tem->ctr_ang, +5, 5);
	if (tem->key.up || tem->key.down || tem->key.left || tem->key.right)
	{
		img_start_draw (info);
		bk_map (info);
		img_set_color (info, 0xF08080);
		graph_square(info, tem->ctr_pos, 10);
		// for (int i = -30; i <= 30; i += 3)
		// {
		// 	img_set_color (info, 0x666666);
		// 	graph_draw_ray (info, biu_hit_pos (info, i));
		// }
		graph_ray_to_wall (info, 60);
		img_set_color (info, 0xFFCC00);
		graph_thick_line (info, tem->ctr_pos, (t_pos){tem->ctr_pos.x + tem->ctr_ang.vx * 3, tem->ctr_pos.y + tem->ctr_ang.vy * 3}, 2);
		img_end_draw (info);
	}
}

//触发按下的事件
int	key_press(int keycode, void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (keycode == 53)// Esc key to quit
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

//触发松开按键的事件
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
