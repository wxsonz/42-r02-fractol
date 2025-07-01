#include "fractol.h"

// Helper to create a color from RGB components
static uint32_t	rgb_to_int(uint8_t r, uint8_t g, uint8_t b)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | 0xFF);
}

// Maps an iteration value to a color
uint32_t	get_color(int value, int max_value)
{
	double	t;

	if (value == max_value)
		return (rgb_to_int(0, 0, 0));
	t = (double)value / (double)max_value;
	if (t < 0.1)
		return (rgb_to_int(
				(uint8_t)(sin(1.5 * M_PI * t) * 100 + 20),
				(uint8_t)(sin(2.0 * M_PI * t) * 120 + 100),
				(uint8_t)(cos(1.0 * M_PI * t) * 150 + 80)));
	else if (t < 0.3)
		return (rgb_to_int(
				(uint8_t)(cos(0.5 * M_PI * t) * 150 + 50),
				(uint8_t)(sin(1.5 * M_PI * t) * 180 + 50),
				(uint8_t)(sin(2.5 * M_PI * t) * 100 + 120)));
	else
		return (rgb_to_int(
				(uint8_t)(sin(3.0 * M_PI * t) * 127 + 128),
				(uint8_t)(cos(2.0 * M_PI * t) * 127 + 128),
				(uint8_t)(sin(1.0 * M_PI * t) * 127 + 128)));
}
