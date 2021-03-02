#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/types.h>
dev_t dev_id;
struct cdev *arr_cdev;
static int Major;


#define BUF_LEN 80
static char msg[BUF_LEN];
static char *msg_Ptr;

struct proc_dir_entry *proc_parent_dir;
struct proc_dir_entry *entry;

#define MODULE_NAME "basic"
#define PPROC_ROOT  NULL  

ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp );


struct file_operations fops = {
   .owner = THIS_MODULE,
  /* .read = read, */
  /*  .write = write, */
  /*  .open = open, */
  /* .release = release */
};

ssize_t Basic_P_ProcWrite
    ( struct file                     *fp,
     const char __user                *pBuffer,
     size_t                            length,
     loff_t                           *pUnused )
{
    pr_info("write is called \n");
    return 0;
}

/* static int Basic_P_ProcRead */
/*     ( struct file                     *fp, */
/*       char                            *pBuffer, */
/*       size_t                           count, */
      /* loff_t                          *offp) */
ssize_t read_proc(struct file *filp,char  __user *buf,size_t count,loff_t *offp )
/* ssize_t simple_attr_read(struct file *file, char __user *buf, */
			 /* size_t len, loff_t *ppos) */
/* static int read_proc */
/*     ( char                            *pBuffer, */
/*       char                           **pStart, */
/*       off_t                            offset, */
/*       int                              count, */
/*       int                             *pEof, */
/*       void                            *pData ) */
{
    /* snprintf(msg,10,"mk node ksohre "); */
    int byte_read=0; 
    printk("read_proc is invoked \n");
    snprintf(msg,10,"I device id \n ");
    if(*msg_Ptr == '\0')
    {
        return 0;
    }
    while(*msg_Ptr)
    {
        put_user(*(msg_Ptr++),buf++);
        byte_read++;
    }
    return byte_read;
}


static const struct file_operations Basic_proc_fops= {
        
	.owner	=   THIS_MODULE,						\
    .read   =   read_proc,
    .write  =   Basic_P_ProcWrite,
    /* write:  Basigccc_P_ProcWrite, */
};

static int __init hellowolrd_init(void) {
    int ret=0;

    pr_info("init invoked!\n");
    
    entry = NULL;
    arr_cdev = cdev_alloc();    
    arr_cdev->ops = &fops;            // allowed file operations
    arr_cdev->owner = THIS_MODULE;    // this module
    printk(KERN_INFO "Inside init module\n");
    msg_Ptr = msg;
    ret = alloc_chrdev_region(&dev_id,0,1,MODULE_NAME);
    if (ret) {
        pr_info("alloc_char is failed \n");
        return ret;
    }
    Major  =MAJOR(dev_id);

    printk(KERN_INFO "init: Major %d\n", Major);
    /* register the driver - should show up in /proc/devices */
    ret = cdev_add(arr_cdev, dev_id, 1);
    if (ret < 0 ) {
        printk(KERN_INFO "Unable to allocate cdev");
        return ret;
    }
    
    proc_parent_dir=proc_mkdir("demo", PPROC_ROOT);
    /* entry = create_proc_entry(MODULE_NAME, S_IFREG | S_IRUGO,proc_parent_dir); */
    entry = proc_create_data(MODULE_NAME, S_IFREG|S_IRUGO,proc_parent_dir, &Basic_proc_fops, NULL);
    /* entry->read_proc = read_proc; */

    return 0;
}

static void __exit hellowolrd_exit(void) {
    pr_info("End of the world\n");
    remove_proc_entry(MODULE_NAME,proc_parent_dir);
    remove_proc_entry("demo", NULL);
    cdev_del(arr_cdev);
    unregister_chrdev_region(dev_id, 1);     /* return range of device numbers */
    unregister_chrdev(Major, MODULE_NAME);  /* release the major number */
}

module_init(hellowolrd_init);
module_exit(hellowolrd_exit);
MODULE_AUTHOR("kishore <kishore.kumar667@gmail.com>");
MODULE_LICENSE("GPL");

