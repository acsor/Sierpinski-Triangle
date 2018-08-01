/**
 * scratch.c is intended to experiment with features of libraries to learn and
 * experiment with other code, not to do unit tests on it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cairo.h>
#include "utils.h"


typedef int (*test_ptr)(void*);

int test_cairo_primitives(void *args);
int test_cairo_triangle(void *args);
int test_cairo_sierpinski_triangle(void *args);
int test_uncategorized(void *args);

int main (int argc, char *argv[]) {
	test_ptr functions[] = {
		test_cairo_primitives, test_cairo_triangle,
		test_cairo_sierpinski_triangle, test_uncategorized
	};
	char *function_names[] = {
		"test_cairo_primitives", "test_cairo_triangle",
		"cairo_sierpinski_triangle", "test_uncategorized"
	};
	void *function_args[] = {
		(void*) argv[1], (void*) argv[1], (void*) argv[1]
	};
	unsigned int functions_no = sizeof(functions) / sizeof(test_ptr);
	int i, choice, exit_status;

	printf(
		"Which primitive do you want to test? [%d - %d]\n",
		0, functions_no - 1
	);

	for (i = 0; i < functions_no; i++) {
		printf("\t[%d] %s()\n", i, function_names[i]);
	}

	scanf("%d", &choice);

	while (choice < 0 || choice >= functions_no) {
		printf("It must be 0 <= choice < functions_no (choice = %d)\n", choice);
		scanf("%d", &choice);
	}

	exit_status = functions[choice](function_args[choice]);

	printf(
		"%s() exited with status %d\n", function_names[choice], exit_status
	);

	return exit_status;
}


int test_cairo_primitives(void *args) {
	char *filename = (char*) args;
	const unsigned int width = 512, height = 512;
	cairo_t *cr;
	cairo_surface_t *surface;
	
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

	cairo_surface_write_to_png(surface, filename);

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}

int test_cairo_triangle(void *args) {
	const char *filename = (char*) args;
	const unsigned int width = 512, height = 512;
	point_t a = {1.0 / 6, 1.0 / 5}, b = {5.0 / 6, 1.0 / 5},
			c = {1.0 / 2, 4.0 / 5.0};
	cairo_t *cr;
	cairo_surface_t *surface;
	
	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);
	cairo_scale(cr, width, height);

	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 172, 23);
	cairo_set_line_width(cr, 0.0025);
	cairo_triangle(cr, a, b, c);
	cairo_stroke(cr);

	cairo_surface_write_to_png(surface, filename);

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}

int test_cairo_sierpinski_triangle(void *args) {
	const char* filename = (char*) args;
	const unsigned int width = 512, height = 512;
	point_t a = {1.0 / 2, 1.0 / 5}, b = {5.0 / 6, 4.0 / 5},
			c = {1.0 / 6, 4.0 / 5};
	cairo_t *cr;
	cairo_surface_t *surface;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);
	cairo_scale(cr, width, height);

	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 75.0 / 256, 69.0 / 256, 209.0 / 256);
	cairo_set_line_width(cr, 0.0025);
	cairo_sierpinski_triangle(cr, a, b, c, 5);
	cairo_stroke(cr);

	cairo_surface_write_to_png(surface, filename);

	cairo_destroy(cr);
	cairo_surface_destroy(surface);

	return 0;
}

int test_uncategorized(void *args) {
	char *digits = "0123456ABCDEFZXYWVUwvu";
	char *numbers[] = {"A494BC", "AA", "AF", "A0", "C0"};
	int i, s = 5;

	for (i = 0; i < strlen(digits); i++) {
		printf("isxdigit(%c) == %d\n", digits[i], isxdigit(digits[i]));
	}

	for (i = 0; i < s; i++) {
		printf("strtol(\"%s\") = %ld\n", numbers[i], strtol(numbers[i], NULL, 16));
	}

	return 0;
}
