/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:44 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:37:47 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

// parser
void	parse_ambient(char **tokens, t_scene *scene);
void	parse_camera(char **tokens, t_scene *scene);
void	parse_cylinder(char **tokens, t_scene *scene);
void	parse_light(char **tokens, t_scene *scene);
void	parse_plane(char **tokens, t_scene *scene);
void	parse_sphere(char **tokens, t_scene *scene);
char	**ft_split_spaces(char *str);
t_vec	parse_vec(char *str, t_scene *scene);
t_vec	parse_color(char *str, t_scene *scene);
double	parse_double(char *str, t_scene *scene);
int		parse_int(char *str, t_scene *scene);
void	add_obj(t_scene *scene, t_obj_type type, void *data);
void	error(t_scene *scene, char *msg);
int		count_tokens(char **tokens);
int		parse_scene(char *filename, t_scene *scene);
int		ft_atof(const char *str, double *result);
void	*free_split(char **strs, int count);
void	parse_line(char *line, t_scene *scene);
void	free_obj(void *content);
void	clean_scene(t_scene *scene);
void	init_scene(t_scene *scene);
void	validate_scene(t_scene *scene);

#endif // PARSER_H
