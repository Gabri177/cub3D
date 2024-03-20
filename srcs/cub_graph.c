/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:51:23 by yugao             #+#    #+#             */
/*   Updated: 2024/03/20 03:18:06 by yugao            ###   ########.fr       */
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

void	graph_line(t_point p1, t_point p2, void *info)
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

// int main() {
// 	t_info info;
	
// 	info.mlx = mlx_init();
// 	info.win = mlx_new_window(info.mlx, 800, 600, "Line Drawing");

// 	graph_line((t_point){10, 100}, (t_point){5, 600}, &info);

// 	mlx_loop(info.mlx);
// }