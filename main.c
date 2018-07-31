#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include "utils.h"


int main (int argc, char *argv[]) {
	unsigned int width = 512, height = 512;
	float color[] = {75.0 / 256, 69.0 / 256, 209.0 / 256};
	unsigned int depth;
	char destfile[256];

	cairo_t *cr;
	cairo_surface_t *s;

	if (argc < 2) {
		printf("%s: <depth level>\n", argv[0]);
		exit(1);
	}

	depth = atoi(argv[1]);
	snprintf(destfile, 256, "Sierpinski%d.png", depth);

	s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(s);
	cairo_scale(cr, width, height);

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, color[0], color[1], color[2]);
	cairo_set_line_width(cr, 0.0025);
	cairo_sierpinski_triangle_auto(cr, depth);
	cairo_stroke(cr);
	
	cairo_surface_write_to_png(s, destfile);

	cairo_destroy(cr);
	cairo_surface_destroy(s);

	return 0;
}
