#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define PI 3.14159265

#define VERTEX_LEN 5

typedef struct polygon{
	float *vertices;
	int    vertices_len;
	int    vertices_count;
} polygon;

polygon * load_polygon(char*);
void      destroy_polygon(polygon*);

void update_polygon(float,polygon*);
void move_polygon(float,polygon*);
void update_color(float,polygon*);


#endif