#include<linux/module.h>
#include<linux/interrupt.h>

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
       nation of how these macros are used

static void normal_tasklet_handler(unsigned long int data)
{
	pr_info("Hi! I'm a tasklet of a normal priority. My ID is: %lu\n",data);
}

static void privileged_tasklet_handler(unsigned long int data)
{
	pr_info("Hi! I'm a tasklet of a high priority. My ID is: %lu\n", data);
}



static DECLARE_TASKLET(normal_tasklet_1,normal_tasklet_handler,0);
static DECLARE_TASKLET(normal_tasklet_2,normal_tasklet_handler,1);
static DECLARE_TASKLET(privileged_tasklet_1,privileged_tasklet_handler,0);
static DECLARE_TASKLET(privileged_tasklet_2,privileged_tasklet_handler,1);


static int __init tasklets_init(void)
{
	tasklet_schedule(&normal_tasklet_1);
	tasklet_schedule(&normal_tasklet_2);
	tasklet_hi_schedule(&privileged_tasklet_1);
	tasklet_hi_schedule(&privileged_tasklet_2);
	return 0;
}
DESCRIPTION
       These macros define and operate on  three  types  of  data  structures:
       lists,  tail queues, and circular queues.  All three structures support
       the following functionality:

           *   Insertion of a new entry at the head of the list.
           *   Insertion of a new entry after any element in the list.
           *   Removal of any entry in the list.
           *   Forward traversal through the list.

       Lists are the simplest of the three data structures  and  support  only
       the above functionality.

       Tail queues add the following functionality:

           *   Entries can be added at the end of a list.

       However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  Code size is about 15% greater and  operations  run  about  20%
               slower than lists.

       Circular queues add the following functionality:


static void __exit tasklets_exit(void)
{
	tasklet_kill(&normal_tasklet_1);
	tasklet_kill(&normal_tasklet_2);
	tasklet_kill(&privileged_tasklet_1);
	tasklet_kill(&privileged_tasklet_2);
}

module_init(tasklets_init);
module_exit(tasklets_exit);
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
