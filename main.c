#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <cairo.h>
#include "utils.h"


#define DESTFILESIZE 512
#define DEFLINEWIDTH (0.00125)

typedef struct {
	unsigned int width, height;
	float rgba_fg[4], rgba_bg[4];
	float line_width;
	unsigned int depth;

	char destfile[DESTFILESIZE];
} cmd_args;


const char * argp_program_version = "0.5";

static error_t sierpinski_argp_parser(int key, char *arg, struct argp_state *s);


int main (int argc, char *argv[]) {
	cmd_args args = {
		512, 512,
		{1.0, 1.0, 1.0, 1.0}, {0.0, 0.0, 0.0, 1.0},
		0.00125,
		0, "\0"
	};

	static struct argp_option options[] = {
		{"fg", 'f', "<RGBA>", 0, "Background color in RGB format", 1},
		{"bg", 'b', "<RGBA>", 0, "Foreground color in RGB format", 1},
		{"linewidth", 'l', "<0..1>", 0, "Scaling factor of the line width. 0 to 1 float.", 2},
		{"width", 'w', "<int>", 0, "Pixel width of the output image", 2},
		{"height", 'h', "<int>", 0, "Pixel height of the output image", 2},
		{"outputfile", 'o', "<filename>", 0, "Arbitrary output file name"},
		{0}
	};

	static struct argp a = {
		options,
		sierpinski_argp_parser,
		"<Depth level>",
		"Sierpinski triangle generator."
	};

	cairo_t *cr;
	cairo_surface_t *s;

	argp_parse(&a, argc, argv, 0, NULL, (void*) &args);

	s = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32, args.width, args.height
	);
	cr = cairo_create(s);
	cairo_scale(cr, args.width, args.height);

	cairo_set_source_rgba(
		cr, args.rgba_bg[0], args.rgba_bg[1], args.rgba_bg[2], args.rgba_bg[3] 
	); 
	cairo_paint(cr);

	cairo_set_source_rgba(
		cr, args.rgba_fg[0], args.rgba_fg[1], args.rgba_fg[2], args.rgba_fg[3]
	);
	cairo_set_line_width(cr, args.line_width);
	cairo_sierpinski_triangle_auto(cr, args.depth);
	cairo_stroke(cr);
	
	cairo_surface_write_to_png(s, args.destfile);

	cairo_destroy(cr);
	cairo_surface_destroy(s);

	return 0;
}


static error_t sierpinski_argp_parser(int key, char *arg, struct argp_state *s) {
	cmd_args * const a = (cmd_args*) s->input;

	switch (key) {
		// When the single required non-option argument is present
		case ARGP_KEY_ARG:
			a->depth = atoi(arg);
			break;
		case ARGP_KEY_NO_ARGS: // When no non-option argument is present
			argp_error(s, "<Depth level>");
			break;
		case ARGP_KEY_END: // At the end of the parsing process
			if (*a->destfile == '\0') {
				snprintf(
					a->destfile, DESTFILESIZE, "Sierpinski%d.png", a->depth
				);
			}
			break;
		case 'f':
			std_rgba_to_cairo_rgba(arg, a->rgba_fg);
			break;
		case 'b':
			std_rgba_to_cairo_rgba(arg, a->rgba_bg);
			break;
		case 'w':
			a->width = atoi(arg);
			break;
		case 'h':
			a->height = atoi(arg);
			break;
		case 'l':
			a->line_width = DEFLINEWIDTH * atof(arg);
			break;
		case 'o':
			strncpy(a->destfile, arg, DESTFILESIZE);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}
