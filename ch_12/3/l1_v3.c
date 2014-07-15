#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{

	return 0;
}

static void __exit my_exit(void)
{


}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("LDD:Ch 12. Synchronization lab");
MODULE_LICENSE("GPL v2");
