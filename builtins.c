#include "minishell.h"

// typedef struct s_data 
// {
//     int exit_status;
//     int last_exit_status;
//     t_list *str;
// }   t_data;
// t_data  g_data;
int    count(char **str)
{
    int    i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int    is_no(char *str)
{
    int    i;

    i = 0;
    if (str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

void    ft_echo(char **str)
{
    int    i;
    int    x;

    i = 1;
    x = 0;
    if (count(str) > 1)
    {
        while (str[i] && str[i][0] && is_no(str[i]) == 0)
        {
            x++;
            i++;
        }
        while (str[i])
        {
            printf("%s", str[i]);
            if (str[i + 1])
                printf(" ");
            i++;
        }
        if (x == 0)
            printf("\n");
    }
    // g_data.exit_status = 0;
}

// void ft_pwd()
// {
//     char str[PATH_MAX];
//     getcwd(str, sizeof(str));
//     printf("%s\n", str);
//     g_data.exit_status = 0;
// }