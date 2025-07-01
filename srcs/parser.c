#include "fractol.h"

// Prints the usage message to standard output
static void	print_usage(void)
{
	ft_putstr_fd("Usage:./fractol <fractal_name>\n\n", 1);
	ft_putstr_fd("Available fractals:\n", 1);
	ft_putstr_fd("  - mandelbrot\n", 1);
	ft_putstr_fd("  - julia <real_const> <imag_const>\n\n", 1);
	ft_putstr_fd("Example:\n", 1);
	ft_putstr_fd(" ./fractol julia -0.7 0.27015\n", 1);
}

// Parses arguments for the Julia set
static int	parse_julia_args(int argc, char **argv, t_fractal *f)
{
	if (argc != 4)
	{
		print_usage();
		return (ERROR);
	}
	f->name = "julia";
	f->is_julia = true;
	f->c.real = ft_atof(argv[2]);  // Fixed: Use argv[2] and argv[3]
	f->c.imag = ft_atof(argv[3]);
	return (SUCCESS);
}

// Main parsing function to be called from main
int	parse_args(int argc, char **argv, t_fractal *f)
{
	if (argc < 2)
	{
		print_usage();
		return (ERROR);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0)  // Fixed: Check argv[1] instead of argv[3]
	{
		if (argc != 2)
		{
			print_usage();
			return (ERROR);
		}
		f->name = "mandelbrot";
		f->is_julia = false;
		return (SUCCESS);
	}
	else if (ft_strcmp(argv[1], "julia") == 0)  // Fixed: Check argv[1] instead of argv[3]
		return (parse_julia_args(argc, argv, f));
	else
	{
		print_usage();
		return (ERROR);
	}
}
