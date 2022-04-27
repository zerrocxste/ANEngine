#include "../../ANSDK.h"

anColor::anColor() : r(0), g(0), b(0), a(0)
{

}

anColor::anColor(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A) : r(R), g(G), b(B), a(A)
{

}

anColor::anColor(std::uint8_t R, std::uint8_t G, std::uint8_t B) : r(R), g(G), b(B), a(255)
{

}

anColor::anColor(std::uint32_t hex)
{
	memcpy(this, &hex, 4);
}

anColor::~anColor()
{

}

std::uint8_t& anColor::operator[](std::uint32_t idx)
{
	if (idx > RGBA_MAX_SIZE)
	{
		auto n = std::uint8_t(0);
		return n;
	}

	return ((std::uint8_t*)(this))[idx];
}

int anColor::AtByteArr()
{
	int Color = 0;
	memcpy(&Color, this, 4);
	return Color;
}

anColor& anColor::MakeRand()
{
	this->r = rand() % 255;
	this->g = rand() % 255;
	this->b = rand() % 255;
	this->a = 255;
	return *this;
}

const anColor anColor::Rand()
{
	return anColor().MakeRand();
}

const anColor anColor::Red()
{
	return anColor(255, 0, 0);
}

const anColor anColor::Green()
{
	return anColor(0, 255, 0);
}

const anColor anColor::Blue()
{
	return anColor(0, 0, 255);
}

const anColor anColor::Yellow()
{
	return anColor(255, 255, 0);
}

const anColor anColor::Magenta()
{
	return anColor(255, 0, 255);
}

const anColor anColor::Aqua()
{
	return anColor(0, 255, 255);
}

const anColor anColor::Grey()
{
	return anColor(128, 128, 128);
}

const anColor anColor::White()
{
	return anColor(255, 255, 255);
}

const anColor anColor::Black()
{
	return anColor(0, 0, 0);
}