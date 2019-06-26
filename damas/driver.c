#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#include "driver.h"

/*-----------------------------------------------------------------------------*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andre Luis Martinotto");
MODULE_DESCRIPTION("Disciplina SO");

/*----------------------------------------------------------------------------*/
#define DEVICE 60
#define DEVICE_NAME "/dev/so"

#define BUF_MSG 80

#define SUCCESS 0
#define BUF_LEN 80

/*----------------------------------------------------------------------------*/

int init_device(void);
void cleanup_device(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length,loff_t * offset);
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

/*----------------------------------------------------------------------------*/

module_init(init_device);
module_exit(cleanup_device)

/*----------------------------------------------------------------------------*/
static int aberto = 0;
static char mensagem[BUF_MSG];
static char *ptr;

/*----------------------------------------------------------------------------*/
struct file_operations fops = {
	.read = device_read,
	.write = device_write,
    .open = device_open,
	.release = device_release,
	.unlocked_ioctl = device_ioctl	
};

/*----------------------------------------------------------------------------*/
int init_device(){

	int ret;

	ret = register_chrdev(DEVICE, DEVICE_NAME, &fops);

	if (ret < 0) {
		printk("Erro ao carregar o dispositivo %d\n.",DEVICE);	
		return ret;
	}

	printk("O dispositivo %d foi carregado.\n", DEVICE);

	return 0;
}

/*----------------------------------------------------------------------------*/

void cleanup_device(){

	unregister_chrdev(DEVICE, DEVICE_NAME);
	printk("O dispositivo %d foi descarregado.\n", DEVICE);
}


/*----------------------------------------------------------------------------*/
static int device_open(struct inode *inode, struct file *file){
	
	if (aberto){
		return -EBUSY;
	}
	aberto++;
	ptr = mensagem;
	try_module_get(THIS_MODULE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static int device_release(struct inode *inode, struct file *file){
	
	aberto--;

	module_put(THIS_MODULE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset){

	int bytes_read = 0;

	if (*ptr == 0){
		return 0;
	}

	while (length && *ptr) {

		put_user(*(ptr++), buffer++);
		length--;
		bytes_read++;
	}
	printk("Leu %d bytes correspondendo a mensagem: %s", bytes_read, mensagem);

	return bytes_read;
}

/*----------------------------------------------------------------------------*/
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset){
	
	int i;

	printk("tamanho: %d\n", length);
	for (i = 0; i < length && i < BUF_MSG; i++){
		printk("mensagem: %c", mensagem[i]);
		get_user(mensagem[i], buffer + i);
	}

	printk("Escreveu a mensagem: %s\n",mensagem);

	ptr = mensagem;

	return i;
}

/*----------------------------------------------------------------------------*/

static long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param){
	
	int i;
	char *temp;
	char ch;

	printk("\ncomunicou com o device_ioctl\n");
	/* 
	 * Switch according to the ioctl called 
	 */
	switch (ioctl_num) {
	case IOCTL_SET_MSG:
		printk("\ncaiu no set_msg\n");
		/* 
		 * Receive a pointer to a message (in user space) and set that
		 * to be the device's message.  Get the parameter given to 
		 * ioctl by the process. 
		 */
		temp = (char *)ioctl_param;

		/* 
		 * Find the length of the message 
		 */
		get_user(ch, temp);
		for (i = 0; ch && i < BUF_LEN; i++, temp++)
			get_user(ch, temp);

		device_write(file, (char *)ioctl_param, i, 0);
		break;

	case IOCTL_GET_MSG:
			printk("\ncaiu no get_msg\n");
		/* 
		 * Give the current message to the calling process - 
		 * the parameter we got is a pointer, fill it. 
		 */
		i = device_read(file, (char *)ioctl_param, 99, 0);
		

		/* 
		 * Put a zero at the end of the buffer, so it will be 
		 * properly terminated 
		 */
		put_user('\0', (char *)ioctl_param + i);
		break;
	}

	return SUCCESS;
	
}