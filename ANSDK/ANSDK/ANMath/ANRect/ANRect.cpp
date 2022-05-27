#include "../../ANSDK.h"

anRect::anRect()
{

}

anRect::anRect(float all) :
	first(anVec2(all)), 
	second(anVec2(all))
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

bool anRect::operator!=(anRect o)
{
	return !operator==(o);
}

anRect& anRect::operator=(anRect o)
{
	this->first = o.first;
	this->second = o.second;

	return *this;
}

anRect anRect::operator+(anRect o)
{
	this->first += o.first;
	this->second += o.second;

	return *this;
}

anRect& anRect::operator+=(anRect o)
{
	this->first += o.first;
	this->second += o.second;

	return *this;
}

anRect anRect::operator+(float o)
{
	return anRect(this->first + o, this->second + o);
}

anRect& anRect::operator+=(float o)
{
	this->first += o;
	this->second += o;

	return *this;
}

anRect anRect::operator+(anVec2 o)
{
	return anRect(this->first + o, this->second + o);
}

anRect& anRect::operator+=(anVec2 o)
{
	this->first += o;
	this->second += o;

	return *this;
}

anRect anRect::operator-(anRect o)
{
	return anRect(this->first - o.first, this->second - o.second);
}

anRect& anRect::operator-=(anRect o)
{
	this->first -= o.first;
	this->second -= o.second;

	return *this;
}

anRect anRect::operator-(float o)
{
	return anRect(this->first - o, this->second - o);
}

anRect& anRect::operator-=(float o)
{
	this->first -= o;
	this->second -= o;

	return *this;
}

anRect anRect::operator-(anVec2 o)
{
	return anRect(this->first - o, this->second - o);
}

anRect& anRect::operator-=(anVec2 o)
{
	this->first -= o;
	this->second -= o;

	return *this;
}

anRect anRect::operator*(anRect o)
{
	return anRect(this->first * o.first, this->second * o.second);
}

anRect& anRect::operator*=(anRect o)
{
	this->first *= o.first;
	this->second *= o.second;

	return *this;
}

anRect& anRect::operator*=(float o)
{
	this->first *= o;
	this->second *= o;

	return *this;
}

anRect anRect::operator*(float o)
{
	return anRect(this->first * o, this->second * o);
}

anRect& anRect::operator*=(anVec2 o)
{
	this->first *= o;
	this->second *= o;

	return *this;
}

anRect anRect::operator*(anVec2 o)
{
	return anRect(this->first * o, this->second * o);
}

anRect anRect::operator/(anRect o)
{
	return anRect(this->first / o.first, this->second / o.second);
}

anRect& anRect::operator/=(anRect o)
{
	this->first /= o.first;
	this->second /= o.second;

	return *this;
}

anRect& anRect::operator/=(float o)
{
	this->first /= o;
	this->second /= o;

	return *this;
}

anRect anRect::operator/(float o)
{
	return anRect(this->first / o, this->second / o);
}

anRect& anRect::operator/=(anVec2 o)
{
	this->first /= o;
	this->second /= o;

	return *this;
}

anRect anRect::operator/(anVec2 o)
{
	return anRect(this->first / o, this->second / o);
}

bool anRect::IsIntersected(anVec2 p)
{
	return p.x > first.x && p.y > first.y && p.x <= second.x && p.y <= second.y;
}

anRect& anRect::MakeSizeToDest()
{
	this->second += this->first;
	return *this;
}

anRect anRect::SizeToDest()
{
	return anRect(this->first, this->first + this->second);
}

anRect& anRect::MakeSwapPoints()
{
	auto T_first = this->first;

	this->first = this->second;
	this->second = T_first;

	return *this;
}

anRect anRect::SwapPoints()
{
	return anRect(this->second, this->first);
}

void anRect::Clear()
{
	this->first = this->second = anVec2();
}
