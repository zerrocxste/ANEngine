#pragma once

class anRect
{
public:
	anRect();
	anRect(anVec2 First, anVec2 Second);
	anRect(float x1, float y1, float x2, float y2);
	~anRect();

	bool operator==(anRect o);

	anRect operator+(anRect o);
	void operator+=(anRect o);

	anVec2 first;
	anVec2 second;

private:

};

