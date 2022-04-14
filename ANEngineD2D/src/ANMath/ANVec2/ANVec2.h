#pragma once

class anVec2
{
public:
	anVec2();
	anVec2(float X, float Y);
	~anVec2();

	bool operator==(anVec2 o);

	anVec2 operator+(anVec2 o);
	void operator+=(anVec2 o);

	float x, y;
private:

};

