#include <minirt.h>
#include <parser.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	ft_atof(const char *str, double *result)
{
	int		i;
	int		sign;
	int		digits;
	int		dots;
	double	val;
	double	decimal;

	i = 0;
	sign = 1;
	digits = 0;
	dots = 0;
	val = 0.0;
	decimal = 0.1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			digits++;
			if (dots == 0)
				val = val * 10.0 + (str[i] - '0');
			else
			{
				val += (str[i] - '0') * decimal;
				decimal *= 0.1;
			}
		}
		else if (str[i] == '.')
		{
			dots++;
			if (dots > 1)
				return (1);
		}
		else
			return (1);
		i++;
	}
	if (digits == 0)
		return (1);
	*result = val * sign;
	return (0);
}

void	*free_split(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

void	error(t_scene *scene, char *msg)
{
	if (scene)
		clean_scene(scene);
	printf("Error\n%s\n", msg);
	exit(1);
}

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
