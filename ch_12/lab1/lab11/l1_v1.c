#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>

struct semaphore my_sema;

//DEFINE_MUTEX(my_mutex);
EXPORT_SYMBOL(my_sema);

static int __init my_init(void)
{

    sema_init(&my_sema, 1);

    printk("1 module: Init semaphore.count = %u\n", my_sema.count);

	return 0;
}

static void __exit my_exit(void)
{

    printk("1 module: Exit; count = %d \n", my_sema.count);

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD:Ch 12. Synchronization lab");
MODULE_LICENSE("GPL v2");
