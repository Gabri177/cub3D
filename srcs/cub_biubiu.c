/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_biubiu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:35:36 by yugao             #+#    #+#             */
/*   Updated: 2024/03/26 03:18:18 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_pos	apoyo_biu_hit_pos_veri(t_pos start_pos, int ang)
{
	double	n_tan;
	double	s_tan;

	ang = fix_ang (ang);
	n_tan = tan (fix_ang_to_rad (ang));
	s_tan = 1.0 / n_tan;
	if (cos(fix_ang_to_rad (ang)) > 0.001)
		return((t_pos){(int)(start_pos.x) / UNIDAD * UNIDAD + UNIDAD, (((int)(start_pos.x) / UNIDAD * UNIDAD + UNIDAD) - start_pos.x) * n_tan + start_pos.y});
	else if (cos(fix_ang_to_rad (ang)) < -0.001)
		return((t_pos){(int)(start_pos.x) / UNIDAD * UNIDAD - 0.001, (((int)(start_pos.x) / UNIDAD * UNIDAD - 0.0001) - start_pos.x) * n_tan + start_pos.y});
	else
		return ((t_pos){start_pos.x + cos (fix_ang_to_rad(ang)) * 500, start_pos.y + sin(fix_ang_to_rad(ang)) * 500});
}

static t_pos	apoyo_biu_hit_pos_hori(t_pos start_pos, int ang)
{
	double	n_tan;
	double	s_tan;

	ang = fix_ang (ang);
	n_tan = tan (fix_ang_to_rad (ang));
	s_tan = 1.0 / n_tan;
	if (sin(fix_ang_to_rad (ang)) > 0.001)
		return((t_pos){((((int)(start_pos.y) / UNIDAD * UNIDAD + UNIDAD)) - start_pos.y) * s_tan + start_pos.x, (((int)(start_pos.y) / UNIDAD * UNIDAD + UNIDAD))});
	else if (sin(fix_ang_to_rad (ang)) < -0.001)
		return((t_pos){((((int)(start_pos.y) / UNIDAD * UNIDAD - 0.0001)) - start_pos.y) * s_tan + start_pos.x, (((int)(start_pos.y) / UNIDAD * UNIDAD - 0.0001))});
	else
		return ((t_pos){start_pos.x + cos (fix_ang_to_rad(ang)) * 500, start_pos.y + sin(fix_ang_to_rad(ang)) * 500});
}

//这里有必要对循环的深度做限制, 一般是水平探查地图长度减一的深度 防止死循环
static t_pos	biu_hit_pos_hori(void *info, int setoff_ang)
{
	int		ang;
	t_pos	p_mtx;
	t_pos	fin;
	int		i;

	ang = fix_ang(((t_info *)info)->ctr_ang.ang + setoff_ang);
	fin = apoyo_biu_hit_pos_hori (((t_info *)info)->ctr_pos, ang);
	p_mtx = math_coordinate (fin);
	i = 0;
	if (sin(fix_ang_to_rad (ang)) > 0.001 || sin(fix_ang_to_rad (ang)) < -0.001)
	{
		
		while (i < 32 && matrix_range_check (info, (int)(p_mtx.x), (int)(p_mtx.y)) && ((t_info *)info)->mtx[(int)(p_mtx.x)][(int)(p_mtx.y)]->obj != '1')
		{
			fin = apoyo_biu_hit_pos_hori (fin, ang);
			p_mtx = math_coordinate (fin);
			i ++;
		}
		return (fin);
	}
	else
		return (apoyo_biu_hit_pos_hori (((t_info *)info)->ctr_pos, ang));
	
}

//这里有必要对循环的深度做限制, 一般是纵向探查地图高度减一的深度 防止死循环
static t_pos	biu_hit_pos_veri(void *info, int setoff_ang)
{
	int		ang;
	t_pos	p_mtx;
	t_pos	fin;
	int		i;

	ang = fix_ang(((t_info *)info)->ctr_ang.ang + setoff_ang);
	fin = apoyo_biu_hit_pos_veri (((t_info *)info)->ctr_pos, ang);
	p_mtx = math_coordinate (fin);
	i = 0;
	//printf ("ori :(%d,%d)\n",(int)(p_mtx.x), (int)(p_mtx.y));
	if (cos(fix_ang_to_rad (ang)) > 0.001 || cos(fix_ang_to_rad (ang)) < -0.001)
	{
		
		while (i < 13 && matrix_range_check (info, (int)(p_mtx.x), (int)(p_mtx.y)) && ((t_info *)info)->mtx[(int)(p_mtx.x)][(int)(p_mtx.y)]->obj != '1')
		{
			fin = apoyo_biu_hit_pos_veri (fin, ang);
			p_mtx = math_coordinate (fin);
			i ++;
		}
		return (fin);
	}
	else
		return (apoyo_biu_hit_pos_veri (((t_info *)info)->ctr_pos, ang));
	
}

t_posx	biu_hit_pos(void *info, int setoff_ang)
{
	t_pos	hori;
	t_pos	veri;
	t_pos	ctr;
	double	dis_hori;
	double	dis_veri;

	hori = biu_hit_pos_hori (info, setoff_ang);
	veri = biu_hit_pos_veri (info, setoff_ang);
	ctr = ((t_info *)info)->ctr_pos;
	dis_hori = math_dist2p(ctr, hori);
	dis_veri = math_dist2p(ctr, veri);
	if (dis_hori < dis_veri)
	{
		if (hori.y < ctr.y)
			return (trans_pos_to_posx (hori, DOWNSIDE));
		else
			return (trans_pos_to_posx (hori, UPSIDE));
	}
	else
	{
		if (veri.x < ctr.x)
			return (trans_pos_to_posx (veri, LEFTSIDE));
		else
			return (trans_pos_to_posx (veri, RIGHTSIDE));
	}
}

//void	biu_2d(void *info);

// int	main(void)
// {
// 	printf ("%f", tan (fix_rad( PI + PI / 3)));
// 	return 0;
// }