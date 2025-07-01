#include "fractol.h"

// Sets the default parameters for the fractal state
void	init_fractal(t_fractal *f)
{
	int	i;

	f->mlx = NULL;
	f->img = NULL;
	f->name = "unspecified";
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->c.real = -0.7;
	f->c.imag = 0.27015;
	f->z.real = 0.0;
	f->z.imag = 0.0;
	f->power_mag = 2.0;
	f->power_ang = 2.0;
	f->iter_max = 128;
	f->is_julia = false;
	f->quality_level = 0;
	f->view_changed = true;
	i = 0;
	while (i < 10)
	{
		f->last_params[i] = 0.0;
		i++;
	}
}

// Initializes MLX42, creates the window and the main image buffer
void	init_mlx(t_fractal *f)
{
	f->mlx = mlx_init(WIDTH, HEIGHT, f->name, true);
	if (!f->mlx)
		cleanup_and_exit(f, EXIT_FAILURE);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		cleanup_and_exit(f, EXIT_FAILURE);
	if (mlx_image_to_window(f->mlx, f->img, 0, 0) < 0)
		cleanup_and_exit(f, EXIT_FAILURE);
}

// Registers all MLX42 hooks for user interaction
void	register_hooks(t_fractal *f)
{
	mlx_loop_hook(f->mlx, render, f);
	mlx_loop_hook(f->mlx, key_hook, f);
	mlx_scroll_hook(f->mlx, scroll_hook, f);
	mlx_mouse_hook(f->mlx, mouse_hook, f);
}
