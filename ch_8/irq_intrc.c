/*
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int my_dev_id = 0;

static int irq = 77;
module_param(irq, int, S_IRUGO);

static irqreturn_t my_interrupt_handler(int irq, void *dev_id)
{
	printk("my_interrupt_handler CALLED!\n");
	return IRQ_NONE;
}

static int __init my_init(void)
{
	pr_info("Loading module \n");
	pr_info(" IRQ to intercept: %d\n", irq);
	if (request_irq(irq, my_interrupt_handler, /*IRQF_SHARED*/ 0, "msz_interrupt", &my_dev_id)) {
		pr_info("Failed to set up a handler for irq %d\n", irq);
		return -1;
	}
	printk("Successfully leading ISR handler\n");
	return 0;
}

static void __exit my_exit(void)
{
	synchronize_irq(irq);
	free_irq(irq, &my_dev_id);
	pr_info("IRQ handler freid successfully.\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LDD:2.0 s_03/lab1_module.c");
MODULE_LICENSE("GPL v2");
