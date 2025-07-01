#include "fractol.h"

// Handles panning when the mouse is being dragged
static void	handle_panning(t_fractal *f)
{
	int32_t	delta_x;
	int32_t	delta_y;
	double	view_width;
	double	view_height;

	if (f->is_dragging)
	{
		mlx_get_mouse_pos(f->mlx, &f->mouse_x, &f->mouse_y);
		delta_x = f->mouse_x - f->drag_start_x;
		delta_y = f->mouse_y - f->drag_start_y;
		view_width = 4.0 / f->zoom;
		view_height = 4.0 / f->zoom;
		f->offset_x = f->start_offset_x - (delta_x * view_width * PAN_SPEED);
		f->offset_y = f->start_offset_y - (delta_y * view_height * PAN_SPEED);
	}
}

// Handles keyboard controls for adjusting fractal parameters
static void	handle_param_adjust(t_fractal *f)
{
	if (mlx_is_key_down(f->mlx, MLX_KEY_W))
		f->c.imag += KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_S))
		f->c.imag -= KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_D))
		f->c.real += KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_A))
		f->c.real -= KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_Q))
		f->power_mag -= KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_E))
		f->power_mag += KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_Z))
		f->power_ang -= KEY_STEP;
	if (mlx_is_key_down(f->mlx, MLX_KEY_C))
		f->power_ang += KEY_STEP;
}

// Handles keyboard controls for adjusting iteration count
static void	handle_iter_adjust(t_fractal *f)
{
	if (mlx_is_key_down(f->mlx, MLX_KEY_P))
		f->iter_max += 1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_O))
		if (f->iter_max > 1)
			f->iter_max -= 1;
	if (mlx_is_key_down(f->mlx, MLX_KEY_PAGE_UP))
		f->iter_max += 64;
	if (mlx_is_key_down(f->mlx, MLX_KEY_PAGE_DOWN))
		if (f->iter_max > 64)
			f->iter_max -= 64;
}

// Main keyboard hook, called every frame
void	key_hook(void *param)
{
	t_fractal	*f;

	f = (t_fractal *)param;
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit(f, EXIT_SUCCESS);
	if (mlx_is_key_down(f->mlx, MLX_KEY_F))
		f->is_julia = false;
	if (mlx_is_key_down(f->mlx, MLX_KEY_G))
		f->is_julia = true;
	handle_panning(f);
	handle_param_adjust(f);
	handle_iter_adjust(f);
}
