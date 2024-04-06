/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:31:39 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/06 02:37:25 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_width(t_parse *parse, char *line)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line_len > parse->width)
		parse->width = line_len;
}