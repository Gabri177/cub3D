/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_anime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:03:58 by javgao            #+#    #+#             */
/*   Updated: 2024/04/11 21:16:25 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	init_anime(t_info *info)
{
	info->anime.ani1 = mlx_xpm_file_to_image (info->mlx,
			hash_grep (parse.hs, "SO"),
			&info->anime.ani1.tex_x, &info->anime.ani1.tex_y);
	if (info->anime.ani1.img == NULL)
		return (-1);
	info->tex_up.img = mlx_xpm_file_to_image (info->mlx,
			hash_grep (parse.hs, "NO"),
			&info->tex_up.tex_x, &info->tex_up.tex_y);
	if (info->tex_up.img == NULL)
		return (-1);
	info->tex_left.img = mlx_xpm_file_to_image (info->mlx,
			hash_grep (parse.hs, "WE"),
			&info->tex_left.tex_x, &info->tex_left.tex_y);
	if (info->tex_left.img == NULL)
		return (-1);
	info->tex_right.img = mlx_xpm_file_to_image (info->mlx,
			hash_grep (parse.hs, "EA"),
			&info->tex_right.tex_x, &info->tex_right.tex_y);
	if (info->tex_right.img == NULL)
		return (-1);
	info->door.img =  mlx_xpm_file_to_image(info->mlx,
			IMG_DOOR, &info->door.tex_x, &info->door.tex_y);
	if (info->door.img == NULL)
		return (-1);
	return (0);
}