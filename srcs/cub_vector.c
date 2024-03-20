/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:32:20 by yugao             #+#    #+#             */
/*   Updated: 2024/03/20 04:22:53 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"
#include <math.h>

typedef struct s_vec
{
    double  vx;
    double  vy;
}   t_vec;

//求两个向量的夹角
double  ang_2vec_2D(t_vec v1, t_vec v2)
{
    double  doc_multi;
    double  len_multi;

    doc_multi = v1.vx * v2.vx + v1.vy * v2.vy;
    len_multi = sqrt (v1.vx * v1.vx + v1.vy * v1.vy) * sqrt (v2.vx * v2.vx + v2.vy * v2.vy);
    
    return (acos(doc_multi / len_multi));
}

//将向量坐标进行旋转变换
void   vec_rotate(t_vec *v_ori, double ang)
{
    double  vx_tem;

    vx_tem = v_ori->vx;
    v_ori->vx = cos (ang) * v_ori->vx - sin (ang) * v_ori->vy;
    v_ori->vy = sin (ang) * vx_tem + cos (ang) * v_ori->vy;
}

//将向量坐标进行缩放
void   vec_scale(t_vec *v_ori, double scale_x, double scale_y)
{
    v_ori->vx = v_ori->vx * scale_x;
    v_ori->vy = v_ori->vy * scale_y;
}

//将向量坐标进行平移
void   vec_trans(t_vec *v_ori, double trans_x, double trans_y)
{
    v_ori->vx = v_ori->vx + trans_x;
    v_ori->vy = v_ori->vy + trans_y;
}