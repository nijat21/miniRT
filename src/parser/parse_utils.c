#include <minirt.h>
#include <parser.h>

t_vec parse_vec(char *str)
{
    char **split;
    t_vec v;

    if (!str)
        error("parse_vec: NULL input");
    split = ft_split(str, ',');
    if (!split || count_tokens(split) != 3)
        error("Invalid vec");
    v.x = ft_atof(split[0]);
    v.y = ft_atof(split[1]);
    v.z = ft_atof(split[2]);

    free_split(split, count_tokens(split));
    return (v);
}

// store already nornmalized color ( color / 255)
t_rgb parse_color(char *str)
{
    char **split;
    t_rgb c;

    split = ft_split(str, ',');
    if (count_tokens(split) != 3)
        error("Invalid color");

    c.r = ft_atof(split[0]) / 255.0;
    c.g = ft_atof(split[1]) / 255.0;
    c.b = ft_atof(split[2]) / 255.0;

    if (c.r < 0 || c.r > 1 || c.g < 0 || c.g > 1 || c.b < 0 || c.b > 1)
        error("Color out of range");

    free_split(split, count_tokens(split));
    return (c);
}

double parse_double(char *str)
{
    return (ft_atof(str));
}

void error(char *msg)
{
    printf("Error\n%s\n", msg);
    exit(1);
}

int count_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
        i++;
    return (i);
}

static int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}

double ft_atof(char *str)
{
    int i;
    int sign;
    double result;
    double decimal;

    i = 0;
    sign = 1;
    result = 0.0;
    decimal = 0.1;
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] && ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        while (str[i] && ft_isdigit(str[i]))
        {
            result += (str[i] - '0') * decimal;
            decimal *= 0.1;
            i++;
        }
    }
    return (result * sign);
}

void *free_split(char **strs, int count)
{
    int i = 0;

    while (i < count)
    {
        free(strs[i]);
        i++;
    }
    free(strs);
    return (NULL);
}
