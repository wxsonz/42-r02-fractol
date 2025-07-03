#include "fractol.h"

double	map(double val, double n_min, double n_max, double o_max)
{
	return ((val / o_max) * (n_max - n_min)) + n_min;
}

double	screen_to_world(double screen_coord, double offset, double zoom, double max_dim)
{
	double	range;

	range = 4.0;
	return ((screen_coord / zoom / max_dim) * range - (range / 2.0) + offset);
}

void	adjust_offsets_for_zoom(t_fractal *f, double zoom_factor)
{
	double	mouse_world_x;
	double	mouse_world_y;
	int32_t	current_mouse_x;
	int32_t	current_mouse_y;

	mlx_get_mouse_pos(f->mlx, &current_mouse_x, &current_mouse_y);
	mouse_world_x = screen_to_world(current_mouse_x, f->offset_x, f->zoom, WIDTH);
	mouse_world_y = screen_to_world(current_mouse_y, f->offset_y, f->zoom, HEIGHT);
	f->zoom *= zoom_factor;
	f->offset_x = mouse_world_x - screen_to_world(current_mouse_x, 0, f->zoom, WIDTH);
	f->offset_y = mouse_world_y - screen_to_world(current_mouse_y, 0, f->zoom, HEIGHT);
}
