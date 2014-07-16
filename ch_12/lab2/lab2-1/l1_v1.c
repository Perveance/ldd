#include <linux/module.h>
#include <linux/init.h>

struct mutex my_mutex;

DEFINE_MUTEX(my_mutex);
EXPORT_SYMBOL(my_mutex);

static int __init my_init(void)
{

    printk("1 module: Init count = %d\n", 
            atomic_read(&my_mutex.count) );

	return 0;
}

static void __exit my_exit(void)
{

    printk("1 module: Exit; count = %d \n",
            atomic_read(&my_mutex.count) );

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD:Ch 12. Synchronization lab");
MODULE_LICENSE("GPL v2");
