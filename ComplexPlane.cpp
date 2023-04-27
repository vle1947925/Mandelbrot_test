#include "ComplexPlane.h"
#include <sstream>
#include <iostream>
#include <complex>

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	float x;
	float y;
	m_zoomCount++;
	x = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
	y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	float x;
	float y;
	m_zoomCount--;
	x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	text.setCharacterSize(24);
	text.setFillColor(Color::Red);
	text.setPosition(0, 0);

	Vector2f centerCoord = m_view.getCenter();



	std::stringstream ss;
	ss << "Mandelbrot Set" << endl;
	ss << "Center: (" << centerCoord.x << "," << centerCoord.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom in" << endl;
	ss << "Right-click to Zoom out" << endl;
	text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	std::complex<double> c(coord.x, coord.y);
	std::complex<double> z(0, 0);
	size_t iter = 0;

	while (abs(z) < 2 && iter < MAX_ITER)
	{
		z = z * z + c;
		iter++;
	}
	return iter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count > 57)
	{
		r = 255;
		g = 255 * (0);
		b = 255 * (0);
	}
	else if (count > 49)
	{
		r = 255;
		g = 255 / 2;
		b = 255 * (0);
	}
	else if (count > 41)
	{
		r = 255 * (0.75);
		g = 255;
		b = 255 * (0);
	}
	else if (count > 33)
	{
		r = 255 * (0.5);
		g = 255;
		b = 255 * (0);
	}
	else if (count > 25)
	{
		r = 255 * (0);
		g = 255;
		b = 255 * (0.5);
	}
}