
#include <linux/module.h>
#include "lab_char.h"

#define MYIOC_TYPE 'M'

#define  MY_IOCTL_SET_PID      _IO(MYIOC_TYPE, 1)
#define  MY_IOCTL_SET_SIGNAL   _IO(MYIOC_TYPE, 2)
#define  MY_IOCTL_SEND_SIGNAL  _IO(MYIOC_TYPE, 3)

static pid_t pid = 0;
static int signal = SIGKILL;
static struct task_struct *ts = NULL;

static long
mycdrv_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    pr_info("%s: cmd = %d arg = %lu\n", __func__, cmd, arg);

    switch (cmd) {
        case MY_IOCTL_SET_PID:
            pid = (int) arg;
            pr_info("%s: MY_IOCTL_SET_PID pid = %d\n", __func__, pid);
            ts = pid_task(find_vpid(pid), PIDTYPE_PID);
            if (ts != NULL) {
                pr_info("%s: pid's task_struct    = 0x%p\n", __func__, ts);
            }
            break;

        case MY_IOCTL_SET_SIGNAL:
            signal = (int) arg;
            pr_info("%s: MY_IOCTL_SET_SIGNAL signal = %d\n", __func__, signal);
            break;

        case MY_IOCTL_SEND_SIGNAL:
            pr_info("%s: MY_IOCTL_SEND_SIGNAL\n", __func__);

            if (ts != NULL) && (pid > 0) { /* User has specified the pid */
                ret = send_sig(signal, ts, 0);
                pr_info("%s: send_sig returned %d\n", __func__, ret);
            } else { /* Send signal to the invoking process */
                pr_info("%s: User haven't specified the pid; using current\n", __func__);
                ts = current;
                pid = (int)current->pid;
            }

            break;

        default:
            pr_info("%s: Invalid case, CMD=%d\n", __func__, cmd);
            return -EINVAL;
    }

    pr_info("%s: EXIT\n\n", __func__);

    return ret;
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
MODULE_DESCRIPTION("LDD Chapter 13, Lab 3");
MODULE_LICENSE("GPL v2");
