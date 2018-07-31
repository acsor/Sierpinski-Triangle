#include "utils.h"

int point_middle(point_t a, point_t b, point_t *dest) {
	if (dest != NULL) {
		dest->x = (a.x + b.x) / 2;
		dest->y = (a.y + b.y) / 2;

		return 0;
	}

	return 1;
}

void cairo_triangle(cairo_t* cr, point_t a, point_t b, point_t c) {
	cairo_move_to(cr, a.x, a.y);
	cairo_line_to(cr, b.x, b.y);
	cairo_move_to(cr, b.x, b.y);
	cairo_line_to(cr, c.x, c.y);
	cairo_move_to(cr, c.x, c.y);
	cairo_line_to(cr, a.x, a.y);

	cairo_stroke(cr);
}

void cairo_sierpinski_triangle(cairo_t *cr, unsigned int depth) {

}
