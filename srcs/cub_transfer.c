/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_transfer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:16:05 by yugao             #+#    #+#             */
/*   Updated: 2024/03/26 02:35:13 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_pos	trans_posx_to_pos(t_posx posx)
{
	return ((t_pos){posx.x, posx.y});
}

t_pos	trans_2num_to_pos(double n1, double n2)
{
	return ((t_pos){n1, n2});
}

t_posx	trans_pos_to_posx(t_pos pos, t_bool side)
{
	return ((t_posx){pos.x, pos.y, side});
}
