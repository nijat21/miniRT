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

static void	check_color_range(int r, int g, int b, t_scene *scene)
{
	if (r < 0 || r > 255 || g < 0 || g > 255
		|| b < 0 || b > 255)
		error(scene, "Color out of range");
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
	check_color_range(r, g, b, scene);
	c.x = (double)r / 255.0;
	c.y = (double)g / 255.0;
	c.z = (double)b / 255.0;
	free_split(split, count_tokens(split));
	return (c);
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
