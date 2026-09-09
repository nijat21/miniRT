#include <minirt.h>
#include <parser.h>

static int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static int count_words(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i])
        {
            count++;
            while (str[i] && !is_space(str[i]))
                i++;
        }
    }
    return (count);
}

static char *word_dup(char *str, int start, int end)
{
    char *word;
    int i;

    i = 0;
    word = malloc(end - start + 1);
    if (!word)
        return (NULL);
    while (start < end)
        word[i++] = str[start++];
    word[i] = '\0';
    return (word);
}

char **ft_split_spaces(char *str)
{
    char **res;
    int i;
    int j;
    int start;

    i = 0;
    j = 0;
    res = malloc(sizeof(char *) * (count_words(str) + 1));
    if (!res)
        return (NULL);
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (!str[i])
            break;
        start = i;
        while (str[i] && !is_space(str[i]))
            i++;
        res[j++] = word_dup(str, start, i);
    }
    res[j] = NULL;
    printf("SPLIT DEBUG: j = %d\n", j);
    for (int k = 0; k <= j; k++)
        printf("SPLIT DEBUG: res[%d] = [%s] (%p)\n", k, res[k], (void *)res[k]);
    return (res);
}
