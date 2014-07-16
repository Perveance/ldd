#include <linux/module.h>
#include <linux/init.h>

extern struct mutex my_mutex;

static char *modname = __stringify(KBUILD_BASENAME);

static int __init my_init(void)
{

    printk("Module 3: INIT before trylock count = %d\n",
            atomic_read(&my_mutex.count));

    if (mutex_trylock(&my_mutex) == 0) {

        printk("Module 3: Failed to obtain mutex\n");
        return -EBUSY;

    } else {

        printk("Module 3: Mutex obtained. count = %d\n",
            atomic_read(&my_mutex.count));

    }

	return 0;
}

static void __exit my_exit(void)
{

    printk("Module 3: EXIT. Before unlock count = %d\n",
            atomic_read(&my_mutex.count));

    mutex_unlock(&my_mutex);

    printk("Module 3: EXIT. After unlock count = %d\n",
            atomic_read(&my_mutex.count));

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD Ch 12. Synchronization lab");
MODULE_LICENSE("GPL v2");
