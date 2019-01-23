#include "config.h"

config* load_config(char * path){

	char   *buffer = malloc(CONFIG_BUFFER_SIZE);
	FILE   *f;
	config *conf = malloc(sizeof(config));

	conf->poly_path = NULL;
	conf->frag_shader_path =NULL;
	conf->vert_shader_path =NULL;
	conf->window_w = 800;
	conf->window_h = 600;

	f = fopen("config.txt","r");

	do{

		memset(buffer,0,CONFIG_BUFFER_SIZE);

		if(!fgets(buffer,CONFIG_BUFFER_SIZE,f))
			break;

		set_config_attr(conf,buffer);

	}while(1);

	if(!conf->poly_path){
		conf->poly_path = copy_string(POLY_PATH_DEFAULT);
	}
	if(!conf->frag_shader_path){
		conf->frag_shader_path = copy_string(FRAG_SHADER_PATH_DEFAULT);
	}
	if(!conf->vert_shader_path){
		conf->vert_shader_path = copy_string(VERT_SHADER_PATH_DEFAULT);
	}

	fclose(f);
	free(buffer);

	return conf;
}

void set_config_attr(config *conf, char* attr){

	char *attr_name;
	char *attr_value;

	attr_name = strtok(attr," =\n");
	attr_value = strtok(NULL," =\n");

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