#pragma once

class anVec2
{
public:
	anVec2();
	anVec2(float all);
	anVec2(float X, float Y);
	~anVec2();

	bool operator!();

	bool operator==(anVec2 o);
	bool operator!=(anVec2 o);

	anVec2& operator=(anVec2 o);
	anVec2& operator=(float o);

	anVec2 operator+(anVec2 o);
	anVec2& operator+=(anVec2 o);
	anVec2& operator+=(float o);
	anVec2 operator+(float o);

	anVec2 operator-(anVec2 o);
	anVec2& operator-=(anVec2 o);
	anVec2& operator-=(float o);
	anVec2 operator-(float o);

	anVec2 operator*(anVec2 o);
	anVec2& operator*=(anVec2 o);
	anVec2& operator*=(float o);
	anVec2 operator*(float o);

	anVec2 operator/(anVec2 o);
	anVec2& operator/=(anVec2 o);
	anVec2& operator/=(float o);
	anVec2 operator/(float o);

	anVec2 Inverse();

	void Clear();

	float x, y;
private:

};
