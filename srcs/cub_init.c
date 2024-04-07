/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:53:08 by yugao             #+#    #+#             */
/*   Updated: 2024/04/07 20:59:16 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_info *info, t_parse parse)
{
	info->tex_down.img = mlx_png_file_to_image (info->mlx,
			hash_grep (parse.hash_elements, "SO"),
			&info->tex_down.tex_x, &info->tex_down.tex_y);
	info->tex_up.img = mlx_png_file_to_image (info->mlx,
			hash_grep (parse.hash_elements, "NO"),
			&info->tex_up.tex_x, &info->tex_up.tex_y);
	info->tex_left.img = mlx_png_file_to_image (info->mlx,
			hash_grep (parse.hash_elements, "WE"),
			&info->tex_left.tex_x, &info->tex_left.tex_y);
	info->tex_right.img = mlx_png_file_to_image (info->mlx,
			hash_grep (parse.hash_elements, "EA"),
			&info->tex_right.tex_x, &info->tex_right.tex_y);
	info->tex_down.addr = mlx_get_data_addr (info->tex_down.img,
			&(info->tex_down.bits_per_pixel),
			&(info->tex_down.len_line), &(info->tex_down.endian));
	info->tex_up.addr = mlx_get_data_addr (info->tex_up.img,
			&(info->tex_up.bits_per_pixel),
			&(info->tex_up.len_line), &(info->tex_up.endian));
	info->tex_left.addr = mlx_get_data_addr (info->tex_left.img,
			&(info->tex_left.bits_per_pixel),
			&(info->tex_left.len_line), &(info->tex_left.endian));
	info->tex_right.addr = mlx_get_data_addr (info->tex_right.img,
			&(info->tex_right.bits_per_pixel),
			&(info->tex_right.len_line), &(info->tex_right.endian));
}

void	init_info(t_info *info, t_parse prase,
	t_vec ori_ang, t_map map)
{
	info->mlx = mlx_init ();
	info->win = mlx_new_window (info->mlx, map.x, map.y, "cub3D");
	info->mtx = matrix_init (ori_ang);
	matrix_push (&info->mtx, prase.map);
	info->mtx_size = (t_size){(int)ori_ang.vx, (int)ori_ang.vy};
	info->map_info = map;
	info->ctr_ang = ori_ang;
	info->ctr_ang.vx = cos (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_ang.vy = sin (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_pos = init_ctr_pos (info->mtx);
	info->key.up = 0;
	info->key.down = 0;
	info->key.left = 0;
	info->key.right = 0;
	info->key.to_left = 0;
	info->key.to_right = 0;
	info->img_info.img = NULL;
	init_img (info, prase);
	info->color = 0xFFFFFF;
	info->color_sky = trans_rgb_to_dig (hash_grep (prase.hash_elements, "C"));
	info->color_floor = trans_rgb_to_dig (hash_grep (prase.hash_elements, "F"));
}

void	init_is_valid(t_parse *parse)
{
	parse->hash_elements = hash_init();
	parse->is_valid[0] = "NO";
	parse->is_valid[1] = "SO";
	parse->is_valid[2] = "WE";
	parse->is_valid[3] = "EA";
	parse->is_valid[4] = "F";
	parse->is_valid[5] = "C";
	parse->is_valid[6] = NULL;
	parse->num = 0;
}

int	is_valid(char *line, t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->is_valid[i] != NULL)
	{
		if ((ft_strcmp (line, parse->is_valid[i]) == 0))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	init_elements(t_parse *parse, char *filename)
{
	char	*line;
	char	*temp;
	int		len_to_space;
	int		fd;
	char	*value;

	init_is_valid(parse);
	fd = open(filename, O_RDONLY);
	while (parse->num != ELEMENTS_MAP)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), -1);
		len_to_space = ft_strchrlen(line, ' ');
		temp = ft_substr(line, 0, len_to_space);
		if (is_valid(temp, parse) == TRUE)
			parse->num++;
		value = ft_substr(line, len_to_space, ft_strlen(line));
		char *valfin = ft_strtrim (value, " \n");
		hash_push(parse->hash_elements, temp, valfin);
		free (valfin);
		free (value);
		free(temp);
		if (is_valid(temp, parse) == FALSE && is_space(line) != 0)
			return (close(fd), free(line), hash_destory(parse->hash_elements), -1);
		free(line);
	}
	if (map_read(parse, fd) == -1)
		return (close(fd) , -1);
	// despues si todo esta bien que esta función llame a otracomo is_valid pero que vaya guardando en la estrucutra
	close (fd);
	return (TRUE);
}
