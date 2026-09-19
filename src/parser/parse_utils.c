#include <minirt.h>
#include <parser.h>

t_vec	parse_vec(char *str, t_scene *scene)
{
	char	**split;
	t_vec	v;

	if (!str)
		error(scene, "Invalid vector");
	split = ft_split(str, ',');
	if (!split)
		error(scene, "Malloc failed");
	if (count_tokens(split) != 3)
	{
		free_split(split, count_tokens(split));
		error(scene, "Invalid vector");
	}
	v.x = parse_double(split[0], scene);
	v.y = parse_double(split[1], scene);
	v.z = parse_double(split[2], scene);
	free_split(split, count_tokens(split));
	return (v);
}

t_vec	parse_color(char *str, t_scene *scene)
{
	char	**split;
	t_vec	c;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split)
		error(scene, "Malloc failed");
	if (count_tokens(split) != 3)
	{
		free_split(split, count_tokens(split));
		error(scene, "Invalid color");
	}
	r = parse_int(split[0], scene);
	g = parse_int(split[1], scene);
	b = parse_int(split[2], scene);
	if (r < 0 || r > 255
		|| g < 0 || g > 255
		|| b < 0 || b > 255)
	{
		free_split(split, count_tokens(split));
		error(scene, "Color out of range");
	}
	c.x = (double)r / 255.0;
	c.y = (double)g / 255.0;
	c.z = (double)b / 255.0;
	free_split(split, count_tokens(split));
	return (c);
}

double	parse_double(char *str, t_scene *scene)
{
	double	val;

	if (ft_atof(str, &val) != 0)
		error(scene, "Invalid number");
	return (val);
}

int	parse_int(char *str, t_scene *scene)
{
	int		i;
	int		sign;
	long	val;

	i = 0;
	sign = 1;
	val = 0;
	if (!str || !str[0])
		error(scene, "Invalid integer");
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		error(scene, "Invalid integer");
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error (scene, "Invalid integer");
		val = val * 10 + (str[i] - '0');
		if (val > 2147483647L)
			error(scene, "Integer overflow");
		i++;
	}
	return ((int)(val * sign));
}

void	add_obj(t_scene *scene, t_obj_type type, void *data)
{
	t_obj	*obj;
	t_list	*node;

	obj = malloc(sizeof(t_obj));
	if (!obj)
	{
		free(data);
		error(scene, "Malloc failed");
	}
	obj->type = type;
	obj->data = data;
	node = ft_lstnew(obj);
	if (!node)
	{
		free(obj);
		free(data);
		error(scene, "Malloc failed");
	}
	ft_lstadd_back(&scene->objs, node);
}
