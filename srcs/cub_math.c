/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:58:10 by yugao             #+#    #+#             */
/*   Updated: 2024/03/23 23:05:32 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	math_dist2p(t_pos p1, t_pos p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
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