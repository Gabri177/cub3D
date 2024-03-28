/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:57 by yugao             #+#    #+#             */
/*   Updated: 2024/03/28 01:22:31 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	graph_draw_ray(void *info, t_pos endpoint)
{
	graph_thick_line (info, ((t_info *)info)->ctr_pos, endpoint, 1);
}

// void	graph_ray_to_wall(void *info, int range_ang)
// {
// 	int		i;
// 	double	dis;
// 	int		ca;
// 	int		lineh;
// 	int		lineoff;
// 	t_posx	hit;
	

// 	i = - range_ang / 2;
// 	while (i <= range_ang / 2)
// 	{
// 		hit = biu_hit_pos (info, i);
// 		printf ("(%d, %d) \n", (int)(hit.x / UNIDAD), (int)(hit.y / UNIDAD));
// 		// color set
// 		if (hit.side == UPSIDE)
// 			img_set_color (info, 0xFFB6C1);
// 		else if (hit.side == DOWNSIDE)
// 			img_set_color (info, 0x800080);
// 		else if (hit.side == LEFTSIDE)
// 			img_set_color (info, 0x4169E1);
// 		else
// 			img_set_color (info, 0x3CB371);
// 		// color set
// 		graph_draw_ray (info, trans_posx_to_pos(hit));
// 		ca = fix_ang (i);
// 		dis = math_dist2p (((t_info *)info)->ctr_pos, trans_posx_to_pos(hit)) * cos (fix_ang_to_rad(ca));
// 		printf ("dis: %f\n",dis);
// 		lineh = UNIDAD * 500 / dis;
// 		if (lineh > 500)
// 			lineh = 500;
// 		lineoff = 250 - (lineh >> 1);
// 		//printf ("dis:%f hit:(%f, %f), lineoff %d\n", dis, hit.x, hit.y, lineoff);

// 		// color set
// 		if (hit.side == UPSIDE)
// 			img_set_color (info, 0xFFB6C1);
// 		else if (hit.side == DOWNSIDE)
// 			img_set_color (info, 0x800080);
// 		else if (hit.side == LEFTSIDE)
// 			img_set_color (info, 0x4169E1);
// 		else
// 			img_set_color (info, 0x3CB371);
// 		// color set

		
// 		graph_thick_line(info, trans_2num_to_pos(530 + (i + range_ang / 2) * 8, lineoff), trans_2num_to_pos(530 + (i + range_ang / 2) * 8, lineoff + lineh), 1);
// 		i += 1;
// 	}
// }

// void graph_ray_to_wall(void *info_ptr, int fov) {
//     t_info *info = (t_info *)info_ptr;
//     int screenWidth = 530; // 假设屏幕宽度为800像素
//     double pixelPerDegree = screenWidth / (double)fov;
//     int range_ang = fov; // FOV
//     int i, screenX;
//     double dis, lineH, lineOff;
//     t_posx hit;
// 	int	textureX;
    
//     for (i = -range_ang / 2; i <= range_ang / 2; i++) {
//         hit = biu_hit_pos(info, i); // 获取射线击中的位置和方向
//         t_img_info *tex;

//         // 根据撞击方向选择对应的纹理
//         if (hit.side == UPSIDE) tex = &info->tex_up;
//         else if (hit.side == DOWNSIDE) tex = &info->tex_down;
//         else if (hit.side == LEFTSIDE) tex = &info->tex_left;
//         else tex = &info->tex_right; // RIGHTSIDE

// 		if (hit.side == LEFTSIDE || hit.side == RIGHTSIDE) {
//         // 对于左面和右面的墙体，使用hit.y计算纹理X坐标
//         textureX = (int)(hit.y) % UNIDAD;
//    		} else {
//         // 对于上面和下面的墙体，使用hit.x计算纹理X坐标
//         textureX = (int)(hit.x) % UNIDAD;
//     	}
// 		graph_draw_ray (info, trans_posx_to_pos(hit));
//         // 计算射线在屏幕上的X坐标
//         screenX = (int)((i + range_ang / 2.0) * pixelPerDegree);

//         // 计算距离和墙壁高度
//         dis = math_dist2p(info->ctr_pos, trans_posx_to_pos(hit)) * cos(fix_ang (i) * PI / 180);
//         lineH = (UNIDAD / dis) * ((screenWidth / 2) / tan(fov / 2.0 * PI / 180));
//         lineOff = (screenWidth / 2) - (lineH / 2);

//         //对每个垂直线段的每个像素应用纹理
//         // for (int y = 0; y < lineH; y++) {
//         //     int texY = (int)(((double)y / lineH) * 64);
//         //     for(int j= 0; j< 9; j++)
// 		// 	{
// 		// 		uint32_t color = *(uint32_t *)(tex->addr + (texY * tex->len_line) + (textureX) * (tex->bits_per_pixel / 8));
//         //     	img_put_pixel(info, screenX + 530 + j, lineOff + y, color);
// 		// 	}
//         // }
// 		for (int y = 0; y < lineH; y++)
// 		{
// 			int texY = (int)(((double)y / lineH) * 64); // 使用纹理的实际高度
// 			uint32_t color = *(uint32_t *)(tex->addr + (texY * tex->len_line) + textureX * (tex->bits_per_pixel / 8));
// 			img_put_pixel(info, 530 + screenX, lineOff + y, color); // 直接使用screenX而不是扩展到多个像素
// 		}

//     }
// }

void graph_ray_to_wall(void *info_ptr, int fov) {
    t_info *info = (t_info *)info_ptr;
    int screenWidth = 530; // 屏幕宽度
    double pixelPerDegree = screenWidth / (double)fov; // 每度对应的像素数
    int range_ang = fov; // 视场角（FOV）
    double angleStep = fov / (double)screenWidth; // 每个像素对应的角度步长
    int textureSize = 64; // 纹理的大小

    for (int x = 0; x < screenWidth; x++) {
        double rayAngle = (x - screenWidth / 2.0) * angleStep; // 计算射线相对于视野中心的角度偏移
        t_posx hit = biu_hit_pos(info, rayAngle); // 获取射线击中的位置和方向
        
        // 根据撞击方向选择对应的纹理
        t_img_info *tex;
        if (hit.side == UPSIDE) tex = &info->tex_up;
        else if (hit.side == DOWNSIDE) tex = &info->tex_down;
        else if (hit.side == LEFTSIDE) tex = &info->tex_left;
        else tex = &info->tex_right;

        // 计算玩家到墙面的距离和墙面在屏幕上的高度
        double dis = math_dist2p(info->ctr_pos, trans_posx_to_pos(hit)) * cos(rayAngle * PI / 180);
        int lineH = (int)(textureSize / dis * screenWidth / (2.0 * tan(fov / 2.0 * PI / 180)));
        int lineOff = (screenWidth / 2) - (lineH / 2);

        // 对每个垂直线段的每个像素应用纹理
        for (int y = 0; y < lineH; y++) {
             int texY = (int)(((double)y / lineH) * 64); 
            int textureX;
            if (hit.side == LEFTSIDE || hit.side == RIGHTSIDE) {
                textureX = (int)(hit.y) % textureSize;
            } else {
                textureX = (int)(hit.x) % textureSize;
            }
            uint32_t color = *(uint32_t *)(tex->addr + (texY * tex->len_line) + textureX * (tex->bits_per_pixel / 8));
            img_put_pixel(info, x + 530, y + lineOff, color);
        }
    }
}


