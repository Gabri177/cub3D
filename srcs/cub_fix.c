/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_fix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:20:38 by yugao             #+#    #+#             */
/*   Updated: 2024/03/25 19:30:07 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//对角度值进行修复, 确保角度在0 - 360之间
int fix_ang(int a)
{
	if (a >= 360)
		return (a - 360);
	if (a < 0)
		return (a + 360);
	return (a);
}

//对用pi表示的角度进行修复, 确保值在0 - 2PI之间
double  fix_rad(double rad)
{
	if (rad >= 2 * PI)
		return (rad - 2 * PI);
	if (rad < 0)
		return (rad + 2 * PI);
	return (rad);
}

//将角度值转换为用PI表示的方法
int	fix_rad_to_ang(double rad)
{
	return ((int)(rad / 2 / PI * 360));
}

double	fix_ang_to_rad(int ang)
{
	return ((double)ang / 360.0 * 2 * PI);
}
