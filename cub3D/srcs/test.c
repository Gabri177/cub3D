#include "../header/so_long.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 510
#define BLOCK_SIZE 10
#define PI 3.1415926

int mapX=8, mapY=8, mapS=64;
float pdx, pdy, pa;


int map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

typedef struct s_info {
	void    *mlx;
	void    *win;
	void	*background;
	int     pos_x;
	int     pos_y;
	int     move_up;
	int     move_down;
	int     move_left;
	int     move_right;
}              t_info;


void drawRays3D(t_info *info); //decclaracion de una funcion
float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void	draw_line(int x1, int y1, int x2, int y2, t_info *vars, int color) // dibujar una linea desde punto x1, y1 hasta x2, y2
{
	double dx, dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs (dx) > fabs (dy)) ? fabs (dx) : fabs (dy);
	dx /= e;
	dy /= e;
	x = x1;
	y = y1;
	for (int i = 0; i < e; i ++)
	{
		mlx_pixel_put(vars->mlx, vars->win, x + 0.5, y + 0.5, color);
		x += dx;
		y += dy;
	}

}


void	apoyo_draw_map(int x, int y, int color, t_info *vars) // dibujar un cuadrado que es una parte del mapa
{
	int xend = mapS + x - 1;
	int yend = mapS + y - 1;
	int yori = y;

	while (x < xend)
	{
		y = yori;
		while (y < yend)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, color);
			y ++;
		}
		x ++;
	}
}

void	draw_map(t_info *vars) // dibujar el background 
{
	int x,y,x0,y0;

	for (y = 0; y < mapY; y ++)
	{
		for (x = 0; x < mapX; x ++)
		{
			if (map[y*mapX+x] == 1)
				apoyo_draw_map (x*mapS, y*mapS, 0x2E8B57,  vars);
			else
				apoyo_draw_map (x*mapS, y*mapS, 0xF0FFF0,  vars);
		}
	}
}



void    draw_square(t_info *vars) // dibujar caracter (personaje)
{
	mlx_clear_window(vars->mlx, vars->win);
	draw_map (vars);
	for (int y = vars->pos_y; y < vars->pos_y + BLOCK_SIZE; y++)
	{
		for (int x = vars->pos_x; x < vars->pos_x + BLOCK_SIZE; x++)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, 0xFFD700); // Draw in white
		}
	}
	draw_line( vars->pos_x + BLOCK_SIZE / 2,  vars->pos_y + BLOCK_SIZE / 2, vars->pos_x + pdx + BLOCK_SIZE / 2,  vars->pos_y + pdy + BLOCK_SIZE / 2, vars, 0x000000);
	drawRays3D (vars);
}

void    move_square(t_info *vars) // en mlx_loop para moverse y controlar el angulo
{
	if (vars->move_up)
	{
		vars->pos_x += pdx;
		vars->pos_y += pdy;
		//px += pdx;
		//py += pdy;
	}
	if (vars->move_down)
	{
		vars->pos_x -= pdx;
		vars->pos_y -= pdy;
		//px -= pdx;
		//py -= pdy;
	}
	if (vars->move_left)
	{
		//vars->pos_x -= 10;
		pa += 5;
		pa = FixAng(pa);
		pdx = cos (degToRad(pa)) * 15;
		pdy = -sin (degToRad(pa)) * 15;
	}
	if (vars->move_right)
	{
		//vars->pos_x += 10;
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos (degToRad(pa)) * 15;
		pdy = -sin (degToRad(pa)) * 15;
	}
	draw_square(vars);
	//draw_line(px, py ,px + pdx * 5, py + pdy * 5, vars, 0x000000);
}

int     key_press(int keycode, t_info *vars) {
	if (keycode == 53) // Esc key to quit
		exit(0);
	if (keycode == 126) // Up arrow
		vars->move_up = 1;
	if (keycode == 125) // Down arrow
		vars->move_down = 1;
	if (keycode == 123) // Left arrow
		vars->move_left = 1;
	if (keycode == 124) // Right arrow
		vars->move_right = 1;
	return (0);
}

int     key_release(int keycode, t_info *vars) {
	if (keycode == 126) // Up arrow
		vars->move_up = 0;
	if (keycode == 125) // Down arrow
		vars->move_down = 0;
	if (keycode == 123) // Left arrow
		vars->move_left = 0;
	if (keycode == 124) // Right arrow
		vars->move_right = 0;
	return (0);
}

void drawRays3D(t_info *info)
{
	int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
	
	ra=FixAng(pa+30);//ray set back 30 degrees
	
	for(r=0;r<60;r++)
	{
		//---Vertical--- 
	dof=0; side=0; disV=100000;
	float Tan=tan(degToRad(ra));
		if(cos(degToRad(ra))> 0.001){ rx=(((int)(info->pos_x)>>6)<<6)+64;      ry=((info->pos_x)-rx)*Tan+(info->pos_y); xo= 64; yo=-xo*Tan;}//looking left
	else if(cos(degToRad(ra))<-0.001){ rx=(((int)(info->pos_x)>>6)<<6) -0.0001; ry=((info->pos_x)-rx)*Tan+(info->pos_y); xo=-64; yo=-xo*Tan;}//looking right
	else { rx=(info->pos_x); ry=(info->pos_y); dof=8;}                                                  //looking up or down. no hit  

	while(dof<8) 
	{ 
	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-(info->pos_x))-sin(degToRad(ra))*(ry-(info->pos_y));}//hit         
	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	} 
	vx=rx; vy=ry;

	//---Horizontal---
	dof=0; disH=100000;
	Tan=1.0/Tan; 
		if(sin(degToRad(ra))> 0.001){ ry=(((int)(info->pos_y)>>6)<<6) -0.0001; rx=((info->pos_y)-ry)*Tan+(info->pos_x); yo=-64; xo=-yo*Tan;}//looking up 
	else if(sin(degToRad(ra))<-0.001){ ry=(((int)(info->pos_y)>>6)<<6)+64;      rx=((info->pos_y)-ry)*Tan+(info->pos_x); yo= 64; xo=-yo*Tan;}//looking down
	else{ rx=(info->pos_x); ry=(info->pos_y); dof=8;}                                                   //looking straight left or right
	
	while(dof<8) 
	{ 
	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
	if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-(info->pos_x))-sin(degToRad(ra))*(ry-(info->pos_y));}//hit         
	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	} 
	
	if(disV<disH){ rx=vx; ry=vy; disH=disV;}                  //horizontal hit first
	//draw 2D ray
	draw_line(info->pos_x + BLOCK_SIZE / 2,(info->pos_y) + BLOCK_SIZE / 2, rx,ry, info, 0xFF8C00);
	int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
	int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
	int lineOff = 160 - (lineH>>1);                                               //line offset
	
	//draw vertical wall  
	for (int k = 0; k < 10; k ++)
		draw_line(r*8+530 + k, lineOff, r*8+530 + k, lineOff+lineH, info, 0xFF8C00);
	ra=FixAng(ra-1);                                                              //go to next ray
 	}
}

/* void normalizeAngle(float *angle) {
	while (*angle < 0) *angle += 2 * PI;
	while (*angle >= 2 * PI) *angle -= 2 * PI;
}

void castRay(t_info *info, float ra) {
	float distToWall = 0; // iniciar la direccon entre la pared y la personaje
	bool hitWall = false; // indicador si hit la pared
	float stepSize = 0.1; // El tamaño del paso del rayo se puede ajustar para optimizar el rendimiento y la precisión.
	float rayX = info->pos_x + BLOCK_SIZE / 2; // x incical de rayas
	float rayY = info->pos_y + BLOCK_SIZE / 2; // y inicial de rayas
	float rayAngle  = ra; // cambiar el angulo con ra + PI

	while (!hitWall && distToWall < mapS * mapX) {
		rayX += cos(rayAngle) * stepSize;
		rayY += sin(rayAngle) * stepSize;
		distToWall += stepSize;

		int mapXIdx = (int)rayX / mapS;
		int mapYIdx = (int)rayY / mapS;
		float disT = dist (info->pos_x + BLOCK_SIZE / 2, info->pos_y + BLOCK_SIZE / 2, rayX, rayY);

		// 边界检查
		if (mapXIdx >= 0 && mapXIdx < mapX && mapYIdx >= 0 && mapYIdx < mapY) {
			if (map[mapYIdx * mapX + mapXIdx] == 1) { // detecta la pared
				hitWall = true;
				draw_line(info->pos_x + BLOCK_SIZE / 2, info->pos_y + BLOCK_SIZE / 2, rayX, rayY, info, 0xFF8C00); // dibujar rayas
			}
		}

		//3d
		float lineH = (mapS * 320) / disT;
		if (lineH > 320)
			lineH = 320;

	}
}

void drawRays3D(t_info *info)	//dibujar una raya
{
	normalizeAngle(&pa);
	//for (int i = pa - PI / 6; i < pa + PI / 6 ; i += PI / 10)
	castRay(info, pa - PI / 6);
	castRay(info, pa - PI / 9);
	castRay(info, pa - PI / 18);
	castRay(info, pa);
	castRay(info, pa + PI / 18);
	castRay(info, pa + PI / 9);
	castRay(info, pa + PI / 6); 
	normalizeAngle(&pa); // confirmar que PI esta dentro de  0 a 2*PI 
	int numRays = 30; // el numero de rayos que vamos a lanzar
	float startAngle = pa - PI / 6; // angulo de rayos iniciales
	normalizeAngle(&startAngle); // confirmar que PI esta dentro de  0 a 2*PI 
	float angleIncrement = PI / 3 / numRays; // Basado en la cantidad de rayos, calcula el incremento del ángulo.

	for (int i = 0; i <= numRays; i++)
	{
		float currentAngle = startAngle + i * angleIncrement;
		normalizeAngle(&currentAngle); // confirmar que PI esta dentro de  0 a 2*PI 
		castRay(info, currentAngle);
	}
} */

int	main(void)
{
	t_info	vars;

	pa =  0;
	pdx = cos(pa) * 15;
	pdy = -sin(pa) * 15;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Move the Square!");
	vars.pos_x = WIN_WIDTH / 4 - BLOCK_SIZE / 2;
	vars.pos_y = WIN_HEIGHT / 4 - BLOCK_SIZE / 2;
	vars.move_up = vars.move_down = vars.move_left = vars.move_right = 0;
	//vars.background = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_square(&vars); // Initially draw the square
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars); // Listen for key press events
	mlx_hook(vars.win, 3, 1L<<1, key_release, &vars); // Listen for key release events
	mlx_loop_hook(vars.mlx, (void *)move_square, &vars); // Continuously move the square if needed
	mlx_loop(vars.mlx);
	return 0;
}
