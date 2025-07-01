#include "fractol.h"

// Maps a value from one range to another
double	map(double val, double n_min, double n_max, double o_max)
{
	return ((val / o_max) * (n_max - n_min)) + n_min;
}

// Adjusts view offsets to keep the point under the mouse cursor fixed during zoom
void	adjust_offsets_for_zoom(t_fractal *f, double zoom_factor)
{
	double	mouse_cx;
	double	mouse_cy;
	double	new_cx;
	double	new_cy;

	mlx_get_mouse_pos(f->mlx, &f->mouse_x, &f->mouse_y);
	mouse_cx = map(f->mouse_x, -2.0, 2.0, WIDTH) / f->zoom + f->offset_x;
	mouse_cy = map(f->mouse_y, -2.0, 2.0, HEIGHT) / f->zoom + f->offset_y;
	f->zoom *= zoom_factor;
	new_cx = map(f->mouse_x, -2.0, 2.0, WIDTH) / f->zoom;
	new_cy = map(f->mouse_y, -2.0, 2.0, HEIGHT) / f->zoom;
	f->offset_x = mouse_cx - new_cx;
	f->offset_y = mouse_cy - new_cy;
}
