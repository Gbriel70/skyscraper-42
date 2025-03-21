#ifndef SKY_H
#define SKY_H

#include <stdlib.h>
#include <stdio.h>

//MACROS
#define TRUE 1
#define FALSE 0

typedef struct s_sky
{
    int tab[4][4];
    int col_up[4];
    int col_down[4];
    int row_left[4];
    int row_right[4];
}               t_sky;


//UTILS
int ft_atoi(char *str);
int ft_len(char *str);
void set_tab(t_sky *sky, int *array);

//RESOLVE
int count_visible_buildings(int line[4], int direction);
short check_all_constraints(t_sky *sky);
short is_valid(t_sky *sky, int row, int col, int num);
void apply_initial_constraints(t_sky *sky);
short resolve(t_sky *sky, int row, int col);


//RESOLVE_UTILS
short check_row_uniqueness(int row[4]);
short check_rows_and_cols(t_sky *sky);
short check_visibility_constraints(t_sky *sky);
short check_duplicate(t_sky *sky, int row, int col, int num);
short check_row_visibility(t_sky *sky, int row);
short check_col_visibility(t_sky *sky, int col);
short is_row_complete(t_sky *sky, int row);
short is_col_complete(t_sky *sky, int col);

#endif