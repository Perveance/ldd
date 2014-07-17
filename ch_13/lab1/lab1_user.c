#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

struct my_data {
	int i;
	long l;
	char str[256];
} my_data;

#define MYIOC_TYPE 'k'

int main(int argc, char *argv[])
{
	int fd, rc;
	int MY_IOCTL;
	char *nodename = "/dev/mycdrv";

	/* Open the device node */
	if (argc > 1)
		nodename = argv[1];

	fd = open(nodename, O_RDWR);
	printf(" I opened the device node, file descriptor = %d\n", fd);
    if (fd < 0) {
        printf("Failed to open the device node, fd = %d \n", fd);
        return;
    } else {
    }

	/* Retrieve the original values; */
	MY_IOCTL = (int)_IOR(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("\n rc from ioctl reading = %d \n\n", rc);
	printf("\tmy_data.i = %d\n\tmy_data.x = %ld\n\tmy_data.s = %s\n",
	       my_data.i, my_data.x, my_data.s);

	/* Fill up the data structure */
	strcpy(my_data.s, "a string");
	my_data.i = 11;
	my_data.x = -777;
	printf("\n Sending from user-space:\n");
	printf("\tmy_data.i = %d\n\tmy_data.x = %ld\n\tmy_data.s = %s\n",
	       my_data.i, my_data.x, my_data.s);

	/* Send to the device */
	MY_IOCTL = (int)_IOW(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("\n rc from ioctl = %d\n\n", rc);

	/* Reread device and see if it got through */
	MY_IOCTL = (int)_IOR(MYIOC_TYPE, 1, struct my_data);
	rc = ioctl(fd, MY_IOCTL, &my_data);
	printf("\n rc from ioctl reading = %d\n\n", rc);

	printf("\tmy_data.i = %d\n\tmy_data.x = %ld\n\tmy_data.s = %s\n",
	     my_data.i, my_data.x, my_data.s);

	close(fd);
	exit(0);

}
