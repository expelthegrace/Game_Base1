#ifndef _TRIANGLEMODULE_
#define _TRIANGLEMODULE_

#include "Globals.h"
#include "Module.h"
#include "SDL/include/SDL.h"
#include "glew.h"


class TriangleModule :
	public Module
{
public:
	TriangleModule();
	virtual ~TriangleModule();

	bool Init();
	GLuint vbo;
	//update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	
	float rotX, rotY, rotZ;

};

#endif