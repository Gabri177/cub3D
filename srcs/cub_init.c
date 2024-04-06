/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:53:08 by yugao             #+#    #+#             */
/*   Updated: 2024/04/06 02:41:30 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_info(t_info *info, t_pos ori_pos,
	t_vec ori_ang, t_map map, t_parse *parse)
{
	info->mlx = mlx_init ();
	info->win = mlx_new_window (info->mlx, map.x, map.y, "cub3D");
	info->mtx = matrix_init (ori_ang);
	info->mtx_size = (t_size){(int)ori_ang.vx, (int)ori_ang.vy};
	info->map_info = map;
	info->ctr_ang = ori_ang;
	info->ctr_ang.vx = cos (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_ang.vy = sin (fix_ang_to_rad (ori_ang.ang)) * 15;
	info->ctr_pos = ori_pos;
	info->key.up = 0;
	info->key.down = 0;
	info->key.left = 0;
	info->key.right = 0;
	info->img_info.img = NULL;
	//info->mtx = NULL;
	info->color = 0xFFFFFF;
	(void)parse;
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
	parse->height = 0;
	parse->width = 0;
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
		hash_push(parse->hash_elements, temp, value);
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
