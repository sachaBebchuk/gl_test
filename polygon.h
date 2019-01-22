#ifndef __POLYGON_H__
#define __POLYGON_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define PI 3.14159265

//Amount of float elements in a vertex
#define VERTEX_LEN 5

typedef struct polygon{
	float  *vertices;       //Array with the vertex data
	int     vertices_len;   //Length of the vertices in bytes
	int     vertices_count; //Amount of vertices in the polygon
	GLuint  vbo;            //Vertex buffer object
	GLuint  ebo;            //Element buffer object
	GLuint *elements;       //Element array
	int     elements_count; //Count of elements array
} polygon;

polygon * load_polygon(char*);
void      destroy_polygon(polygon*);

void update_polygon(float,polygon*);
void move_polygon(float,polygon*);
void update_color(float,polygon*);

#endif