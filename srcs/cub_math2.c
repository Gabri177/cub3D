/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:20:44 by yugao             #+#    #+#             */
/*   Updated: 2024/03/24 00:50:59 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vec	math_projection_vec(t_vec v_ori, double change_ang, int vec_len)
{
	double	new_ang;

	if (vec_len <= 0)
		vec_len = 1;
	new_ang = fix_ang (v_ori.ang + change_ang);
	return ((t_vec){cos (fix_ang_to_rad(new_ang)) * vec_len, -sin (fix_ang_to_rad(new_ang)) * vec_len, new_ang});	
}
