#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>

int main (int argc, char *argv[]) {
	const unsigned int width = 512, height = 512;
	cairo_t *cr;
	cairo_surface_t *surface;
	
	if (argc < 2) {
		printf("%s: <image filename>\n", argv[0]);
		exit(1);
	}

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);
	cairo_scale(cr, width, height);

	cairo_set_source_rgb(cr, 256, 256, 256);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 0.0025);
	cairo_move_to(cr, 1.0 / 2, 1.0 / 5);
	cairo_line_to(cr, 5.0 / 6, 4.0 / 5);
	cairo_move_to(cr, 5.0 / 6, 4.0 / 5);
	cairo_line_to(cr, 1.0 / 6, 4.0 / 5);
	cairo_move_to(cr, 1.0 / 6, 4.0 / 5);
	cairo_line_to(cr, 1.0 / 2, 1.0 / 5);
	cairo_stroke(cr);

	cairo_surface_write_to_png(surface, argv[1]);

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}
