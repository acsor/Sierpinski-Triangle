#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <cairo.h>
#include <cairo-svg.h>
#include "utils.h"


#define DESTFILESIZE 512
#define DEFLINEWIDTH (0.00125)

#define OPT_FORMAT_PNG "png"
#define OPT_FORMAT_SVG "svg"

typedef enum {
	PNG = 0,
	SVG
} output_format;

typedef struct {
	unsigned int width, height;
	float rgba_fg[4], rgba_bg[4];
	float line_width;
	unsigned int depth;

	output_format format;
	char destfile[DESTFILESIZE];
} cmd_args;


const char * argp_program_version = "0.5";

static error_t sierpinski_argp_parser(int key, char *arg, struct argp_state *s);


int main (int argc, char *argv[]) {
	cmd_args args = {
		512, 512,
		{1.0, 1.0, 1.0, 1.0}, {0.0, 0.0, 0.0, 1.0},
		0.00125,
		0, PNG, "\0"
	};

	static struct argp_option options[] = {
		{"fg", 'f', "<#RGBA>", 0, "Background color in RGBA format", 1},
		{"bg", 'b', "<#RGBA>", 0, "Foreground color in RGBA format", 1},
		{"linewidth", 'l', "<0..1>", 0, "Scaling factor of the line width. 0 to 1 float", 2},
		{"width", 'w', "<int>", 0, "Width of the output image, in pixels if PNG or points if SVG", 2},
		{"height", 'h', "<int>", 0, "Height of the output image, in pixels if PNG or points if SVG", 2},
		{"format", 'F', "<[png|svg]>", 0, "Output file format", 3},
		{"outputfile", 'o', "<filename>", 0, "Arbitrary output file name", 3},
		{0}
	};

	static struct argp a = {
		options,
		sierpinski_argp_parser,
		"<Depth level>",
		"Sierpinski triangle generator."
	};

	cairo_t *cr;
	cairo_surface_t *s = NULL;

	argp_parse(&a, argc, argv, 0, NULL, (void*) &args);

	if (args.format == PNG) {
		s = cairo_image_surface_create(
			CAIRO_FORMAT_ARGB32, args.width, args.height
		);
	} else if (args.format == SVG) {
		// TO-DO Can a more careful conversion of the width and height
		// parameters be done with regard to the point unit? (I guess no.)
		s = cairo_svg_surface_create(args.destfile, args.width, args.height);
	}

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
				if (a->format == PNG) {
					snprintf(
						a->destfile, DESTFILESIZE,
						"Sierpinski%d.png", a->depth
					);
				} else if (a->format == SVG) {
					snprintf(
						a->destfile, DESTFILESIZE,
						"Sierpinski%d.svg", a->depth
					);
				}
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
		case 'F':
			if (!strcmp(arg, OPT_FORMAT_PNG)) {
				a->format = PNG;
			} else if (!strcmp(arg, OPT_FORMAT_SVG)) {
				a->format = SVG;
			} else {
				argp_error(s, "-F <[png|svg]>");
			}
			break;
		case 'o':
			strncpy(a->destfile, arg, DESTFILESIZE);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}
