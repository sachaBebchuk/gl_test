#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct config{
	char * frag_shader_path;
	char * vert_shader_path;
	char * poly_path;
} config;

config * load_config(char*);
void     free_config(config*);

#endif