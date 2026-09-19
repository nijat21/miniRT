#include <minirt.h>
#include <parser.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	parse_atof_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

static int	parse_atof_integer_part(const char *str, int *i, double *val)
{
	int	digits;

	digits = 0;
	while (ft_isdigit(str[*i]))
	{
		*val = *val * 10.0 + (str[*i] - '0');
		(*i)++;
		digits++;
	}
	return (digits);
}

static int	parse_atof_decimal_part(const char *str, int *i, double *val)
{
	int	digits;
	double	decimal;

	digits = 0;
	decimal = 0.1;
	if (str[*i] != '.')
		return (0);
	(*i)++;
	while (ft_isdigit(str[*i]))
	{
		*val += (str[*i] - '0') * decimal;
		decimal *= 0.1;
		(*i)++;
		digits++;
	}
	if (str[*i] == '.')
		return (-1);
	return (digits);
}

int	ft_atof(const char *str, double *result)
{
	int		i;
	int		sign;
	int		digits;
	int		decimal_digits;
	double	val;

	i = 0;
	val = 0.0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	sign = parse_atof_sign(str, &i);
	digits = parse_atof_integer_part(str, &i, &val);
	decimal_digits = parse_atof_decimal_part(str, &i, &val);
	if (decimal_digits < 0 || (!digits && !decimal_digits) || str[i])
		return (1);
	*result = val * sign;
	return (0);
}
