#include "main.h"

char * read_file(char * path){
	
	size_t str_size;
	char * result; 
	FILE * f = fopen(path,"r");

	fseek(f,0,SEEK_END);
	str_size = ftell(f);
	fseek(f,0,SEEK_SET);

	result = malloc(str_size+1);
	fread(result, str_size, 1, f);

	fclose(f);

	result[str_size] = '\0';

	return result;
}

void init_gl(){

	//Init glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(conf->window_w, conf->window_h, "OpenGL", NULL, NULL);

	glfwMakeContextCurrent(window);	

	//Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();
}

void init_vertex(){

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	poly = load_polygon(conf->poly_path);
	
}

void init_shaders(){

	char * shader_source;
	GLint  status;

	printf("\ncompiling vertex shader...");
	shader_source = read_file(conf->vert_shader_path);
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const char * const*)&shader_source, NULL);
	glCompileShader(vertex_shader);
	free(shader_source);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if(GL_TRUE == status)
		printf("\tOK\n");
	else
		printf("\tERROR\n");

	printf("compiling fragment shader...");
	shader_source = read_file(conf->frag_shader_path);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const char * const*)&shader_source, NULL);
	glCompileShader(fragment_shader);
	free(shader_source);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if(GL_TRUE == status)
		printf("\tOK\n");
	else
		printf("\tERROR\n");

	shader_program = glCreateProgram();
	
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glBindFragDataLocation(shader_program, 0, "outColor");
    glLinkProgram(shader_program);
    glUseProgram(shader_program);
}

void init_attributes(){

    pos_attr = glGetAttribLocation(shader_program, "position");
	glEnableVertexAttribArray(pos_attr);
	glVertexAttribPointer(pos_attr, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

	col_attr = glGetAttribLocation(shader_program, "color");
	glEnableVertexAttribArray(col_attr);
	glVertexAttribPointer(col_attr, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    //uni_color = glGetUniformLocation(shader_program, "triangleColor");
}

void init(){

	struct timeval t;
	gettimeofday(&t, NULL);

	start_time = ((float)t.tv_usec)/1000000;

	conf = load_config("config.txt");
	printf(
		"\nUsing the following configuration:\n"
		"\twindow size:        %dx%d\n"
		"\tvertex shader:      %s\n"
		"\tfragment shader:    %s\n"
		"\tpolygon:            %s\n",
		conf->window_w,
		conf->window_h,
		conf->vert_shader_path,
		conf->frag_shader_path,
		conf->poly_path
	);

	init_gl();

	init_vertex();

	init_shaders();

	init_attributes();
}

void terminate(){

    glDeleteProgram(shader_program);
	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);

	destroy_polygon(poly);

    glDeleteVertexArrays(1, &vao);    

	glfwTerminate();

	free_config(conf);
}

void draw(){
	
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	draw_polygon(poly);	

	glfwSwapBuffers(window);
}

void loop(){

	last_time = start_time;

	while(!glfwWindowShouldClose(window)){

	    glfwPollEvents();

	    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    		glfwSetWindowShouldClose(window, GL_TRUE);
	    }

    	//update();
	    
		draw();

		usleep(10000);
	}
}

void update(){

	struct timeval t;
	float          actual_time;
	float          dt;

	gettimeofday(&t, NULL);

	actual_time = ((float)t.tv_usec)/1000000;
	dt = actual_time - last_time;
	last_time = actual_time;

	//Ni idea, por ahora no me molesto en resolverlo 
	if(dt < 0){
		return;
	}

	update_polygon(dt,poly);
}

int main( int argc, char ** argv){

	init();

	loop();

    terminate();

    return 0;
}