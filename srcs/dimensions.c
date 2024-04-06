/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:31:39 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/06 04:34:51 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_dimension(t_parse *parse, char *filename)
{
	int		fd;
	char	*line;
	fd = open(filename, O_RDONLY);

	parse->height = 0;
	parse->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		free (line);
		if (check_invalid_characters(line, 0) == 0 && is_space(line) == -1)
		{
			printf("hola\n");
			get_width(parse, line);
			parse->height++;
		}
		line = get_next_line(fd); 
	}
	close (fd);
}

void	get_width(t_parse *parse, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > parse->width)
		parse->width = line_len;
}