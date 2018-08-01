#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../utils.h"


typedef int (*test_function) (void);

int test_std_rgba_to_cairo_rgba();


int main (int argc, char *argv[]) {
	test_function tests[] = {
		test_std_rgba_to_cairo_rgba
	};
	test_function current_test;

	size_t tests_no = sizeof(tests) / sizeof(test_function);
	int i;

	for (i = 0; i < tests_no; i++) {
		current_test = tests[i];

		fprintf(stderr, "Test %d... ", i + 1);

		if (current_test() == 0) {
			fputs("OK\n", stderr);
		} else {
			fputs("failed\n", stderr);
		}
	}

	return EXIT_SUCCESS;
}


int test_std_rgba_to_cairo_rgba() {
	char *input[] = {
		"#AABBCCDD", "#00112233", "#00AA11BB", "#12345678",
		"#aabbccdd", "#00112233", "#00aa11bb", "#12345678",
		"#AABB", "#AABBCCDDE", "AABBCCDD", "#ZXYV0101",
		"1'401409", "#UUBB0101",
	};
	const float expected_outputs[][4] = {
		{170.0 / 255, 187.0 / 255, 204.0 / 255, 221.0 / 255},
		{0.0, 17.0 / 255, 34.0 / 255, 51.0 / 255},
		{0.0, 170.0 / 255, 17.0 / 255, 187.0 / 255},
		{18.0 / 255, 52.0 / 255, 86.0 / 255, 120.0 / 255},
		{170.0 / 255, 187.0 / 255, 204.0 / 255, 221.0 / 255},
		{0.0, 17.0 / 255, 34.0 / 255, 51.0 / 255},
		{0.0, 170.0 / 255, 17.0 / 255, 187.0 / 255},
		{18.0 / 255, 52.0 / 255, 86.0 / 255, 120.0 / 255},
		{0}, {0}, {0}, {0}, {0}, {0}
	};
	const int expected_retvals[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1
	};

	float output[4];
	int elements = 8;
	int i, j, retval;
	char errmsg[256];

	for (i = 0; i < elements; i++) {
		memset(output, 0, sizeof(output));
		retval = std_rgba_to_cairo_rgba(input[i], output);

		snprintf(
			errmsg, 256,
			"Elem. %d, input = %s\nretval = %d\nrgba = {%f, %f, %f, %f}",
			i, input[i], retval, output[0], output[1], output[2], output[3]
		);
		ASSERT_MSG(retval == expected_retvals[i], errmsg, 1);

		for (j = 0; j < 4; j++) {
			ASSERT_MSG(
				output[j] == expected_outputs[i][j], errmsg, 1
			);
		}
	}

	return 0;
}
