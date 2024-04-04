/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_transfer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:16:05 by yugao             #+#    #+#             */
/*   Updated: 2024/04/04 01:46:57 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//将t_posx类型的变量转换为t_pos类型
// Convert a variable of type t_posx to t_pos
t_pos	trans_posx_to_pos(t_posx posx)
{
	return ((t_pos){posx.x, posx.y});
}

//将两个数字转换为t_pos类型变量
// Convert two numbers into a variable of type t_pos
t_pos	trans_2num_to_pos(double n1, double n2)
{
	return ((t_pos){n1, n2});
}

//将t_pos类型的变量转换为t_posx类型
// Convert a variable of type t_pos to t_posx
t_posx	trans_pos_to_posx(t_pos pos, t_bool side)
{
	return ((t_posx){pos.x, pos.y, side});
}
