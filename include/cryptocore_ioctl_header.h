/* 
* cryptocore_ioctl_header.h - the header file with the ioctl definitions.
* The declarations here have to be in a header file, because
* they need to be known both the kernel module in *_driver.c
* and the application *_app.c 
*/

#include <linux/ioctl.h>

#define IOCTL_BASE 'k' 					// magic number

// NOTE: magic | cmdnumber | size of data to pass
#define 	IOCTL_SET_TRNG_CMD		_IOW(IOCTL_BASE, 1, __u32)
#define 	IOCTL_SET_TRNG_CTR		_IOW(IOCTL_BASE, 2, __u32)
#define 	IOCTL_SET_TRNG_TSTAB		_IOW(IOCTL_BASE, 3, __u32)
#define 	IOCTL_SET_TRNG_TSAMPLE		_IOW(IOCTL_BASE, 4, __u32)
#define 	IOCTL_READ_TRNG_FIFO		_IOR(IOCTL_BASE, 5, __u32)

// Define further IOCTL commands here...