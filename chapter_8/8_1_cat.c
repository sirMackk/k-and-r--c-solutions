/* 8-1: Rewrite the program cat from Chatper 7 using read, write, open, and close
 * instead of their standard libary equivalents. Perform experiments to determine
 * the relative speeds of the two versions. */

#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1

void filecopy(int input_fd, int output_fd);

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1)
        filecopy(0, 1);
    while (--argc) {
        if ((fd = open(*++argv, O_RDONLY, 0)) < 0)
            write(2, "Cannot open file\n", 17);
        else {
            filecopy(fd, 1);
            close(fd);
        }
    }

    return 0;
}

void filecopy(int input_fd, int output_fd)
{
    char buf[BUFSIZE];
    int n;

    while ((n = read(input_fd, buf, BUFSIZE)) > 0)
        write(output_fd, buf, n);
}
