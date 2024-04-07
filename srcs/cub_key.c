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

void	draw_ceiling_and_floor_from_middle(void *info, int colorCeiling, int colorFloor)
{
	int	screenWidth = 1060;
	int	screenHeight = 510;
	int	halfScreenHeight = screenHeight / 2;
	int	startX = 530;

	for (int y = 0; y < halfScreenHeight; y++)
	{
		for (int x = startX; x < screenWidth; x++)
		{
			img_put_pixel(info, x, y, colorCeiling); // 使用天花板颜色
		}
	}
	for (int y = halfScreenHeight; y < screenHeight; y++)
	{
		for (int x = startX; x < screenWidth; x++)
		{
			img_put_pixel(info, x, y, colorFloor); // 使用地面颜色
		}
	}
}

//用来防止碰撞墙体的函数, 如果检测到前方有墙, 则不会更新位置
// function to prevent collision with walls, does 
//not update position if a wall is detected in front of it.
static t_pos	key_check_wall(void *info, t_vec v, t_bool is_ahead)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (is_ahead && tem->mtx[(int)((tem->ctr_pos.x + v.vx * 3)
			/ UNI)][(int)((tem->ctr_pos.y +
				v.vy * 3) / UNI)]->obj == '1')
		return (tem->ctr_pos);
	if (!is_ahead && tem->mtx[(int)((tem->ctr_pos.x -
				v.vx * 3) / UNI)][(int)((tem->ctr_pos.y -
				v.vy * 3) / UNI)]->obj == '1')
		return (tem->ctr_pos);
	return (vec_trans (tem->ctr_pos, v, is_ahead));
}

//上下左右箭头 左右箭头控制视角, 上下箭头控制前进和后退
//Up/down/right/left/right/left arrows to control 
//the angle of view, up/down arrows to control forward and backward.
void	key_move(void *info)
{
	t_info	*tem;

	tem = ((t_info *)info);
	if (tem->key.up)
		tem->ctr_pos = key_check_wall (info, tem->ctr_ang, TRUE);
	if (tem->key.down)
		tem->ctr_pos = key_check_wall (info, tem->ctr_ang, FALSE);
	if (tem->key.left)
		tem->ctr_pos = key_check_wall (info, (t_vec){-tem->ctr_ang.vy, tem->ctr_ang.vx, tem->ctr_ang.ang}, FALSE);
	if (tem->key.right)
		tem->ctr_pos = key_check_wall (info, (t_vec){-tem->ctr_ang.vy, tem->ctr_ang.vx, tem->ctr_ang.ang}, TRUE);
	if (tem->key.to_left)
		tem->ctr_ang = math_projection_vec (tem->ctr_ang, -5, 5);
	if (tem->key.to_right)
		tem->ctr_ang = math_projection_vec (tem->ctr_ang, +5, 5);
	if (tem->key.up || tem->key.down || tem->key.left || tem->key.right || tem->key.to_left || tem->key.to_right)
	{
		img_start_draw (info);
		bk_map (info);
		img_set_color (info, 0xF08080);
		graph_square(info, tem->ctr_pos, 10);
		draw_ceiling_and_floor_from_middle (info, tem->color_sky, tem->color_floor);
		graph_ray_to_wall (info);
		img_set_color (info, 0xFFCC00);
		graph_thick_line (info, tem->ctr_pos, (t_pos){tem->ctr_pos.x
			+ tem->ctr_ang.vx * 3, tem->ctr_pos.y + tem->ctr_ang.vy * 3}, 2);
		img_end_draw (info);
	}
}

//触发按下的事件
//Trigger the press event
int	key_press(int keycode, void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (keycode == 53)// Esc key to quit
		exit(0);
	if (keycode == W_CODE)
		tem->key.up = 1;
	if (keycode == S_CODE)
		tem->key.down = 1;
	if (keycode == L_ARROW)
		tem->key.to_left = 1;
	if (keycode == R_ARROW)
		tem->key.to_right = 1;
	if (keycode == A_CODE)
		tem->key.left = 1;
	if (keycode == D_CODE)
		tem->key.right = 1;
	return (0);
}

//触发松开按键的事件
//Trigger the release of a key
int	key_release(int keycode, void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	if (keycode == W_CODE)
		tem->key.up = 0;
	if (keycode == S_CODE)
 		tem->key.down = 0;
	if (keycode == L_ARROW)
 		tem->key.to_left = 0;
	if (keycode == R_ARROW)
		tem->key.to_right = 0;
	if (keycode == A_CODE)
		tem->key.left = 0;
	if (keycode == D_CODE)
		tem->key.right = 0;
	return (0);
}
