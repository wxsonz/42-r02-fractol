#include "fractol.h"

// Initializes the Z and C complex numbers based on fractal type
static void	init_complex_vars(t_fractal *f, double x, double y,
	t_complex *z, t_complex *c)
{
	if (f->is_julia)
	{
		c->real = f->c.real;
		c->imag = f->c.imag;
		z->real = map(x, -2.0, 2.0, WIDTH) + f->offset_x;
		z->imag = map(y, -2.0, 2.0, HEIGHT) + f->offset_y;
	}
	else
	{
		c->real = map(x, -2.0, 2.0, WIDTH) + f->offset_x;
		c->imag = map(y, -2.0, 2.0, HEIGHT) + f->offset_y;
		z->real = f->z.real;
		z->imag = f->z.imag;
	}
}

// Performs one step of the generalized fractal formula
static void	iterate_z(t_complex *z, t_complex *c, t_fractal *f)
{
	double	mag_sq;
	double	log_mag;
	double	angle;
	double	exp_power;
	double	new_real;

	mag_sq = z->real * z->real + z->imag * z->imag;
	log_mag = 0.5 * log(mag_sq);
	angle = atan2(z->imag, z->real) * f->power_ang;
	exp_power = exp(f->power_mag * log_mag);
	new_real = exp_power * cos(angle) + c->real;
	z->imag = exp_power * sin(angle) + c->imag;
	z->real = new_real;
}

// Calculates the escape time for a given point
int	calculate_iterations(t_fractal *f, double x, double y)
{
	t_complex	z;
	t_complex	c;
	int			iter;
	double		mag_sq;

	init_complex_vars(f, x / f->zoom, y / f->zoom, &z, &c);
	iter = 0;
	while (iter < f->iter_max)
	{
		mag_sq = z.real * z.real + z.imag * z.imag;
		if (mag_sq > 4.0)
			return (iter);
		iterate_z(&z, &c, f);
		iter++;
	}
	return (iter);
}
