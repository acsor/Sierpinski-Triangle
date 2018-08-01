#include "utils.h"

static void cairo_sierpinski_triangle_rec(
	cairo_t *cr, point_t a, point_t b, point_t c, int depth
);

int point_middle(point_t a, point_t b, point_t *dest) {
	if (dest != NULL) {
		dest->x = (a.x + b.x) / 2;
		dest->y = (a.y + b.y) / 2;

		return 0;
	}

	return 1;
}

int std_rgba_to_cairo_rgba(char *rgbain, float rgbaout[]) {
	int i;
	size_t insize = strlen(rgbain);
	char temp[2];

	if (insize != 9 || rgbain[0] != '#') {
		return 1;
	}

	for (i = 1; i < insize; i++) {
		if (!isxdigit(rgbain[i])) {
			return 1;
		}
	}

	for (i = 1; i < insize; i += 2) {
		temp[0] = rgbain[i];
		temp[1] = rgbain[i + 1];
		rgbaout[(i - 1) / 2] = (float) strtol(temp, NULL, 16) / 255;
	}

	return 0;
}

void cairo_triangle(cairo_t* cr, point_t a, point_t b, point_t c) {
	cairo_move_to(cr, a.x, a.y);
	cairo_line_to(cr, b.x, b.y);
	cairo_move_to(cr, b.x, b.y);
	cairo_line_to(cr, c.x, c.y);
	cairo_move_to(cr, c.x, c.y);
	cairo_line_to(cr, a.x, a.y);
}

void cairo_sierpinski_triangle(
	cairo_t *cr, point_t a, point_t b, point_t c, int depth
) {
	point_t ma, mb, mc;

	if (depth < 1) {
		return;
	}

	// Compute the middle points of a, b and c which will act as coordinates
	// for the internal splitting triangle
	point_middle(c, a, &ma);
	point_middle(a, b, &mb);
	point_middle(b, c, &mc);

	cairo_triangle(cr, a, b, c);

	if (depth > 1) {
		cairo_sierpinski_triangle(cr, ma, mb, mc, 1);
	}

	if (depth > 2) {
		cairo_sierpinski_triangle_rec(cr, ma, a, mb, depth - 2);
		cairo_sierpinski_triangle_rec(cr, mc, mb, b, depth - 2);
		cairo_sierpinski_triangle_rec(cr, c, ma, mc, depth - 2);
	}
}

static void cairo_sierpinski_triangle_rec(
	cairo_t *cr, point_t a, point_t b, point_t c, int depth
) {
	point_t ma, mb, mc;

	// Compute the middle points of a, b and c which will act as coordinates
	// for the internal splitting triangle
	point_middle(c, a, &ma);
	point_middle(a, b, &mb);
	point_middle(b, c, &mc);

	cairo_triangle(cr, ma, mb, mc);

	if (depth > 0) {
		cairo_sierpinski_triangle_rec(cr, ma, a, mb, depth - 1);
		cairo_sierpinski_triangle_rec(cr, mc, mb, b, depth - 1);
		cairo_sierpinski_triangle_rec(cr, c, ma, mc, depth - 1);
	}
}

void cairo_sierpinski_triangle_auto(cairo_t *cr, int depth) {
	point_t a = {1.0 / 2, 1.0 / 5}, b = {5.0 / 6, 4.0 / 5},
			c = {1.0 / 6, 4.0 / 5};

	cairo_sierpinski_triangle(cr, a, b, c, depth);
}
