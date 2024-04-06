/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:40:59 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/06 04:52:54 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*add_space(t_parse *parse, char *line)
{
	int		line_len;
	int		i;
	char	*new_line;
	
	line_len = ft_strlen(line);
	i = 0;
	new_line = malloc (parse->width + 1); //Ver si tiene que ser + 1
	while (i < line_len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < parse->width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
