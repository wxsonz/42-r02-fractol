#include "fractol.h"

// A simple string comparison function
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

// A simple function to write a string to a file descriptor
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// Helper to process the fractional part of a number for ft_atof
static double	process_fraction(const char *str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (*str >= '0' && *str <= '9')
	{
		fraction = fraction + (*str - '0') / divisor;
		divisor *= 10.0;
		str++;
	}
	return (fraction);
}

// A simplified atof to convert string to double, respecting Norm
double	ft_atof(const char *str)
{
	double	integer_part;
	double	result;
	int		sign;

	integer_part = 0.0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		integer_part = integer_part * 10.0 + (*str - '0');
		str++;
	}
	result = integer_part;
	if (*str == '.')
	{
		str++;
		result = result + process_fraction(str);
	}
	return (result * sign);
}
