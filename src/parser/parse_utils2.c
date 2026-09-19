#include <minirt.h>
#include <parser.h>

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

double	parse_double(char *str, t_scene *scene)
{
	double	val;

	if (ft_atof(str, &val) != 0)
		error(scene, "Invalid number");
	return (val);
}
