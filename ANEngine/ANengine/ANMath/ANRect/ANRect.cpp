#include "../../ANEngine.h"

anRect::anRect()
{

}

anRect::anRect(anVec2 First, anVec2 Second) : 
	first(First), second(Second)
{

}

anRect::anRect(float x1, float y1, float x2, float y2)
{
	first.x = x1;
	first.y = y1;

	second.x = x2;
	second.y = y2;
}

anRect::~anRect()
{

}

bool anRect::operator==(anRect o)
{
	return this->first == o.first && this->second == o.second;
}

anRect anRect::operator+(anRect o)
{
	return anRect(this->first + o.first, this->second + o.second);
}

void anRect::operator+=(anRect o)
{
	this->first += o.first;
	this->second += o.second;
}
