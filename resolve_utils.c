#include "sky.h"

short check_row_uniqueness(int row[4])
{
    int nums[5];
    int i;
    
    i = 0;
    while (i < 5)
        nums[i++] = 0;
    i = 0;
    while (i < 4)
        nums[row[i++]]++;
    i = 1;
    while (i <= 4)
    {
        if (nums[i] != 1)
            return (FALSE);
        i++;
    }
    return (TRUE);
}

short check_rows_and_cols(t_sky *sky)
{
    int i;
    int j;
    int row[4];
    int col[4];
    
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            row[j] = sky->tab[i][j];
            col[j] = sky->tab[j][i];
            j++;
        }
        if (!check_row_uniqueness(row) || !check_row_uniqueness(col))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

short check_visibility_constraints(t_sky *sky)
{
    int i;
    int j;
    int row[4];
    int col[4];
    
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            row[j] = sky->tab[i][j];
            col[j] = sky->tab[j][i];
            j++;
        }
        if (count_visible_buildings(row, 0) != sky->row_left[i])
            return (FALSE);
        if (count_visible_buildings(row, 1) != sky->row_right[i])
            return (FALSE);
        if (count_visible_buildings(col, 0) != sky->col_up[i])
            return (FALSE);
        if (count_visible_buildings(col, 1) != sky->col_down[i])
            return (FALSE);
        i++;
    }
    return (TRUE);
}

short check_duplicate(t_sky *sky, int row, int col, int num)
{
    int i;
    
    i = -1;
    while (++i < 4)
    {
        if (sky->tab[row][i] == num)
            return (FALSE);
        if (sky->tab[i][col] == num)
            return (FALSE);
    }
    return (TRUE);
}

short check_row_visibility(t_sky *sky, int row)
{
    int tmp_row[4];
    int i;
    int visible_left;
    int visible_right;
    
    i = -1;
    while (++i < 4)
        tmp_row[i] = sky->tab[row][i];
    
    visible_left = count_visible_buildings(tmp_row, 0);
    visible_right = count_visible_buildings(tmp_row, 1);
    
    if (visible_left != sky->row_left[row] || visible_right != sky->row_right[row])
        return (FALSE);
    return (TRUE);
}

short check_col_visibility(t_sky *sky, int col)
{
    int tmp_col[4];
    int i;
    int visible_up;
    int visible_down;
    
    i = -1;
    while (++i < 4)
        tmp_col[i] = sky->tab[i][col];
    
    visible_up = count_visible_buildings(tmp_col, 0);
    visible_down = count_visible_buildings(tmp_col, 1);
    
    if (visible_up != sky->col_up[col] || visible_down != sky->col_down[col])
        return (FALSE);
    return (TRUE);
}

short is_row_complete(t_sky *sky, int row)
{
    int i;
    
    i = -1;
    while (++i < 4)
    {
        if (sky->tab[row][i] == 0)
            return (FALSE);
    }
    return (TRUE);
}

short is_col_complete(t_sky *sky, int col)
{
    int i;
    
    i = -1;
    while (++i < 4)
    {
        if (sky->tab[i][col] == 0)
            return (FALSE);
    }
    return (TRUE);
}