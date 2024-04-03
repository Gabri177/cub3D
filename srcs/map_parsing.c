/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:57:42 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/03 15:53:49 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_cub_extension_and_file(char *filename)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(filename, '.');
	if (!(ft_strcmp(extension, ".cub") == 0))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-2);
	close (fd);
	return (0);
}

int	check_invalid_characters(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == ' '
			|| (line[i] >= 9 && line[i] <= 13))
			i++;
		else
		{
			perror("Error: data file contains invalid characters:");
			return (-1);
		}
	}
	// Llamar a una función que comprueebe que esta rodeado de 1
	return (0);
}

int	map_read(t_parse *parse, int fd)
{
	char	*line;
	char	*join;
	char	*temp;
	char	*out_nl;

	join = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_invalid_characters(line) == -1)
			return (free(line), free(join), -1);
		out_nl = ft_strtrim(line, "\n");
		temp = ft_strjoin(join, out_nl);
		free(out_nl);
		free (join);
		join = ft_strdup(temp);
		// Si todo esta bien ir guardando en un char * todo el mapa
		free (temp);
		free(line);
		line = get_next_line(fd);
	}
	parse->map = ft_strdup(join);
	free(join);
	return (0);
}

int	map_parsing(t_parse *parse, char *filename)
{
	if (check_cub_extension_and_file(filename) == -1)
		return (perror("Error: file extension of the map isn't .cub"), -1);
	if (check_cub_extension_and_file(filename) == -2)
		return (perror("Error: map file doesn't exist"), -1);
	if (init_elements(parse, filename) == -1)
		return (perror("Erorr: invalid element on the map"), -1);
	// Borrar desde aquí
	printf("--------------------- T_PARSE ---------------------\n\n");
	printf("Map:%s\n\n", parse->map);
	hash_display(*parse->hash_elements);
	hash_destory(parse->hash_elements);
	// Borrar hasta aquí
	return (0);
}
