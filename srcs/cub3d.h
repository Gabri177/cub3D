/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:45:47 by yugao             #+#    #+#             */
/*   Updated: 2024/03/20 04:53:45 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define PI 3.1415926

typedef int	t_bool;

typedef struct s_pos
{
	double x;
	double y;
}   		t_pos;

typedef struct s_vec
{
	double  vx;
	double  vy;
	double	ang;
}   		t_vec;

typedef struct s_map2d
{
	int	x;
	int	y;
	int	size_unit;
}  			t_map2d;

typedef struct s_key
{
	t_bool	up;
	t_bool	down;
	t_bool	left;
	t_bool	right;
}  			t_key;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	t_vec	ang;
	t_pos	ctr;
	t_map2d	map;
	t_key	key;
	int		color;
}			t_info;

//======graph.h======
void	graph_thick_line(void *info, t_pos p1, t_pos p2, double thick);
void	graph_square(void *info, t_pos p_center, int len_side);
void	graph_rectangle(void *info, t_pos p_low_left, t_pos p_up_right);
//======fix.h========
int		fix_ang(int a);
double	fix_rad(double rad);
int		fix_rad_to_ang(double rad);
double	fix_ang_to_rad(int ang);
//======vec.h========
double	ang_2vec_2D(t_vec v1, t_vec v2);
void	vec_rotate(t_vec *v_ori, double ang);
void	vec_scale(t_vec *v_ori, double scale_x, double scale_y);
void	vec_trans(t_vec *v_ori, double trans_x, double trans_y);

#endif