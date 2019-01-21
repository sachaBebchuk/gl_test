#include "config.h"

config* load_config(char * path){

	config * conf = malloc(sizeof(config));

	conf->poly_path = "polis/triangulo.txt";
	conf->frag_shader_path = "shaders/shader4.frag";
	conf->vert_shader_path = "shaders/shader4.vert";
	conf->window_h = 600;
	conf->window_w = 800;

	return conf;
}

void free_config(config *conf){
	free(conf);
}