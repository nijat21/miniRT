#include <minirt.h>
#include <parser.h>
#include <libft.h>

/*

sq  0,100,40    0,0,1.0     30    0,255,255

tokens[1] center of square
tokens[2] normal vector
tokens[3] side length
tokens[4] color

*/

void	parse_square(char **tokens, t_scene *scene)
{
	t_obj		*obj;
	t_square	*sq;
	t_list		*node;

	if (count_tokens(tokens) != 5)
		error("Invalid square format");
	sq = malloc(sizeof(t_square));
	obj = malloc(sizeof(t_obj));
	if (!sq || !obj)
		error("Malloc failed");
	sq->cors = parse_vec(tokens[1]);
	sq->norm = parse_vec(tokens[2]);
	if (vec_len(sq->norm) == 0)
		error("Square norm cannot be zero");
	sq->norm = normalize(sq->norm);
	sq->side_len = parse_double(tokens[3]);
	// maybe add sp->half_size to make intersection easier in rendering....
	if (sq->side_len <= 0)
		error("Side length must be > 0");
	sq->rgb = parse_color(tokens[4]);
	obj->type = SQUARE;
	obj->data = sq;
	node = ft_lstnew(obj);
	if (!node)
		error("Malloc failed");
	ft_lstadd_back(&scene->objs, node);
}
