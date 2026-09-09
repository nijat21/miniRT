#include <minirt.h>
#include <parser.h>

t_vec parse_vec(char *str)
{
    char **split;
    t_vec v;

    if (!str)
        error("Invalid vector");
    split = ft_split(str, ',');
    if (!split)
        error("Malloc failed");
    if (count_tokens(split) != 3)
    {
        free_split(split, count_tokens(split));
        error("Invalid vector");
    }
    v.x = parse_double(split[0]);
    v.y = parse_double(split[1]);
    v.z = parse_double(split[2]);

    free_split(split, count_tokens(split));
    return (v);
}

// store already nornmalized color ( color / 255)
t_vec parse_color(char *str)
{
    char **split;
    t_vec   c;
    int r;
    int g;
    int b;

    split = ft_split(str, ',');
    if (!split)
        error("Malloc failed");
    if (count_tokens(split) != 3)
    {
        free_split(split, count_tokens(split));
        error("Invalid color");
    }
    r = parse_int(split[0]);
    g = parse_int(split[1]);
    b = parse_int(split[2]);
    if (r < 0 || r > 255
        || g < 0 || g > 255
        || b < 0 || b > 255)
    {
        free_split(split, count_tokens(split));
        error("Color out of range");
    }    
    c.x = (double)r / 255.0;
    c.y = (double)g / 255.0;
    c.z = (double)b / 255.0;
    free_split(split, count_tokens(split));
    return (c);
}

double parse_double(char *str)
{
    double  val;

    if (ft_atof(str, &val) != 0)
        error("Invalid number");
    return (val);
}

int parse_int(char *str)
{
    int i;
    int sign;
    long    val;

    i = 0;
    sign = 1;
    val = 0;
    if (!str || !str[0])
        error("Invalid integer");
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (!str[i])
        error("Invalid integer");
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            error ("Invalid integer");
        val = val * 10 + (str[i] - '0');
        if (val > 2147483647L)
            error("Integer overflow");
        i++;
    }
    return ((int)(val * sign));
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

int ft_atof(const char *str, double *result)
{
    int i;
    int sign;
    int digits;
    int dots;
    double val;
    double decimal;

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
