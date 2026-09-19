#include <minirt.h>
#include <parser.h>

static int	get_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

static int	check_digit(char c, long *val)
{
	if (!ft_isdigit(c))
		return (0);
	*val = *val * 10 + (c - '0');
	if (*val > 2147483647L)
		return (0);
	return (1);
}

int	parse_int(char *str, t_scene *scene)
{
	int		i;
	int		sign;
	long	val;

	i = 0;
	val = 0;
	if (!str || !str[0])
		error(scene, "Invalid integer");
	sign = get_sign(str[i]);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		error(scene, "Invalid integer");
	while (str[i])
	{
		if (!check_digit(str[i], &val))
			error(scene, "Invalid integer");
		i++;
	}
	return ((int)(val * sign));
}
