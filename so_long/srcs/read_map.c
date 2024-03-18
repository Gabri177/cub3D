/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:07:16 by yugao             #+#    #+#             */
/*   Updated: 2024/02/23 19:40:05 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	r_fd(char *dir)
{
	int	fd;

	fd = open (dir, O_RDONLY);
	if (fd < 0)
		e_exit(ERR_FIL);
	return (fd);
}

static t_bool	r_str_leg(char *str)
{
	size_t		i;
	static int	num_p;

	i = 0;
	while (i < ft_strlen (str))
	{
		if (str[i] == 'P')
			num_p ++;
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P'
			&& str[i] != 'C' && str[i] != 'E' && str[i] != '\n')
			return (FALSE);
		if (num_p > 1)
			return (FALSE);
		i ++;
	}
	return (TRUE);
}

static size_t	r_len(char *str)
{
	int	i;

	i = 0;
	if (!r_str_leg (str))
		e_exit (ERR_CHA);
	while (str[i])
	{
		if (str[i] == '\n')
			return (ft_strlen (str) - 1);
		i ++;
	}
	return (ft_strlen (str));
}

t_bool	r_size(t_data *info, int fd)
{
	static size_t		w;
	static size_t		h;
	char				*line;

	line = get_next_line (fd);
	if (!line || *line == '\n')
		e_exit (ERR_RED);
	w = r_len (line);
	h ++;
	while (line)
	{
		line = get_next_line (fd);
		if (!line || *line == '\n')
			break ;
		if (r_len (line) != w)
			e_exit (ERR_NOM);
		free (line);
		h ++;
	}
	info->win_x = w * UNI;
	info->win_y = h * UNI;
	close (fd);
	return (TRUE);
}

t_bool	r_to_mrx(t_data *info, int fd, t_ary *m)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < info->win_y / UNI)
	{
		line = get_next_line (fd);
		if (!line)
			e_exit (ERR_RED);
		x = 0;
		while (x < info->win_x / UNI)
		{
			(*m)[x][y]->obj = line[x];
			x ++;
		}
		free (line);
		y ++;
	}
	close (fd);
	m_check (*m, info);
	m_can_out (m, info->ctr_x, info->ctr_y);
	m_check_out (*m, *info);
	return (TRUE);
}
