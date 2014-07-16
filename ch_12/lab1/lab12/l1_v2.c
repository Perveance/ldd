#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>

extern struct semaphore my_sema;

static char *modname = __stringify(KBUILD_BASENAME);

static int __init my_init(void)
{

    printk("Module 2: INIT before down_trylock count = %u\n", my_sema.count);

    if (down_trylock(&my_sema) != 0) {

        printk("Module 2: Failed to obtain semaphore\n");
        return -EBUSY;

    } else {

        printk("Module 2: Semaphore obtained. count = %u\n", my_sema.count);

    }

    return 0;
}

static void __exit my_exit(void)
{

    printk("Module 2: EXIT. Before unlock count = %u\n", my_sema.count);

    up(&my_sema);

    printk("Module 2: EXIT. After unlock count = %u\n", my_sema.count);

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD Ch 12. Synchronization lab");
MODULE_LICENSE("GPL v2");
