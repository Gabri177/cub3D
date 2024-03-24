/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_math1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:58:10 by yugao             #+#    #+#             */
/*   Updated: 2024/03/24 00:27:45 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	math_dist2p(t_pos p1, t_pos p2)
{
	double	dy;
	double	dx;

	dy = fabs (p2.y - p1.y);
	dx = fabs (p2.x - p1.x);
	return (sqrt(dx * dx + dy * dy));
}

double	math_k2p(t_pos p1, t_pos p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double	math_b2p(t_pos p, double k)
{
	return (p.y - k * p.x);
}

t_pos	math_line_offset(t_pos p_esp, t_pos p1, t_pos p2, double b_offset)
{
	double	k;
	double	b;

	k = math_k2p (p1, p2);
	b = math_b2p (p1, k) + b_offset;
	return ((t_pos){p_esp.x, k * p_esp.x + b});
}