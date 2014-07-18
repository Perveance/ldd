#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define MYIOC_TYPE 'M'

#define  MY_IOCTL_SET_PID      _IO(MYIOC_TYPE, 1)
#define  MY_IOCTL_SET_SIGNAL   _IO(MYIOC_TYPE, 2)
#define  MY_IOCTL_SEND_SIGNAL  _IO(MYIOC_TYPE, 3)

int main(int argc, char *argv[])
{
	int fd, rc;
	int MY_IOCTL, i;
	char *nodename = "/dev/mycdrv";
    pid_t pid = 11458;
    int signal = 9;

    /* Read the device node path */
	if (argc > 1)
		nodename = argv[1];

    if (argc == 4) {
        pid = atoi(argv[2]);
        signal = atoi(argv[3]);
    }

	/* Open the device node */
	fd = open(nodename, O_RDWR);
	printf("\tI opened the device node, file descriptor = %d\n", fd);
    if (fd < 0) {
        printf("\tFailed to open the device node, fd = %d\n", fd);
        return;
    }

	/* Send the pid number */
	rc = ioctl(fd, MY_IOCTL_SET_PID, pid);
	printf("\tioctl MY_IOCTL_SET_PID returned %d\n\n", rc);

	/* Send the signal number */
	rc = ioctl(fd, MY_IOCTL_SET_SIGNAL, signal);
	printf("\tioctl MY_IOCTL_SET_SIGNAL returned %d\n\n", rc);

	/* Send the signal */
	rc = ioctl(fd, MY_IOCTL_SEND_SIGNAL, NULL);
	printf("\tioctl MY_IOCTL_SEND_SIGNAL returned %d\n\n", rc);

	close(fd);
}
