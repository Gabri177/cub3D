/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_over.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 01:48:37 by yugao             #+#    #+#             */
/*   Updated: 2024/04/08 01:49:14 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destory_all(t_info *info, t_parse *parse)
{
	free (parse->map);
	matrix_destory (&info->mtx);
	hash_destory(parse->hash_elements);
	mlx_destroy_image (info->mlx, info->tex_down.img);
	mlx_destroy_image (info->mlx, info->tex_up.img);
	mlx_destroy_image (info->mlx, info->tex_left.img);
	mlx_destroy_image (info->mlx, info->tex_right.img);
	if (info->img_info.img)
		mlx_destroy_image (info->mlx, info->img_info.img);
	mlx_destroy_window (info->mlx, info->win);
}
