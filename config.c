#include "config.h"

config* load_config(char * path){

	char   buffer[128];
	FILE   *f;
	config *conf = malloc(sizeof(config));

	conf->poly_path = NULL;
	conf->frag_shader_path =NULL;
	conf->vert_shader_path =NULL;
	conf->window_w = 800;
	conf->window_h = 600;

	f = fopen("config.txt","r");

	memset(buffer,0,sizeof(buffer));

	while( fgets(buffer,sizeof(buffer),f) ){

		set_config_attr(conf,buffer);
		memset(buffer,0,sizeof(buffer));
	}

	fclose(f);

	if(!conf->poly_path){
		conf->poly_path = copy_string(POLY_PATH_DEFAULT);
	}
	if(!conf->frag_shader_path){
		conf->frag_shader_path = copy_string(FRAG_SHADER_PATH_DEFAULT);
	}
	if(!conf->vert_shader_path){
		conf->vert_shader_path = copy_string(VERT_SHADER_PATH_DEFAULT);
	}

	return conf;
}

void set_config_attr(config *conf, char* attr){

	char *attr_name;
	char *attr_value;

	attr_name = strtok(attr,"=");
	attr_value = attr+strlen(attr_name);

	if(!strncmp(attr_name,"poly",4)){
		conf->poly_path = copy_string(attr_value);
		return;
	}
	
	if(!strncmp(attr_name,"frag_shader",11)){
		conf->frag_shader_path = copy_string(attr_value);
		return;
	}
	
	if(!strncmp(attr_name,"vert_shader",11)){
		conf->vert_shader_path = copy_string(attr_value);
		return;
	}
	
	if(!strncmp(attr_name,"w_width",7)){
		conf->window_w = atoi(attr_value);
		return;
	}

	if(!strncmp(attr_name,"w_height",8)){
		conf->window_h = atoi(attr_value);
		return;
	}
}

char* copy_string(char *str){

	char *result = malloc(strlen(str)+1);
	
	strcpy(result,str);

	return result;
}

void free_config(config *conf){
	free(conf->poly_path);
	free(conf->vert_shader_path);
	free(conf->frag_shader_path);
	free(conf);
}