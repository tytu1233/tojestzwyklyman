#include<linux/module.h>
#include<linux/timer.h>

static struct timer_list timer;


       However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  The termination condition for traversal is more complex.
           4.  Code size is about 40% greater and  operations  run  about  45%
               slower than lists.

       In the macro definitions, TYPE is the name of a user-defined structure,
       that must contain a field of  type  LIST_ENTRY,  TAILQ_ENTRY,  or  CIR‐
       CLEQ_ENTRY,  named  NAME.  The argument HEADNAME is the name of a user-
       defined structure that must be declared  using  the  macros  LIST_HEAD,
       TAILQ_HEAD, or CIRCLEQ_HEAD.  See the examples below for further expla‐
       nation of how these macros are used.

static void timer_handler(unsigned long int data)
{
	pr_info("Timer nr %lu is active!\n",data);
}

static int __init timer_module_init(void) 
{ 
	init_timer(&timer);
	timer.expires = jiffies + 15*HZ;
	timer.data = 0;
	timer.function = timer_handler;
	add_timer(&timer);
	return 0; 
}

However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  Code size is about 15% greater and  operations  run  about  20%
               slower than lists.

       Circular queues add the following functionality:

           *   Entries can be added at the end of a list.
           *   Entries can be added before another entry.
           *   They may be traversed backward, from tail to head.


static void __exit timer_module_exit(void) 
{
	if(del_timer_sync(&timer))
		pr_notice("The timer was not active!\n");
}

module_init(timer_module_init);
module_exit(timer_module_exit);
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
