#pragma once

class anVec3
{
public:
	anVec3();
	anVec3(float X, float Y, float Z);
	~anVec3();

	bool operator==(anVec3 o);

	anVec3 operator+(anVec3 o);
	void operator+=(anVec3 o);

	float x, y, z;
private:

};

