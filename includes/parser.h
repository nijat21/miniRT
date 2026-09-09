#ifndef PARSER_H
#define PARSER_H

#define WIDTH 1600
#define HEIGHT 800
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xffd43b
#define RAYS_NUMBER 100

#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

//
#include <minirt.h>

// parser
void parse_ambient(char **tokens, t_scene *scene);
void parse_camera(char **tokens, t_scene *scene);
void parse_cylinder(char **tokens, t_scene *scene);
void parse_light(char **tokens, t_scene *scene);
void parse_plane(char **tokens, t_scene *scene);
void parse_resolution(char **tokens, t_scene *scene);
void parse_sphere(char **tokens, t_scene *scene);
char **ft_split_spaces(char *str);
void parse_square(char **tokens, t_scene *scene);
t_vec parse_vec(char *str);
t_vec parse_color(char *str);
double parse_double(char *str);\
int parse_int(char *str);
void error(char *msg);
int count_tokens(char **tokens);
int parse_scene(char *filename, t_scene *scene);
int ft_atof(const char *str, double *result);
void *free_split(char **strs, int count);
void parse_line(char *line, t_scene *scene);

#endif // PARSER_H
