/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_graph_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:29:57 by yugao             #+#    #+#             */
/*   Updated: 2024/04/06 02:03:14 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//画一条射线, 需要提供结束点的坐标, 因为起始点的坐标就是人物坐标ctr_pos
// draw a ray, need to provide the coordinates of the end point,
// because the coordinates of the start 
//point is the character coordinates ctr_pos
void	graph_draw_ray(void *info, t_pos endpoint)
{
	graph_thick_line (info, ((t_info *)info)->ctr_pos, endpoint, 1);
}

//根据撞击点的方向判断应该应用什么类型的材质
//Determine what type of material should be 
//applied based on the direction of the point of impact.
static t_img_info	pick_tex(void *info, t_bool side)
{
	t_info	*tem;

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

//这里FOV是视角的大小, 通过这个函数我们可以生成3d场景
// Here FOV is the size of the viewpoint, 
//with this function we can generate a 3d scene.
void	graph_ray_to_wall(void *info_ptr)
{
	t_info		*info;
	int			y;
	int			x;
	t_img_info	tex;

	info = (t_info *)info_ptr;
	x = 0;
	while (x < SCREENWITH)
	{
		double rayAngle = (x - SCREENWITH / 2.0) * (FOV / (double)SCREENWITH);
		t_posx hit = biu_hit_pos(info, rayAngle);
		tex = pick_tex (info_ptr, hit.side);
		double dis = math_dist2p(info->ctr_pos, trans_posx_to_pos(hit)) * cos(fix_ang_to_rad(fix_ang(rayAngle)));
		int lineH = (int)(UNI / dis * SCREENWITH / (2.0 * tan(fix_ang_to_rad(fix_ang(FOV / 2)))));
		int lineOff = (SCREENWITH / 2) - (lineH / 2);

		y = 0;
		while (y < lineH)
		{
			int texY = (int)(((double)y / lineH) * tex.tex_y); 
			int textureX;
			if (hit.side == LEFTSIDE || hit.side == RIGHTSIDE)
				textureX = (int)((int)(hit.y - (int)(hit.y / UNI) * UNI) % tex.tex_y);
			else
				textureX = (int)((int)(hit.x - (int)(hit.x / UNI) * UNI) % tex.tex_x);
			img_put_pixel(info, x + 530, y + lineOff, *(uint32_t *)(tex.addr + (texY * tex.len_line) + textureX * (tex.bits_per_pixel / 8)));
			y ++;
		}
		x ++;
	}
}

// void graph_ray_to_wall(void *info_ptr, int FOV)
// {
// 	t_info *info = (t_info *)info_ptr;
// 	int SCREENWITH = 530;
// 	int screenHeight = 530;
// 	double angleStep = FOV / (double)SCREENWITH; // 每个像素对应的角度步长
// 	double halfFOV = FOV / 2.0;

// 	for (int x = 0; x < SCREENWITH; x++)
// 	{
// 		// 计算射线相对于视野中心的角度偏移，并修正角度
// 		double rayAngle = (x - SCREENWITH / 2.0) * angleStep;
		
// 		// 获取射线击中的位置和方向
// 		t_posx hit = biu_hit_pos(info, rayAngle);

// 		// 计算玩家到墙面的距离，并进行鱼眼效应的校正
// 		double dis = math_dist2p(info->ctr_pos, trans_posx_to_pos(hit)) *  cos(fix_ang_to_rad(fix_ang(rayAngle)));

// 		// 根据距离计算墙面的高度
// 		int wallHeight = (int)(UNI / dis * SCREENWITH / (2.0 * tan(fix_ang_to_rad(FOV / 2))));
		
// 		// 计算墙面顶部和底部的屏幕位置
// 		int drawStart = (screenHeight - wallHeight) / 2;
// 		drawStart = drawStart < 0 ? 0 : drawStart; // 防止超出屏幕范围
// 		int drawEnd = drawStart + wallHeight;
// 		drawEnd = drawEnd >= screenHeight ? screenHeight - 1 : drawEnd;

// 		int color;
// 		switch (hit.side) {
// 			case LEFTSIDE:
// 				color = 0xFF0000; // 假设左边墙面为红色
// 				break;
// 			case RIGHTSIDE:
// 				color = 0x00FFFF; // 假设右边墙面为绿色
// 				break;
// 			case UPSIDE:
// 				color = 0x0000FF; // 假设上边墙面为蓝色
// 				break;
// 			case DOWNSIDE:
// 				color = 0xFFFF00; // 假设下边墙面为黄色
// 				break;
// 			default:
// 				color = 0xFFFFFF; // 默认为白色
// 		}
		
// 		img_set_color(info, color); // 设置颜色
// 		//绘制墙面
// 		for (int y = drawStart; y < drawEnd; y++)
// 		{
// 			// 这里简化处理，假设墙面颜色固定。在实际应用中，你可能会根据材质和光照等因素选择颜色。
// 			img_put_pixel(info, x, y, color); // 假定墙面为白色
// 		}
// 		switch (hit.side) {
// 			case RIGHTSIDE:
// 				color = 0xFF0000; // 假设左边墙面为红色
// 				break;
// 			case LEFTSIDE:
// 				color = 0x00FF00; // 假设右边墙面为绿色
// 				break;
// 			case DOWNSIDE:
// 				color = 0x0000FF; // 假设上边墙面为蓝色
// 				break;
// 			case UPSIDE:
// 				color = 0xFFFF00; // 假设下边墙面为黄色
// 				break;
// 			default:
// 				color = 0xFFFFFF; // 默认为白色
// 		}
// 		img_set_color (info, color);
// 		switch (hit.side) {
// 			case RIGHTSIDE:
// 				printf ("右边->: hitx: %f, hity %lf,  ctrx: %lf, ctry: %lf \n", hit.x, hit.y, info->ctr_pos.x, info->ctr_pos.y);
// 				break;
// 			case LEFTSIDE:
// 				printf ("左边<-: hitx: %f, hity %lf,  ctrx: %lf, ctry: %lf \n", hit.x, hit.y, info->ctr_pos.x, info->ctr_pos.y);
// 				break;
// 			case DOWNSIDE:
// 				printf ("下边v: hitx: %f, hity %lf,  ctrx: %lf, ctry: %lf \n", hit.x, hit.y, info->ctr_pos.x, info->ctr_pos.y);
// 				break;
// 			case UPSIDE:
// 				printf ("上边^: hitx: %f, hity %lf,  ctrx: %lf, ctry: %lf \n", hit.x, hit.y, info->ctr_pos.x, info->ctr_pos.y);
// 				break;
// 			default:
// 				color = 0xFFFFFF; // 默认为白色
// 		}
// 		graph_thick_line (info_ptr, info->ctr_pos, trans_posx_to_pos(hit), 1);
// 	}
// }