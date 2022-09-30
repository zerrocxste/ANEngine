#pragma once

class anRect
{
public:
	anRect();
	anRect(float all);
	anRect(anVec2 First, anVec2 Second);
	anRect(float x1, float y1, float x2, float y2);
	~anRect();

	bool operator==(anRect o);
	bool operator!=(anRect o);

	anRect& operator=(anRect o);

	anRect operator+(anRect o);
	anRect& operator+=(anRect o);
	anRect operator+(float o);
	anRect& operator+=(float o);
	anRect operator+(anVec2 o);
	anRect& operator+=(anVec2 o);

	anRect operator-(anRect o);
	anRect& operator-=(anRect o);
	anRect operator-(float o);
	anRect& operator-=(float o);
	anRect operator-(anVec2 o);
	anRect& operator-=(anVec2 o);

	anRect operator*(anRect o);
	anRect& operator*=(anRect o);
	anRect& operator*=(float o);
	anRect operator*(float o);
	anRect& operator*=(anVec2 o);
	anRect operator*(anVec2 o);

	anRect operator/(anRect o);
	anRect& operator/=(anRect o);
	anRect& operator/=(float o);
	anRect operator/(float o);
	anRect& operator/=(anVec2 o);
	anRect operator/(anVec2 o);

	bool IsIntersected(anVec2 p);

	anRect& MakeSizeToDest();
	anRect SizeToDest();

	anRect& MakeSwapPoints();
	anRect SwapPoints();

	anRect RecalcWithRelativeDistance();
	anVec2 GetPointsDistantion();

	void Clear();

	anVec2 first;
	anVec2 second;

private:
	
};

