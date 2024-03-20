/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:51:23 by yugao             #+#    #+#             */
/*   Updated: 2024/03/20 04:11:15 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

typedef int	t_bool;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	double	v_ang;
	double	v_ang_x;
	double	v_ang_y;
	int		p_x;
	int		p_y;
	int		map2d_x;
	int		map2d_y;
	int		map2d_size_unit;
	int		color;
	t_bool	up;
	t_bool	down;
	t_bool	left;
	t_bool	right;
}			t_info;


typedef struct s_point
{
	double x;
	double y;
}   		t_point;

static void	graph_line(void *info, t_point p1, t_point p2)
{
	double	dx;
	double	dy;
	double	e;
	int		i;

	i = -1;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabs(dx) > fabs(dy))
		e = dx;
	else
		e = dy;
	dx = dx / e;
	dy = dy / e;
	while (++ i < e)
	{
		mlx_pixel_put(((t_info *)(info))->mlx, ((t_info *)(info))->win, (int)(p1.x + 0.5), (int)(p1.y + 0.5), 0x2E8B57);
		p1.x += dx;
		p1.y += dy;
	}
}

void	graph_thick_line(void *info, t_point p1, t_point p2, double thick)
{
	double	mid;
	int		i;

	if (thick == 0)
		thick = 1;
	mid = (thick / 2);
	i = 0;
	while (i < 2 * mid)
	{
		graph_line (info,(t_point){p1.x - mid + i, p1.y - mid}, (t_point){p2.x - mid + i, p2.y - mid});
		i ++;
	}
}

void	graph_square(void *info, t_point p_center, int len_side)
{
	graph_thick_line (info, (t_point){p_center.x, p_center.y - (int)(len_side / 2 + 0.5)}, (t_point){p_center.x, p_center.y + (int)(len_side / 2 + 0.5)}, len_side);
}

void	graph_rectangle(void *info, t_point p_low_left, t_point p_up_right)
{
	int	i;

	i = p_low_left.x;
	while (i < p_up_right.x)
	{
		graph_thick_line (info, (t_point){p_low_left.x + i, p_low_left.y}, (t_point){p_low_left.x + i, p_up_right.y}, 1);
		i ++;
	}
}
int main() {
	t_info info;
	
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, 800, 600, "Line Drawing");

	graph_thick_line(&info, (t_point){250, 100}, (t_point){400, 600}, 10);
	graph_line(&info, (t_point){0, 0}, (t_point){500, 600});
	//graph_square(&info, (t_point){50, 100}, 50);
	graph_rectangle(&info, (t_point){50, 50}, (t_point){300, 300});
	mlx_loop(info.mlx);
}