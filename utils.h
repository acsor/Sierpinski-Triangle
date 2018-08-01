#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <ctype.h>


#define ASSERT_MSG(expression, msg, code)\
	if (!(expression)) {\
		fprintf(stderr, "Assertion error at %s:%d: %s\n", __FILE__, __LINE__, (msg));\
		exit(code);\
	}

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
/**
 * Converts the standard RGBA format #AABBCCDD to Cairo's format in float
 * values, such that 0 <= f <= 1 for every float number f representing a
 * channel value.
 *
 * Returns:
 * 	0 on success;
 * 	1 if rgbain is an invalid string
 */
int std_rgba_to_cairo_rgba(char *rgbain, float rgbaout[]);
void cairo_triangle(cairo_t*, point_t a, point_t b, point_t c);
/**
 * Draws a Sierpinski triangle with depth depth to cr.
 */
void cairo_sierpinski_triangle(
	cairo_t *cr, point_t a, point_t b, point_t c, int depth
);
/**
 * Automates the process of picking arbitrary points a, b and c choosing
 * them at aesthetically pleasing coordinates.
 */
void cairo_sierpinski_triangle_auto(cairo_t *cr, int depth);


#endif // UTILS_H
