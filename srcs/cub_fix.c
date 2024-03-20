/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_fix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:38 by yugao             #+#    #+#             */
/*   Updated: 2024/03/20 03:27:29 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"
# define PI 3.1415926

int fix_ang(int a)
{
	if (a >= 360)
		return (a - 360);
	if (a < 0)
		return (a + 360);
}

double  fix_rad(double rad)
{
	if (rad >= 2 * PI)
		return (rad - 2 * PI);
	if (rad < 0)
		return (rad + 2 * PI);
}

int	fix_rad_to_ang(double rad)
{
	return ((int)(rad / 2 / PI * 360));
}

double	fix_ang_to_rad(int ang)
{
	return ((double)ang / 360.0 * 2 * PI);
}