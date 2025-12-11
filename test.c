/* Simple test driver for get_next_line.
 * Build: cc -Wall -Wextra -Werror test.c get_next_line.c get_next_line_utils.c -o gnl_test
 * Run:  ./gnl_test file1.txt file2.txt ...
 * If no args are given, it reads from stdin (press Ctrl+D to end).
 */

#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int run_fd(int fd, const char *label)
{
	char *line;
	int   count;

	count = 0;
	printf("=== Reading %s ===\n", label);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("[%04d] %s", count, line);
		if (line[strlen(line) - 1] != '\n')
			printf("\n");
		free(line);
		count++;
	}
	printf("(total lines: %d)\n\n", count);
	return 0;
}

static int run_file(const char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open %s: %s\n", path, strerror(errno));
		return 1;
	}
	run_fd(fd, path);
	close(fd);
	return 0;
}

int main(int argc, char **argv)
{
	int i;
	int rc;

	rc = 0;
	if (argc == 1)
		return run_fd(STDIN_FILENO, "stdin");
	i = 1;
	while (i < argc)
	{
		if (run_file(argv[i]) != 0)
			rc = 1;
		i++;
	}
	return rc;
}
