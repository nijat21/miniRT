/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:26:44 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:27:41 by abraz-ab         ###   ########.fr       */
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
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_cylinder(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene);
int		parse_plane(char **tokens, t_scene *scene);
int		parse_sphere(char **tokens, t_scene *scene);
int		check_cylinder_norm(t_vec norm, t_scene *scene);
int		parse_cylinder_vectors(char **tokens, t_cyl *cy, t_scene *scene);
int		parse_cylinder_size(char **tokens, t_cyl *cy, t_scene *scene);
int		is_space(char c);
int		count_words(char *str);
char	*word_dup(char *str, int start, int end);
char	**ft_split_spaces(char *str);
int		parse_vec(char *str, t_vec *result, t_scene *scene);
int		parse_color(char *str, t_vec *result, t_scene *scene);
int		parse_double(char *str, double *result);
int		parse_int(char *str, int *result);
void	add_obj(t_scene *scene, t_obj_type type, void *data);
void	error(t_scene *scene, char *msg);
int		count_tokens(char **tokens);
int		parse_scene(char *filename, t_scene *scene);
int		ft_atof(const char *str, double *result);
void	*free_split(char **strs, int count);
int		parse_line(char *line, t_scene *scene);
void	free_obj(void *content);
void	clean_scene(t_scene *scene);
void	init_scene(t_scene *scene);
void	validate_scene(t_scene *scene);

#endif // PARSER_H
