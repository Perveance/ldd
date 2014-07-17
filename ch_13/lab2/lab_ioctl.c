
#include <linux/module.h>
#include "lab_char.h"


#define MYIOC_TYPE 25 

static long
mycdrv_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
    int size, rc, direction, nr, type;
    void __user *ioargp = (void __user *)arg;
    char *buffer = NULL;
    int i;

    type = _IOC_TYPE(cmd);
    if (type != MYIOC_TYPE) {
        pr_info(" got invalid case, CMD=%d\n", cmd);
        return -EINVAL;
    }

    direction = _IOC_DIR(cmd);
    size = _IOC_SIZE(cmd);
    nr = _IOC_NR(cmd);

    pr_info("%s: direction=%d, size=%d nr=%d\n", __func__, direction, size, nr);

    buffer = kmalloc(size, GFP_KERNEL);

    switch (direction) {
        case _IOC_WRITE:
            pr_info("%s: reading = %d bytes from user-space and writing to device\n", __func__, size);
            rc = copy_from_user(buffer, ioargp, size);
            pr_info("%s:           %d bytes read                                 \n", __func__, rc);

            break;

        case _IOC_READ:
            pr_info("%s: reading device and writing = %d bytes to user-space\n", __func__, size);
            memset(buffer, '5', size);
            rc = copy_to_user(ioargp, buffer, size);
            pr_info("%s:                              %d bytes copied       \n", __func__, rc);
            break;

        default:
            pr_info("%s: got invalid case, CMD=%d\n", __func__, cmd);
            return -EINVAL;
    }

    pr_info("buffer:\t");
    for (i = 0; i < size; i++) {
        pr_info("%c", buffer[i]);
    }
    pr_info("%s: EXIT\n\n", __func__);

    return rc;
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
MODULE_DESCRIPTION("LDD Chapter 13, Lab 2");
MODULE_LICENSE("GPL v2");
