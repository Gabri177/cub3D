/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yugao <yugao@student.42madrid.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:42:17 by yugao             #+#    #+#             */
/*   Updated: 2024/03/17 03:57:29 by yugao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	info_init(t_data *info)
{
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, info->win_x,
			info->win_y, "MinilibX Window");
	info->ctr_x = 0;
	info->ctr_y = 0;
	info->img_x = 50;
	info->img_y = 50;
	info->img_bk = mlx_xpm_file_to_image (info->mlx,
			IMAG_BK, &info->img_x, &info->img_y);
	info->img_ctr = mlx_xpm_file_to_image (info->mlx,
			IMAG_CTR, &info->img_x, &info->img_y);
	info->img_wal = mlx_xpm_file_to_image (info->mlx,
			IMAG_WAL, &info->img_x, &info->img_y);
	info->img_exit = mlx_xpm_file_to_image (info->mlx,
			IMAG_EXIT, &info->img_x, &info->img_y);
	info->img_coin = mlx_xpm_file_to_image (info->mlx,
			IMAG_COIN, &info->img_x, &info->img_y);
	if (!info->img_bk || !info->img_ctr || !info->img_wal
		|| !info->img_exit || !info->img_coin)
		e_exit (ERR_IMG);
	info->n_mov = -1;
}

// int	key_hook(int key, void *param)
// {
// 	t_data	*info;

// 	info = (t_data *)param;
// 	if (key == 13 || key == 126)
// 		dw_mov(info, info->ctr_x, info->ctr_y - 1, &info->mrx);
// 	if (key == 1 || key == 125)
// 		dw_mov(info, info->ctr_x, info->ctr_y + 1, &info->mrx);
// 	if (key == 0 || key == 123)
// 		dw_mov(info, info->ctr_x - 1, info->ctr_y, &info->mrx);
// 	if (key == 2 || key == 124)
// 		dw_mov(info, info->ctr_x + 1, info->ctr_y, &info->mrx);
// 	if (key == 53)
// 		s_exit (SCS_EXE);
// 	return (0);
// }

int	cls_win(void *param)
{
	(void)param;
	s_exit (SCS_EXE);
	return (0);
}

static void	invalid_line_check(int fd)
{
	char	*line;

	line = get_next_line (fd);
	if (!line)
		e_exit (ERR_RED);
	while (*line == '\n')
		line = get_next_line (fd);
	while (line && *line != '\n')
		line = get_next_line (fd);
	while (line)
	{
		if (*line != '\n')
			e_exit (ERR_MAP);
		line = get_next_line (fd);
	}
	close (fd);
}

// int	main(int arc, char **argv)
// {
// 	t_data	info;

// 	if (arc != 2)
// 		e_exit (ERR_ARG);
// 	if (!ft_strnstr (argv[1], ".ber", ft_strlen (argv[1])))
// 		e_exit (ERR_ARG);
// 	invalid_line_check (r_fd (argv[1]));
// 	r_size (&info, r_fd (argv[1]));
// 	info_init (&info);
// 	m_init (&info.mrx, info);
// 	r_to_mrx (&info, r_fd (argv[1]), &info.mrx);
// 	dw_mov(&info, info.ctr_x, info.ctr_y, &info.mrx);
// 	mlx_key_hook (info.win, key_hook, (void *)&info);
// 	mlx_hook (info.win, 17, 0, cls_win, NULL);
// 	mlx_loop (info.mlx);
// 	return (0);
// }
#include <X11/X.h>
#include <X11/keysym.h>
# define INSTANT 1
# define SIDE_LEN 50
# define P_SIZE 10

int px = 100, py = 100;
int key_states[256];

typedef struct newinfo
{
    void *mlx;
    void *win;
    void *img;  // 图像指针
    char *addr; // 图像数据地址
    int bits_per_pixel;
    int line_length;
    int endian;
}   t_newinfo;



void	dw_cube(int x, int y, void *mlx, void *win)
{
	int	starty;
	int	startx = x * SIDE_LEN + INSTANT;

	while (startx < x * SIDE_LEN + SIDE_LEN)
	{
		starty = y * SIDE_LEN + INSTANT;
		while (starty < y * SIDE_LEN + SIDE_LEN)
		{
			mlx_pixel_put(mlx, win, startx, starty, 0x3CB371);
			starty ++;
		}
		startx ++;
	}
}

void	dw_bankg(int win_x, int win_y, void *mlx, void *win)
{
	int i, j;

	i = 0;
	while (i < win_x)
	{
		j = 0;
		while (j < win_y)
		{
			mlx_pixel_put (mlx, win, i, j, 0xC0C0C0);
			j ++;
		}
		i ++;
	}
}

// void	dw_player (int px, int py, void *mlx, void *win)
// {
// 	int	starty;
// 	int	startx = px * SIDE_LEN + INSTANT;

// 	dw_bankg (1024, 512, mlx, win);
// 	while (startx < px * SIDE_LEN + P_SIZE)
// 	{
// 		starty = py * SIDE_LEN + INSTANT;
// 		while (starty < py * SIDE_LEN + P_SIZE)
// 		{
// 			mlx_pixel_put(mlx, win, startx, starty, 0xFFD700);
// 			starty ++;
// 		}
// 		startx ++;
// 	}
// }

void	dw_player (int px, int py, void *mlx, void *win)
{
	int	starty;
	int	startx = px;

	dw_bankg (1024, 512, mlx, win);
	while (startx < px + P_SIZE)
	{
		starty = py;
		while (starty < py + P_SIZE)
		{
			mlx_pixel_put(mlx, win, startx, starty, 0xFFD700);
			starty ++;
		}
		startx ++;
	}
}

int	key_hook(int key, void *param)
{
	t_newinfo	*info;

	info = (t_newinfo *)param;
	if (key == 13 || key == 126)
	{
		dw_player (px , py - 5, info->mlx, info->win);
		py --;
	}
	if (key == 1 || key == 125)
	{
		dw_player (px , py + 5, info->mlx, info->win);
		py += 5;
	}
	if (key == 0 || key == 123)
	{
		dw_player (px - 5 , py, info->mlx, info->win);
		px -= 5;
	}
	if (key == 2 || key == 124)
	{
		dw_player (px + 5 , py, info->mlx, info->win);
		px += 5;
	}
	if (key == 53)
		s_exit (SCS_EXE);
	return (0);
}

int repeat_actions(void *param)
{
	t_newinfo	*info;

	info = (t_newinfo *)param;
    // 根据key_states数组的值执行动作，例如移动玩家
    if (key_states[13] || key_states[126]) { /* 向上移动玩家 */ }
    {
		dw_player (px , py - 5, info->mlx, info->win);
		py --;
	}
	if (key_states[1] || key_states[125])
	{
		dw_player (px , py + 5, info->mlx, info->win);
		py += 5;
	}
	if (key_states[0] || key_states[123])
	{
		dw_player (px - 5 , py, info->mlx, info->win);
		px -= 5;
	}
	if (key_states[2] || key_states[124])
	{
		dw_player (px + 5 , py, info->mlx, info->win);
		px += 5;
	}
	if (key_states[53])
		s_exit (SCS_EXE);
	return 0;
}

int key_press(int keycode, t_newinfo *info)
{
    key_states[keycode] = 1; // 设置按键状态为按下
    return 0;
}

int key_release(int keycode, t_newinfo *info)
{
    key_states[keycode] = 0; // 设置按键状态为未按下
    return 0;
}

// int	main(void)
// {
// 	t_newinfo info;


// 	info.mlx = mlx_init();
// 	info.win = mlx_new_window(info.mlx, 1024, 512, "MiniLibX Window");


// 	// for (int i = 0; i < 10 ; i ++)
// 	// 	for (int j = 0 ; j < 10; j ++)
// 	// 		dw_cube (i, j, mlx_ptr, win_ptr);
// 	dw_player (px , py, info.mlx, info.win);
// 	mlx_hook(info.win, KeyPress, KeyPressMask, key_press, &info);
//     mlx_hook(info.win, KeyRelease, KeyReleaseMask, key_release, &info);

// 	mlx_loop_hook(info.mlx, repeat_actions, &info);
// 	mlx_loop(info.mlx);

// 	return (0);
// }

void init_image_buffer(t_newinfo *info) {
    int width = 1024; // 窗口宽度
    int height = 512; // 窗口高度
    int bits_per_pixel, line_length, endian;
    
    info->img = mlx_new_image(info->mlx, width, height); // 创建图像
    info->addr = mlx_get_data_addr(info->img, &bits_per_pixel, &line_length, &endian); // 获取数据地址
}

void put_pixel_to_image(t_newinfo *info, int x, int y, int color) {
    char *dst = info->addr + (y * line_length + x * (bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int draw_player_and_background(t_newinfo *info) {
    // 假设已经创建并初始化了图像缓冲区
    dw_bankg(info->mlx, info->win); // 使用图像缓冲区绘制背景
    dw_player(px, py, info->mlx, info->win); // 使用图像缓冲区绘制玩家
    mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0); // 将图像绘制到窗口
	return 0;
}

// int main(void) {
//     t_newinfo info;
    
//     // 初始化和窗口创建省略...
//     init_image_buffer(&info); // 初始化图像缓冲区
//     mlx_loop_hook(info.mlx, draw_player_and_background, &info); // 设置循环中的绘图回调
//     mlx_loop(info.mlx); // 开始事件循环
// }
