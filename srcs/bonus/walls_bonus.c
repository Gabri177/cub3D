/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuarez- <jjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:30:45 by jjuarez-          #+#    #+#             */
/*   Updated: 2024/04/10 22:39:40 by jjuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	change_doors(t_mtx matrix)
{
	int	x;
	int	y;

	if (!matrix)
		return ;
	y = 0;
	while (matrix[0][y])
	{
		x = 0;
		while (matrix[x] && matrix[x][y])
		{
			if (matrix[x][y]->obj == 'D')
				matrix[x][y]->obj = 'O';
			else if (matrix[x][y]->obj == 'O')
				matrix[x][y]->obj = 'D';
			x ++;
		}
		y ++;
	}
}
