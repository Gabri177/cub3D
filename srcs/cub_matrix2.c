/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_matrix2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:40:20 by yugao             #+#    #+#             */
/*   Updated: 2024/04/06 01:24:05 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// 用在条件判断中, 查看x , y 是不是超过数组下标, 从而避免seg问题
// Used in conditional judgment to see if x , y 
//exceeds the array subscripts, thus avoiding the seg problem.
t_bool	matrix_range_check(void *info, int x, int y)
{
	int		lenx;
	int		leny;
	t_mtx	tem;

	tem = ((t_info *)info)->mtx;
	lenx = 0;
	leny = 0;
	while (tem[0][leny])
		leny ++;
	while (tem[lenx])
		lenx ++;
	if (x < lenx && y < leny && x >= 0 && y >= 0)
		return (TRUE);
	else
		return (FALSE);
}