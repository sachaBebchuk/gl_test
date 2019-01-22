#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "polygon.h"

//Globals
float        start_time;
float        last_time;
config     * conf;
polygon    * poly;

//GL handlers
GLFWwindow * window;
GLuint       vertex_shader;
GLuint       fragment_shader;
GLuint       shader_program;
GLuint       vao;
GLint        pos_attr;
GLint        col_attr;
//GLint        uni_color;


//Functions
char    * read_file(char*);
void      init_gl();
void      init_vertex();
void      init_shaders();
void      init_attributes();
void      init();
void      draw();
void      loop();
void      update();

#endif