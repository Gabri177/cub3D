/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 03:44:33 by yugao             #+#    #+#             */
/*   Updated: 2024/02/23 19:36:33 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

t_bool	canmov(t_ary m, int x, int y)
{
	if (m[x][y]->obj == '1' || m[x][y]->obj == 'P')
		return (FALSE);
	return (TRUE);
}

void	m_can_out(t_ary *m, int x, int y)
{
	if (canmov (*m, x + 1, y) && (*m)[x + 1][y]->stp == 0)
	{
		(*m)[x + 1][y]->stp = (*m)[x][y]->stp + 1;
		m_can_out (m, x + 1, y);
	}
	if (canmov (*m, x, y + 1) && (*m)[x][y + 1]->stp == 0)
	{
		(*m)[x][y + 1]->stp = (*m)[x][y]->stp + 1;
		m_can_out (m, x, y + 1);
	}
	if (canmov (*m, x - 1, y) && (*m)[x - 1][y]->stp == 0)
	{
		(*m)[x - 1][y]->stp = (*m)[x][y]->stp + 1;
		m_can_out (m, x - 1, y);
	}
	if (canmov (*m, x, y - 1) && (*m)[x][y - 1]->stp == 0)
	{
		(*m)[x][y - 1]->stp = (*m)[x][y]->stp + 1;
		m_can_out (m, x, y - 1);
	}
	return ;
}

void	m_check_out(t_ary l, t_data info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info.win_y / UNI)
	{
		j = 0;
		while (j < info.win_x / UNI)
		{
			if (l[j][i]->obj == 'E' && l[j][i]->stp == 0)
				e_exit (ERR_NOWAY);
			if (l[j][i]->obj == 'C' && l[j][i]->stp == 0)
				e_exit (ERR_NOWAY);
			j ++;
		}
		i ++;
	}
}
