#include "Color.h"
#include "RandomHelper.h"

Color Color::White = Color(1.0f, 1.0f, 1.0f);
Color Color::Black = Color(0.0f, 0.0f, 0.0f);
Color Color::Red = Color(1.0f, 0.0f, 0.0f);
Color Color::Green = Color(0.0f, 1.0f, 0.0f);
Color Color::Blue = Color(0.0f, 0.0f, 1.0f);

Color Color::RandomColor()
{
	return Color(Random(0.0f, 1.0f), Random(0.0f, 1.0f), Random(0.0f, 1.0f));
}
