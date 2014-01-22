/*
 * Using jprobes
 *
 * Test the jprobes facility by instrumenting a commonly used exported
 * kernel function.
 *
 * Keep a counter of how many times the function is called.  If you
 * print it out each time, be careful not to get overwhelmed with
 * output.
 *
 @*/

#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

static long exec_count = 0;

static void do_fork_inst(struct timer_list *timer, unsigned long expires)
{
	exec_count++;
	if (exec_count % 10 == 0)
		pr_info("mod_timer_count=%ld\n", exec_count);
	jprobe_return();
}

static struct jprobe jp = {
	.kp.addr = (kprobe_opcode_t *) mod_timer,
	.entry = (kprobe_opcode_t *) do_fork_inst,
};

static int __init my_init(void)
{
	register_jprobe(&jp);
	pr_info("plant jprobe at %p, handler addr %p\n", jp.kp.addr, jp.entry);
	return 0;
}

static void __exit my_exit(void)
{
	unregister_jprobe(&jp);
	pr_info("jprobe unregistered\n");
	pr_info("EXIT: exec_count = %ld\n", exec_count);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Mikhail Zhidko");
MODULE_DESCRIPTION("Ch10: lab2_jprobes.c");
MODULE_LICENSE("GPL v2");
