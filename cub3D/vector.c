/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 01:05:07 by yugao             #+#    #+#             */
/*   Updated: 2024/03/17 01:10:45 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

t_vec	*vac_rotate(t_vec *old, double angle)
{
	t_vec	*new;

	new = malloc (sizeof (t_vec));
	if (!new)
		return (NULL);
	new->x = cos(angle) - sin(angle);
	new->y = sin(angle) - cos(angle);
	return (new);
}

