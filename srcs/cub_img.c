/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:56:09 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 21:27:08 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//这个是初始化t_info参数中的img_info类型的函数
void	img_new(void *info)
{
	t_info	*tem;

	tem = (t_info *)info;
	tem->img_info.img = mlx_new_image (tem->mlx, tem->map_info.x, tem->map_info.y);
	tem->img_info.addr = mlx_get_data_addr (tem->img_info.img, &(tem->img_info.bits_per_pixel), &(tem->img_info.len_line), &(tem->img_info.endian));
}

//在上面的函数用完以后, 这个函数负责在我们创建的图像中画图像
void	img_put_pixel(void *info, int x, int y, int color)
{
	char	*dst;
	t_info	*tem;

	tem = (t_info *)info;
	dst = tem->img_info.addr + (y * tem->img_info.len_line + x * (tem->img_info.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//画任何东西的时候, 必须以这个函数为开始, 否则会出错
void	img_start_draw(void *info)
{
	t_info	*tem;
	
	tem = (t_info *)info;
	if (tem->img_info.img)
		mlx_put_image_to_window (tem->mlx, tem->win, tem->img_info.img, 0, 0);
	img_new (info);
}


//在结束一张画布的时候, 必须以这个函数为结束, 这样才能将画的内容推送到窗口并销毁图像
void	img_end_draw(void *info)
{
	t_info	*tem;
	
	tem = (t_info *)info;
	mlx_put_image_to_window (tem->mlx, tem->win, tem->img_info.img, 0, 0);
	mlx_destroy_image (tem->mlx, tem->img_info.img);
	tem->img_info.img = NULL;
}