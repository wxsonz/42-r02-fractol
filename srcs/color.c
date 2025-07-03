#include "fractol.h"

// Helper to create a color from RGB components
static uint32_t	rgb_to_int(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

// Helper for linear interpolation between two color components
static uint8_t	lerp(uint8_t start, uint8_t end, double t)
{
	return ((uint8_t)(start + t * (end - start)));
}

// Generates the color palette using linear interpolation.
void	init_palette(t_fractal *f)
{
	static const uint32_t	key_colors[] = {
		0x000000FF,
		0x00429dFF,
		0xfee090FF,
		0xFFFFFFFF
	};
	int						num_keys;
	int						segment_size;
	int						i;

	num_keys = sizeof(key_colors) / sizeof(key_colors[0]);
	segment_size = PALETTE_SIZE / (num_keys - 1);
	i = 0;
	while (i < PALETTE_SIZE)
	{
		int			seg_idx;
		uint32_t	c1;
		uint32_t	c2;
		double		t;
		uint8_t		r;
		uint8_t		g;
		uint8_t		b;

		seg_idx = i / segment_size;
		if (seg_idx >= num_keys - 1)
		{
			f->palette[i++] = key_colors[num_keys - 1];
			continue;
		}
		c1 = key_colors[seg_idx];
		c2 = key_colors[seg_idx + 1];
		t = (double)(i % segment_size) / (double)(segment_size - 1);
		r = lerp((c1 >> 24) & 0xFF, (c2 >> 24) & 0xFF, t);
		g = lerp((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, t);
		b = lerp((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, t);
		f->palette[i++] = rgb_to_int(r, g, b);
	}
}

// Highly optimized get_color function
uint32_t	get_color(t_fractal *f, int value, int max_value)
{
	if (value == max_value)
		return (0x000000FF);
	return (f->palette[value % PALETTE_SIZE]);
}

