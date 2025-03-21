#include "sky.h"

int ft_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    int res = 0;

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * sign);
}

int ft_len(char *str)
{
    int i = -1;
    while (str[++i]);
    return (i);
}

void set_tab(t_sky *sky, int *array)
{
    int i = -1;
    int j;

    while (++i < 4)
    {
        sky->col_up[i] = array[i];
        sky->col_down[i] = array[i + 4];
        sky->row_left[i] = array[i + 8];
        sky->row_right[i] = array[i + 12];
    }
    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            sky->tab[i][j] = 0;
    }
}
