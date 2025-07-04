#include "fractol.h"

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
	handle_param_adjust(f);
	handle_iter_adjust(f);
}
