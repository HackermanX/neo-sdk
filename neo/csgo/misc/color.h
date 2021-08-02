#pragma once

#include <cstdint>
#include <cmath>

class color
{
public:
	color();
	color(int _r, int _g, int _b);
	color(int _r, int _g, int _b, int _a);
	color(float _r, float _g, float _b) : color(_r, _g, _b, 1.0f) {}
	color(float _r, float _g, float _b, float _a)
		: color(
			static_cast<int>(_r * 255.0f),
			static_cast<int>(_g * 255.0f),
			static_cast<int>(_b * 255.0f),
			static_cast<int>(_a * 255.0f))
	{
	}
	explicit color(float* rgb) : color(rgb[0], rgb[1], rgb[2], 1.0f) {}
	explicit color(unsigned long argb)
	{
		_Ccolor[2] = (unsigned char)((argb & 0x000000FF) >> (0 * 8));
		_Ccolor[1] = (unsigned char)((argb & 0x0000FF00) >> (1 * 8));
		_Ccolor[0] = (unsigned char)((argb & 0x00FF0000) >> (2 * 8));
		_Ccolor[3] = (unsigned char)((argb & 0xFF000000) >> (3 * 8));
	}

	void    set_raw_color(int color32);
	int     get_raw_color() const;
	void    set_color(int _r, int _g, int _b, int _a = 0);
	void    set_color(float _r, float _g, float _b, float _a = 0);
	void    get_color(int& _r, int& _g, int& _b, int& _a) const;

	int r() const { return _Ccolor[0]; }
	int g() const { return _Ccolor[1]; }
	int b() const { return _Ccolor[2]; }
	int a() const { return _Ccolor[3]; }

	unsigned char& operator[](int index)
	{
		return _Ccolor[index];
	}
	const unsigned char& operator[](int index) const
	{
		return _Ccolor[index];
	}

	bool operator==(const color& rhs) const;
	bool operator!=(const color& rhs) const;
	color& operator=(const color& rhs);

	static color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		int hh = int(floor(h));
		switch (hh) {
		case 0:
			return color(brightness, t, p);
		case 1:
			return color(q, brightness, p);
		case 2:
			return color(p, brightness, t);
		case 3:
			return color(p, q, brightness);
		case 4:
			return color(t, p, brightness);
		default:
			return color(brightness, p, q);
		}
	}
private:
	unsigned char _Ccolor[4];
};