/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:15:03 by yugao             #+#    #+#             */
/*   Updated: 2024/02/23 19:36:31 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

t_bool	m_init(t_ary *l, t_data info)
{
	int	i;
	int	j;

	i = 0;
	*l = (t_node ***) malloc (sizeof (t_node **) * info.win_x / UNI);
	if (!(*l))
		return (FALSE);
	while (i < info.win_x / UNI)
	{
		(*l)[i] = (t_node **) malloc (sizeof (t_node *) * info.win_y / UNI);
		if (!(*l)[i])
			return (FALSE);
		j = 0;
		while (j < info.win_y / UNI)
		{
			(*l)[i][j] = (t_node *) malloc (sizeof (t_node));
			if (!(*l)[i][j])
				return (FALSE);
			(*l)[i][j]->stp = 0;
			j ++;
		}
		i ++;
	}
	return (TRUE);
}

void	m_print(t_ary l, t_data info, t_bool is_obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < info.win_y / UNI)
	{
		j = 0;
		while (j < info.win_x / UNI)
		{
			if (is_obj)
				ft_printf ("   %c", l[j][i]->obj);
			else
				ft_printf ("\t%d", l[j][i]->stp);
			j ++;
		}
		ft_printf ("\n");
		i ++;
	}
}

t_bool	m_clr(t_ary *m, t_data info)
{
	int	i;
	int	j;

	i = 0;
	if (!m)
		return (FALSE);
	while (i < info.win_x / UNI)
	{
		j = 0;
		while (j < info.win_y / UNI)
		{
			free ((*m)[i][j]);
			j ++;
		}
		i ++;
	}
	i = 0;
	while (i < info.win_x / UNI)
	{
		free ((*m)[i]);
		i ++;
	}
	free (*m);
	return (TRUE);
}

t_bool	m_check(t_ary m, t_data *info)
{
	int	i;

	i = 0;
	while (i < info->win_x / UNI)
	{
		if (m[i][0]->obj != '1' || m[i][info->win_y / UNI - 1]->obj != '1')
			e_exit (ERR_MAP);
		i ++;
	}
	i = 0;
	while (i < info->win_y / UNI)
	{
		if (m[0][i]->obj != '1' || m[info->win_x / UNI - 1][i]->obj != '1')
			e_exit (ERR_MAP);
		i ++;
	}
	if (!m_grep(m, *info, 'E') || !m_grep(m, *info, 'P')
		|| !m_grep(m, *info, '0') || !m_grep(m, *info, 'C'))
		e_exit (ERR_MAP);
	info->ctr_x = m_grep(m, *info, 'P')->x;
	info->ctr_y = m_grep(m, *info, 'P')->y;
	return (TRUE);
}

t_pos	*m_grep(t_ary m, t_data info, char c)
{
	int		i;
	int		j;
	t_pos	*tem;

	i = 0;
	tem = (t_pos *) malloc (sizeof (t_pos));
	if (!tem)
		e_exit (ERR_MEM);
	while (i < info.win_y / UNI)
	{
		j = 0;
		while (j < info.win_x / UNI)
		{
			tem->x = j;
			tem->y = i;
			if (m[j][i]->obj == c)
				return (tem);
			j ++;
		}
		i ++;
	}
	return (NULL);
}

/* int	main(void)
{
	t_ary	l;
	t_data	test;
	int		a;

	test.win_x = 3;
	test.win_y = 8;
	m_init (&l, test);
	m_clr (&l, test);
	//m_print (l, test);
	
	return (0);
} */