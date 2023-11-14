#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"


#define AW_READ_SIZE 1024

/**
 * aw_getline - a custom getline function by Ahmed & Wissal.
 * @lineptr: The pointer to buffer.
 * @n: The size of buffer.
 * @stream: The input stream to read.
 *
 * Return: The number of characters read
 *
 * Description: Reads an entire line from stream
 */
ssize_t aw_getline(char **lineptr, size_t *n, FILE *stream)
{
	static char aw_buffer[AW_READ_SIZE];
	static ssize_t aw_buffer_size = 0;
	static char *aw_next = NULL;
	char *aw_ptr;
	char *aw_newline = NULL;
	char *aw_new_lineptr;
	ssize_t aw_bytes_read;
	size_t aw_line_length;
	ssize_t aw_total_size = 0;

	if (lineptr == NULL || n == NULL || stream == NULL) {
		return (-1);
	}

	if (*lineptr == NULL) {
		*n = AW_READ_SIZE;
		*lineptr = malloc(*n);
		if (*lineptr == NULL) {
			return (-1);
		}
	}

	aw_ptr = *lineptr;
	while (1) {
		if (aw_next == NULL) {
			aw_bytes_read = read(fileno(stream), aw_buffer, AW_READ_SIZE);
			if (aw_bytes_read <= 0) {
				if (aw_total_size == 0) {
					return (-1);
				}
				break;
			}
			aw_buffer_size = (size_t)aw_bytes_read; /* Cast aw_bytes_read to size_t */
			aw_next = aw_buffer;
		}

		aw_newline = memchr(aw_next, '\n', aw_buffer_size);
		/* Ensure that all expressions in the ternary operator have the same type (size_t) */
		aw_line_length = aw_newline ? (size_t)(aw_newline - aw_next + 1) : (size_t)aw_buffer_size;

		if ((size_t)aw_total_size + aw_line_length + 1 > *n)
		{
			*n = (size_t)aw_total_size + aw_line_length + 1;
			aw_new_lineptr = realloc(*lineptr, *n);
			if (aw_new_lineptr == NULL)
			{
				return (-1);
			}
			*lineptr = aw_new_lineptr;
			aw_ptr = aw_new_lineptr + aw_total_size;
		}

		memcpy(aw_ptr, aw_next, aw_line_length);
		aw_total_size += (ssize_t)aw_line_length; /* Cast aw_line_length to ssize_t */
		aw_ptr += aw_line_length;

		if (aw_newline) 
		{
			aw_next = aw_newline + 1;
			aw_buffer_size -= aw_line_length;
			break;
		}
		else
		{
			aw_next = NULL;
		}
	}

	*aw_ptr = '\0';
	return (aw_total_size);
}
