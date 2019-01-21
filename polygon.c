#include "polygon.h"

polygon * load_polygon(char * path){

	int      i;
	FILE    *f = fopen(path,"r");
	polygon *p = malloc(sizeof(polygon));

	fscanf(f,"%d",&p->vertices_count);

	p->vertices_len = sizeof(float) * p->vertices_count * VERTEX_LEN;

	p->vertices = malloc( p->vertices_len );

	for(i = 0; i < p->vertices_count * VERTEX_LEN; i++){
		fscanf(f,"%f",p->vertices + i);
	}

	fclose(f);

	printf("\nPolygon loaded:\n"
	       "\tvertices length: %d\n"
	       "\tvertices count: %d\n",
	       p->vertices_len,p->vertices_count
	);

	return p;
}

void destroy_polygon( polygon * p){
	free(p->vertices);
	free(p);
}

void update_polygon(float dt,polygon *p){

	move_polygon(dt,p);
	update_color(dt,p);

	//glBufferData(GL_ARRAY_BUFFER, p->vertices_len, p->vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, p->vertices_len, p->vertices, GL_STREAM_DRAW);
}

void update_color(float dt,polygon *p){

	static float   time_elapsed = 0.0f;
	static float   v = 0.50f;
	float        * color;
	int            i;
	int            j;

	time_elapsed += dt;

	for(i = 0; i < p->vertices_count * VERTEX_LEN; i+=VERTEX_LEN){
		
		color = p->vertices + i + 2;

		for(j = 0; j < 2; j++){

			if(color[j])
				color[j] = (sin( (color[j] + time_elapsed) * PI * v ) + 1.0f) / 2.0f;
		}
	}

	//glUniform3f(uni_color, (sin(time_elapsed * PI * v) + 1.0f) / 2.0f, 0.0f, 0.0f);	
}

void move_polygon(float dt,polygon *p){

	float x_vel = 0.25;
	float y_vel = 0.25;
	int   i;

	for( i = 0; i < p->vertices_count * VERTEX_LEN; i+=VERTEX_LEN ){
		p->vertices[i]   += dt * x_vel;
		p->vertices[i+1] += dt * y_vel;
	}
}