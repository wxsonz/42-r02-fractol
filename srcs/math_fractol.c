#include "fractol.h"

double	screen_to_world(double screen_coord, double offset, double zoom, double max_dim);

static void	init_complex_vars(t_fractal *f, double x, double y,
	t_complex *z, t_complex *c)
{
	if (f->is_julia)
	{
		c->real = f->c.real;
		c->imag = f->c.imag;
		z->real = screen_to_world(x, f->offset_x, f->zoom, WIDTH);
		z->imag = screen_to_world(y, f->offset_y, f->zoom, HEIGHT);
	}
	else // Mandelbrot
	{
		c->real = screen_to_world(x, f->offset_x, f->zoom, WIDTH);
		c->imag = screen_to_world(y, f->offset_y, f->zoom, HEIGHT);
		z->real = f->z.real;
		z->imag = f->z.imag;
	}
}

// Performs one step of the generalized fractal formula
static void	iterate_z(t_complex *z, t_complex *c, t_fractal *f)
{
	double	new_real;
	double	mag_sq;
	double	log_mag;
	double	angle;
	double	exp_power;

	if (f->power_mag == 2.0 && f->power_ang == 2.0)
	{
		new_real = z->real * z->real - z->imag * z->imag + c->real;
		z->imag = 2 * z->real * z->imag + c->imag;
		z->real = new_real;
	}
	else
	{

		mag_sq = z->real * z->real + z->imag * z->imag;
		log_mag = 0.5 * log(mag_sq);
		angle = atan2(z->imag, z->real) * f->power_ang;
		exp_power = exp(f->power_mag * log_mag);
		new_real = exp_power * cos(angle) + c->real;
		z->imag = exp_power * sin(angle) + c->imag;
		z->real = new_real;
	}
}

// Calculates the escape time for a given point
int	calculate_iterations(t_fractal *f, double x, double y)
{
	t_complex	z;
	t_complex	c;
	int			iter;
	double		mag_sq;

	init_complex_vars(f, x, y, &z, &c);
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
