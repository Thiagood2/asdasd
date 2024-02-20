#ifndef BLOCKS_H
#define BLOCKS_H
#include "Object.h"

class Blocks : public Object {
public:
	Blocks(float x, float y, float width, float height, Color color, bool is_especial = false);
	bool isSpecialBlock() const {return es_especial;};
	
private:
	bool es_especial; 
};

#endif

