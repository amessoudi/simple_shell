#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define AW_READ_SIZE 1024

/**
 * aw_getline - a custom getline function by Ahmed & Wissal.
 * @lineptr: The pointer to buffer.
 * @n: The size of buffer.
 * @stream: The input stream to read from.
 *
 * Return: The number of characters read
 *
 * Description: Reads an entire line from stream, storing the address of the
 * buffer containing the text into *lineptr. The buffer is null-terminated and
 * includes the newline character, if one was found.
 */
ssize_t aw_getline(char **lineptr, size_t *n, FILE *stream) {
	static char aw_buffer[AW_READ_SIZE];
	static ssize_t aw_buffer_size = 0;
	static char *aw_next = NULL;
	char *aw_ptr;
	ssize_t aw_total_size = 0;

	if (lineptr == NULL || n == NULL || stream == NULL) {
		return -1;
	}

	if (*lineptr == NULL) {
		*n = AW_READ_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL) {
			return -1;
		}
	}

	aw_ptr = *lineptr;

	while (1) {
		ssize_t aw_bytes_read;
		if (aw_next == NULL) {
			aw_bytes_read = read(fileno(stream), aw_buffer, AW_READ_SIZE);
			if (aw_bytes_read <= 0) {
				if (aw_total_size == 0) {
					return -1;
				}
				break;
			}
			aw_buffer_size = aw_bytes_read;
			aw_next = aw_buffer;
		}

		char *aw_newline = memchr(aw_next, '\n', aw_buffer_size);
		ssize_t aw_line_length = aw_newline ? (aw_newline - aw_next + 1) : aw_buffer_size;

		if (aw_total_size + aw_line_length + 1 > *n) {
			*n = aw_total_size + aw_line_length + 1;
			char *aw_new_lineptr = realloc(*lineptr, *n);
			if (aw_new_lineptr == NULL) {
				return -1;
			}
			*lineptr = aw_new_lineptr;
			aw_ptr = aw_new_lineptr + aw_total_size;
		}

		memcpy(aw_ptr, aw_next, aw_line_length);
		aw_total_size += aw_line_length;
		aw_ptr += aw_line_length;

		if (aw_newline) {
			aw_next = aw_newline + 1;
			aw_buffer_size -= aw_line_length;
			break;
		} else {
			aw_next = NULL;
		}
	}

	*aw_ptr = '\0';
	return aw_total_size;
}
