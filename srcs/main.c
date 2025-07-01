#include "fractol.h"

void	cleanup_and_exit(t_fractal *f, int status)
{
	if (f->mlx)
		mlx_terminate(f->mlx);
	exit(status);
}

int	main(int argc, char **argv)
{
	t_fractal	f;

	init_fractal(&f);
	if (parse_args(argc, argv, &f) == ERROR)
		return (EXIT_FAILURE);
	init_mlx(&f);
	register_hooks(&f);
	mlx_loop(f.mlx);
	cleanup_and_exit(&f, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
