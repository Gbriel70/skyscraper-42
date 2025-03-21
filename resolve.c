#include "sky.h"

int count_visible_buildings(int line[4], int direction)
{
    int visible = 0;
    int max = 0;
    int i = -1;

    if (direction == 0)
    {
        while (++i < 4)
        {
            if (line[i] > max)
            {
                max = line[i];
                visible++;
            }
        }
    }else
    {
        i = 4;
        while (--i >= 0)
        {
            if (line[i] > max)
            {
                max = line[i];
                visible++;
            }
        }
    }
    return (visible);
}

short check_all_constraints(t_sky *sky)
{
    if (!check_rows_and_cols(sky))
        return (FALSE);
    if (!check_visibility_constraints(sky))
        return (FALSE);
    return (TRUE);
}

short is_valid(t_sky *sky, int row, int col, int num)
{
    short result;
    
    if (!check_duplicate(sky, row, col, num))
        return (FALSE);
    
    sky->tab[row][col] = num;
    
    result = TRUE;
    if (is_row_complete(sky, row))
    {
        if (!check_row_visibility(sky, row))
            result = FALSE;
    }
    
    if (result && is_col_complete(sky, col))
    {
        if (!check_col_visibility(sky, col))
            result = FALSE;
    }
    
    sky->tab[row][col] = 0;
    return (result);
}

void apply_initial_constraints(t_sky *sky)
{
    int i;

    i = -1;
    while (++i < 4)
    {
        if (sky->col_up[i] == 4)
        {
            sky->tab[0][i] = 1;
            sky->tab[1][i] = 2;
            sky->tab[2][i] = 3;
            sky->tab[3][i] = 4;
        }
        if (sky->col_down[i] == 4)
        {
            sky->tab[3][i] = 1;
            sky->tab[2][i] = 2;
            sky->tab[1][i] = 3;
            sky->tab[0][i] = 4;
        }
    }
    i = -1;
    while (++i < 4)
    {
        if (sky->col_up[i] == 1 && sky->tab[0][i] == 0)
            sky->tab[0][i] = 4;
        if (sky->col_down[i] == 1 && sky->tab[3][i] == 0)
            sky->tab[3][i] = 4;
        if (sky->row_left[i] == 1 && sky->tab[i][0] == 0)
            sky->tab[i][0] = 4;
        if (sky->row_right[i] == 1 && sky->tab[i][3] == 0)
            sky->tab[i][3] = 4;
    }
}

short resolve(t_sky *sky, int row, int col)
{
    int next_row;
    int next_col;
    int value;

    if (row == 4)
        return check_all_constraints(sky);       
    if (col == 3) {
        next_row = row + 1;
        next_col = 0;
    } else {
        next_row = row;
        next_col = col + 1;
    }    
    if (sky->tab[row][col] != 0)
        return resolve(sky, next_row, next_col);
    value = 1;
    while (value <= 4)
    {
        if (is_valid(sky, row, col, value))
        {
            sky->tab[row][col] = value;            
            if (resolve(sky, next_row, next_col))
                return (TRUE);                
            sky->tab[row][col] = 0;
        }
        value++;
    }    
    return (FALSE);
}