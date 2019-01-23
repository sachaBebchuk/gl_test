#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_BUFFER_SIZE 128
#define POLY_PATH_DEFAULT "polis/cuadrado.txt"
#define FRAG_SHADER_PATH_DEFAULT "shaders/shader4.frag"
#define VERT_SHADER_PATH_DEFAULT "shaders/shader4.vert"

typedef struct config{
	char * frag_shader_path;
	char * vert_shader_path;
	char * poly_path;
	int    window_w;
	int    window_h;
} config;

config * load_config(char*);
void     free_config(config*);
void     set_config_attr(config*,char*);
char   * copy_string(char*);

#endif