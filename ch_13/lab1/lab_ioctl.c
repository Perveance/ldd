
#include <linux/module.h>
#include "lab_char.h"


struct my_data {
    int i;
    long l;
    char str[256];
};

static struct my_data my_data = {
    .i = -525,
    .l = 555525,
    .str = "Hi ioctl lab!!!",
};

#define MYIOC_TYPE 'k'

static long
mycdrv_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
    int size, rc, direction;
    void __user *ioargp = (void __user *)arg;

    if (_IOC_TYPE(cmd) != MYIOC_TYPE) {
        pr_info(" got invalid case, CMD=%d\n", cmd);
        return -EINVAL;
    }

    direction = _IOC_DIR(cmd);
    size = _IOC_SIZE(cmd);

    switch (direction) {
        case _IOC_WRITE:
            pr_info(
                " reading = %d bytes from user-space and writing to device\n",
                size);

            rc = copy_from_user(&my_data, ioargp, size);
            pr_info(
                "    my_data.i = %d\n    (int)my_data.x = %ld\n    my_data.s = %s\n",
                my_data.i, my_data.l, my_data.str);
            return rc;
            break;

        case _IOC_READ:
            pr_info(
                " reading device and writing = %d bytes to user-space\n",
                size);
            pr_info(
                "    my_data.i = %d\n    (int)my_data.x = %ld\n    my_data.s = %s\n",
                my_data.i, my_data.l, my_data.str);
            rc = copy_to_user(ioargp, &my_data, size);
            return rc;
            break;

        default:
            pr_info(" got invalid case, CMD=%d\n", cmd);
            return -EINVAL;
    }

}

static const struct file_operations mycdrv_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = mycdrv_unlocked_ioctl,
    .open = mycdrv_generic_open,
    .release = mycdrv_generic_release
};

module_init(my_generic_init);
module_exit(my_generic_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD Chapter 13, Lab 1");
MODULE_LICENSE("GPL v2");
