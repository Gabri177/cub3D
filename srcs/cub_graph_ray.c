/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javgao <yugao@student.42madrid.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:57 by yugao             #+#    #+#             */
/*   Updated: 2024/04/03 22:36:06 by javgao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	graph_draw_ray(void *info, t_pos endpoint)
{
	graph_thick_line (info, ((t_info *)info)->ctr_pos, endpoint, 1);
}

static t_img_info pick_tex(void *info, t_bool side)
{
    t_info  *tem;

    tem = (t_info *)info;
    if (side == UPSIDE)
        return (tem->tex_up);
    else if (side == DOWNSIDE)
        return (tem->tex_down);
    else if (side == LEFTSIDE)
        return (tem->tex_left);
    else
        return (tem->tex_right);
}

void graph_ray_to_wall(void *info_ptr, int fov)
{
    t_info *info = (t_info *)info_ptr;
    int screenWidth = 530; // 屏幕宽度
    double pixelPerDegree = screenWidth / (double)fov; // 每度对应的像素数
    double angleStep = fov / (double)screenWidth; // 每个像素对应的角度步长

    for (int x = 0; x < screenWidth; x++)
    {
        double rayAngle = (x - screenWidth / 2.0) * angleStep; // 计算射线相对于视野中心的角度偏移
        t_posx hit = biu_hit_pos(info, rayAngle); // 获取射线击中的位置和方向
        
        // 根据撞击方向选择对应的纹理
        t_img_info tex;
        tex = pick_tex (info_ptr, hit.side);

        // 计算玩家到墙面的距离和墙面在屏幕上的高度
        double dis = math_dist2p(info->ctr_pos, trans_posx_to_pos(hit)) * cos(rayAngle * PI / 180);
        int lineH = (int)(UNIDAD / dis * screenWidth / (2.0 * tan(fov / 2.0 * PI / 180)));
        int lineOff = (screenWidth / 2) - (lineH / 2);

        // 对每个垂直线段的每个像素应用纹理
        for (int y = 0; y < lineH; y++)
        {
            int texY = (int)(((double)y / lineH) * UNIDAD); 
            int textureX;
            if (hit.side == LEFTSIDE || hit.side == RIGHTSIDE)
            {
                textureX = (int)(hit.y) % UNIDAD;
            } else {
                textureX = (int)(hit.x) % UNIDAD;
            }
            uint32_t color = *(uint32_t *)(tex.addr + (texY * tex.len_line) + textureX * (tex.bits_per_pixel / 8));
            img_put_pixel(info, x + 530, y + lineOff, color);
        }
    }
}


