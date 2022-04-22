#pragma once

class anColor
{
public:
	anColor();
	anColor(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A);
	anColor(std::uint8_t R, std::uint8_t G, std::uint8_t B);
	anColor(std::uint32_t hex);
	~anColor();

	std::uint8_t& operator[](std::uint32_t idx);

	int AtByteArr();

	anColor& MakeRand();

	static const anColor Red();
	static const anColor Green();
	static const anColor Blue();
	static const anColor Yellow();
	static const anColor Magenta();
	static const anColor Aqua();
	static const anColor Grey();
	static const anColor White();
	static const anColor Black();
private:
	std::uint8_t r, g, b, a;
};