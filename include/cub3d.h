/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:45:47 by yugao             #+#    #+#             */
/*   Updated: 2024/03/24 03:49:02 by yugao            ###   ########.fr       */
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

# define UNIDAD 64
# define TRUE 1
# define FALSE 0
# define PI 3.1415926

typedef int	t_bool;

typedef struct s_img_info
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		len_line;
	int		endian;
}			t_img_info;

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

typedef struct s_map
{
	int	x;
	int	y;
}  			t_map;

typedef struct s_key
{
	t_bool	up;
	t_bool	down;
	t_bool	left;
	t_bool	right;
}  			t_key;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_vec		ctr_ang;
	t_pos		ctr_pos;
	t_map		map_info;
	t_img_info	img_info;
	t_key		key;
	int			color;
}			t_info;

//======cub_graph.c======
void	graph_thick_line(void *info, t_pos p1, t_pos p2, double thick);
void	graph_square(void *info, t_pos p_center, int len_side);
void	graph_rectangle(void *info, t_pos p_low_left, t_pos p_up_right);
//======cub_fix.c========
int		fix_ang(int a);
double	fix_rad(double rad);
int		fix_rad_to_ang(double rad);
double	fix_ang_to_rad(int ang);
//======cub_vec.c========
double	ang_2vec_2D(t_vec v1, t_vec v2);
void	vec_rotate(t_vec *v_ori, double ang);
void	vec_scale(t_vec *v_ori, double scale_x, double scale_y);
t_pos	vec_trans(t_pos p_ori, t_vec v_direction);
//======cub_math.c========
double	math_dist2p(t_pos p1, t_pos p2);
double	math_k2p(t_pos p1, t_pos p2);
double	math_b2p(t_pos p, double k);
t_pos	math_line_offset(t_pos p_esp, t_pos p1, t_pos p2, double b_offset);
t_vec	math_projection_vec(t_vec v_ori, double change_ang, int vec_len);
t_pos	math_coordinate(t_pos pos);
//======cub_img.c=========
void	img_new(void *info);
void	img_put_pixel(void *info, int x, int y, int color);
void	img_start_draw(void *info);
void	img_end_draw(void *info);
void	img_set_color(void *info, int new_color);
//======cub_key.c=========
void    key_move(void *info);
int		key_press(int keycode, void *info);
int		key_release(int keycode, void *info);
//======cub_init.c=========
void	init_info(t_info *info, t_pos ori_pos, t_vec ori_ang, t_map map);
//======cub_2d_bk.c=========
void	bk_map(void *info);
#endif