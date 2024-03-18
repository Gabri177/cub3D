/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 20:24:36 by yugao             #+#    #+#             */
/*   Updated: 2024/02/23 19:36:27 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

static void	e_info_err(char *str)
{
	write (2, str, ft_strlen(str));
}

void	e_exit(int tp)
{
	if (tp == ERR_IMG)
		e_info_err ("Error\n:Load IMG error!\n");
	else if (tp == ERR_FIL)
		e_info_err ("Error\n:Please cheack if exist the file! \n");
	else if (tp == ERR_ARG)
		e_info_err ("Error\n:You have passed an argument invalid!\n");
	else if (tp == ERR_RED)
		e_info_err ("Error\n:Sorry, Read file failed! \n");
	else if (tp == ERR_NOM)
		e_info_err ("Error\n:The map is nos a square!\n");
	else if (tp == ERR_MAP)
		e_info_err ("Error\n:The map is ilegal!\n");
	else if (tp == ERR_MEM)
		e_info_err ("Error\n:Malloc unsuccessfully!\n");
	else if (tp == ERR_NOWAY)
		e_info_err ("Error\n:There is no way out!\n");
	else if (tp == ERR_CHA)
		e_info_err ("Error\n:Ilegal character en map!\n");
	exit (1);
}

void	s_exit(int tp)
{
	if (tp == SCS_WIN)
		printf ("You Win !\n");
	exit (0);
}
