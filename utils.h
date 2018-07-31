#ifndef UTILS_H
#define UTILS_H

#include <cairo.h>
#include <stdlib.h>

typedef struct {
	double x, y;
} point_t;


/**
 * Computes the middle point between a and b and stores it in dest.
 *
 * Returns:
 * 	0 in case of success
 * 	1 if dest == NULL.
 */
int point_middle(point_t a, point_t b, point_t *dest);
void cairo_triangle(cairo_t*, point_t a, point_t b, point_t c);
/**
 * Draws a Sierpinski triangle with depth depth to cr.
 */
void cairo_sierpinski_triangle(
	cairo_t *cr, point_t a, point_t b, point_t c, int depth
);


#endif // UTILS_H
