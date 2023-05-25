#pragma once

#include "common.h"

class Texture {

public:
	int w=0;
	int h=0;
	unsigned int glId=-1;

	Texture(std::string fileName);
	void bind(int textureunitIdx);


};