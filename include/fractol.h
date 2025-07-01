#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h> // For write in ft_putstr_fd

// Return values
# define SUCCESS 0
# define ERROR 1

// Window and Rendering settings
# define WIDTH 1024
# define HEIGHT 1024
# define MAX_ITER 1024

// Control sensitivity
# define KEY_STEP 0.05
# define PAN_SPEED 0.01
# define ZOOM_FACTOR_IN 1.1
# define ZOOM_FACTOR_OUT 0.9

// A simple struct for complex numbers to improve readability
typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

// Main data structure for the fractal state
typedef struct s_fractal
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			*name;

	// View parameters
	double			zoom;
	double			offset_x;
	double			offset_y;

	// Fractal parameters
	bool			is_julia;
	t_complex		c;
	t_complex		z;
	double			power_mag;
	double			power_ang;
	int				iter_max;

	// Mouse and interaction state
	int32_t			mouse_x;
	int32_t			mouse_y;
	bool			is_dragging;
	int32_t			drag_start_x;
	int32_t			drag_start_y;
	double			start_offset_x;
	double			start_offset_y;

	// Adaptive rendering state
	int				quality_level;
	double			last_params[10];
	bool			view_changed;

}	t_fractal;

// --- Function Prototypes ---

// main.c
void		cleanup_and_exit(t_fractal *f, int status);

// parser.c
int			parse_args(int argc, char **argv, t_fractal *f);

// init.c
void		init_fractal(t_fractal *f);
void		init_mlx(t_fractal *f);
void		register_hooks(t_fractal *f);

// render.c
void		render(void *param);

// math_fractal.c
int			calculate_iterations(t_fractal *f, double x, double y);

// math_zoom.c
double		map(double val, double n_min, double n_max, double o_max);
void		adjust_offsets_for_zoom(t_fractal *f, double zoom_factor);

// color.c
uint32_t	get_color(int value, int max_value);

// events_mouse.c
void		scroll_hook(double xdelta, double ydelta, void *param);
void		mouse_hook(mouse_key_t btn,
				action_t act, modifier_key_t mod, void *p);

// events_keyboard.c
void		key_hook(void *param);

// utils.c
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putstr_fd(char *s, int fd);
double		ft_atof(const char *str);

#endif
