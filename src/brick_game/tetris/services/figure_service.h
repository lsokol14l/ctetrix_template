#ifndef __FIGURE_SERVICE_H__
#define __FIGURE_SERVICE_H__

#include "entities/figure.h"

void rotate_figure(figure_t *figure);
void rotate_float_figure(figure_t *figure);

void move_figure(int offset_x, int offset_y, figure_t *figure);
void move_figure_to_abs_coordinate(int x, int y, figure_t *figure);

void fill_figure_from_string(figure_t *figure, const char *str);
void copy_figure(const figure_t *src, figure_t *dst);
void generate_figure(figure_t *figure);

int get_offset_for_inscribed_horizontal_coord(int start_coord, int end_coord,
                                              const figure_t *figure);
int get_offset_for_inscribed_coord(int start_coord, int end_coord,
                                   int coord_index, const figure_t *figure);
int get_offset_for_inscribed_horizontal_coord(int start_coord, int end_coord,
                                              const figure_t *figure);
int get_offset_for_inscribed_vertical_coord(int start_coord, int end_coord,
                                            const figure_t *figure);

#endif  // __FIGURE_SERVICE_H__
