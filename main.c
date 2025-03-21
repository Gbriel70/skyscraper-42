#include "sky.h"

void print_solution(t_sky *sky)
{
    int i = -1;
    int j;

    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            printf("%d", sky->tab[i][j]);
            if (j != 3)
                printf(" ");
        }
        printf("\n");
    }
}

int  *process(char *av)
{
    int i = 0;
    int index = 0;
    int len = ft_len(av);
    int *processed = malloc(sizeof(int) * (len + 1)); 

    if (!processed)
        return (NULL);

    while (av[i])
    {
        if (av[i] >= '0' && av[i] <= '4')
        {
            processed[index] = ft_atoi(&av[i]);
            index++;
        }
        i++;
    }
    if (index != 16)
    {
        free(processed);
        return (NULL);
    }
    return (processed);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Error\n");
        return (1);
    }
    int *array = process(av[1]);
    if (!array)
    {
        printf("Error\n");
        return (0);
    }
    t_sky sky;
    set_tab(&sky, array);
    apply_initial_constraints(&sky);
    if (resolve(&sky, 0, 0) == TRUE)
        print_solution(&sky);
    else
        printf("Não foi possível encontrar solução\n");
    free(array);
    return (0);
}
