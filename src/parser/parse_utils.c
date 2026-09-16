#include <minirt.h>
#include <parser.h>

t_vec	parse_vec(char *str)
{
	char	**split;
	t_vec	v;

	if (!str)
		error("Invalid vector");
	split = ft_split(str, ',');
	if (!split)
		error("Malloc failed");
	if (count_tokens(split) != 3)
	{
		free_split(split, count_tokens(split));
		error("Invalid vector");
	}
	v.x = parse_double(split[0]);
	v.y = parse_double(split[1]);
	v.z = parse_double(split[2]);
	free_split(split, count_tokens(split));
	return (v);
}

t_vec	parse_color(char *str)
{
	char	**split;
	t_vec	c;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split)
		error("Malloc failed");
	if (count_tokens(split) != 3)
	{
		free_split(split, count_tokens(split));
		error("Invalid color");
	}
	r = parse_int(split[0]);
	g = parse_int(split[1]);
	b = parse_int(split[2]);
	if (r < 0 || r > 255
		|| g < 0 || g > 255
		|| b < 0 || b > 255)
	{
		free_split(split, count_tokens(split));
		error("Color out of range");
	}
	c.x = (double)r / 255.0;
	c.y = (double)g / 255.0;
	c.z = (double)b / 255.0;
	free_split(split, count_tokens(split));
	return (c);
}

double	parse_double(char *str)
{
	double	val;

	if (ft_atof(str, &val) != 0)
		error("Invalid number");
	return (val);
}

int	parse_int(char *str)
{
	int		i;
	int		sign;
	long	val;

	i = 0;
	sign = 1;
	val = 0;
	if (!str || !str[0])
		error("Invalid integer");
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		error("Invalid integer");
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error ("Invalid integer");
		val = val * 10 + (str[i] - '0');
		if (val > 2147483647L)
			error("Integer overflow");
		i++;
	}
	return ((int)(val * sign));
}
