#include "fractol.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_fractal	*f;
	int32_t		delta_x;
	int32_t		delta_y;
	double		view_width;
	double		view_height;

	f = (t_fractal *)param;
	if (f->is_dragging)
	{
		f->mouse_x = (int32_t)xpos;
		f->mouse_y = (int32_t)ypos;
		delta_x = f->mouse_x - f->drag_start_x;
		delta_y = f->mouse_y - f->drag_start_y;
		view_width = 4.0 / f->zoom;
		view_height = 4.0 / f->zoom;
		f->offset_x = f->start_offset_x - (delta_x * view_width * PAN_SPEED);
		f->offset_y = f->start_offset_y - (delta_y * view_height * PAN_SPEED);
	}
}

// Hook for mouse scroll wheel (zooming)
void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractal	*f;
	double		zoom_factor;

	(void)xdelta;
	f = (t_fractal *)param;
	if (ydelta > 0)
		zoom_factor = ZOOM_FACTOR_IN;
	else
		zoom_factor = ZOOM_FACTOR_OUT;
	adjust_offsets_for_zoom(f, zoom_factor);
}

// Hook for mouse button presses (panning)
void	mouse_hook(mouse_key_t btn, action_t act, modifier_key_t mod, void *p)
{
	t_fractal	*f;

	(void)mod;
	f = (t_fractal *)p;
	if (btn == MLX_MOUSE_BUTTON_LEFT)
	{
		if (act == MLX_PRESS)
		{
			f->is_dragging = true;
			mlx_get_mouse_pos(f->mlx, &f->drag_start_x, &f->drag_start_y);
			f->start_offset_x = f->offset_x;
			f->start_offset_y = f->offset_y;
		}
		else
			f->is_dragging = false;
	}
}

