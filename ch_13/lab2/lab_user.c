#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define MYIOC_TYPE 25

int main(int argc, char *argv[])
{
	int fd, rc;
	int MY_IOCTL, i;
	char *nodename = "/dev/mycdrv";
    int size = 0;
    char *buffer = NULL;

	/* Open the device node */
	if (argc > 1)
		nodename = argv[1];

    if (argc > 2)
        size = atoi(argv[2]);
    else
        size = 50;

	fd = open(nodename, O_RDWR);
	printf("\tI opened the device node, file descriptor = %d\n", fd);
    if (fd < 0) {
        printf("\tFailed to open the device node, fd = %d\n", fd);
        return;
    }

    buffer = (char *) malloc(size);
    printf("\tsize = %d\n", size);

	/* Retrieve the original values */
    MY_IOCTL = _IOC(_IOC_READ, MYIOC_TYPE, 1, size);
	rc = ioctl(fd, MY_IOCTL, buffer);
	printf("\tioctl returned %d\n\n", rc);

    printf("\tReading from the device %d bytes\n", size);
	printf("buffer[] = ");
    for (i = 0; i < size; i++)
	    printf("%c", buffer[i]);

	printf("\n");

	/* Reset the buffer */
    memset(buffer, '7', size);

	/* Send to the device */
    MY_IOCTL = _IOC(_IOC_WRITE, MYIOC_TYPE, 1, size);
	rc = ioctl(fd, MY_IOCTL, buffer);
	printf("\tioctl returned = %d\n", rc);

	/* Reread device and see if it got through */
    MY_IOCTL = _IOC(_IOC_READ, MYIOC_TYPE, 1, size);
	rc = ioctl(fd, MY_IOCTL, buffer);
	printf("\nioctl returned %d\n\n", rc);
	printf("buffer[] = ");
    for (i = 0; i < size; i++)
	    printf("%c", buffer[i]);

	printf("\n");

    free(buffer);
	close(fd);
}
