#include <asm-generic/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../include/cryptocore_ioctl_header.h"

/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void close_physical (int);

int main(void)
{
	int dd = -1;
	int ret_val;

	__u32 trng_val = 0;
	__u32 i = 0;
	__u32 rw_prec = 0;
	
	double seconds;
	struct timespec tstart={0,0}, tend={0,0};

	if ((dd = open_physical (dd)) == -1)
      return (-1);

// Stop TRNG and clear FIFO
	trng_val = 0x00000010;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);

// Configure Feedback Control Polynomial
	trng_val = 0x0003ffff;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CTR, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Stabilisation Time
	trng_val = 0x00000050;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSTAB, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Configure Sample Time
	trng_val = 0x00000006;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_TSAMPLE, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

// Start TRNG
	trng_val = 0x00000001;
	ret_val = ioctl(dd, IOCTL_SET_TRNG_CMD, &trng_val);
	if(ret_val != 0) {
		printf("Error occured\n");
	}

	usleep(10);

	ModSub_params_t ModSub_191_test = { 191,
	0,
	0,
	{ 0x80000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000201                         },
	{  },
	{  },
	{  },
	};

	if(ModSub_191_test.prec % 32) {
		rw_prec = (ModSub_191_test.prec/32 + 1) * 32;
	} else {
		rw_prec = ModSub_191_test.prec;
	}
	
	// Read random a word from TRNG FIRO and clear msb
	i = 0;
	while (i < 1) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			trng_val &= 0x7FFFFFFF;
			ModSub_191_test.a[0] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}		
	
	// Read remaining random a words from TRNG FIRO
	i = 1;
	while (i < rw_prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			ModSub_191_test.a[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}		
	
	printf("A: 0x");
	for(i=0; i<rw_prec/32; i++){
		printf("%08x", ModSub_191_test.a[i]);
	}
	printf("\n\n");	
	
	// Read random b word from TRNG FIRO and clear msb
	i = 0;
	while (i < 1) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			trng_val &= 0x7FFFFFFF;
			ModSub_191_test.b[0] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}		
	
	// Read remaining random b words from TRNG FIRO
	i = 1;
	while (i < rw_prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			ModSub_191_test.b[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}		
	
	printf("B: 0x");
	for(i=0; i<rw_prec/32; i++){
		printf("%08x", ModSub_191_test.b[i]);
	}
	printf("\n\n");
	
	printf("N: 0x");
	for(i=0; i<rw_prec/32; i++){
		printf("%08x", ModSub_191_test.n[i]);
	}
	printf("\n\n");	
	
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODSUB, &ModSub_191_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);

	printf("C = ModSub(A,B,N): 0x");
	for(i=0; i<rw_prec/32; i++){
		printf("%08x", ModSub_191_test.c[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("ModSub 191 took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("ModSub 191 took about %.5f us\n\n", seconds*1000000.0);	

	// Clear c
	for(i=0; i<rw_prec/32; i++){
		ModSub_191_test.c[i] = 0;
	}	
	
	ModSub_191_test.sec_calc = 1;	

	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MODSUB, &ModSub_191_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);

	printf("C = ModSub(A,B,N): 0x");
	for(i=0; i<rw_prec/32; i++){
		printf("%08x", ModSub_191_test.c[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("ModSub 191 (sec calc) took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("ModSub 191 (sec calc) took about %.5f us\n\n", seconds*1000000.0);
	
	close_physical (dd);   // close /dev/cryptocore
	return 0;
}

// Open /dev/cryptocore, if not already done, to give access to physical addresses
int open_physical (int dd)
{
   if (dd == -1)
      if ((dd = open( "/dev/cryptocore", (O_RDWR | O_SYNC))) == -1)
      {
         printf ("ERROR: could not open \"/dev/cryptocore\"...\n");
         return (-1);
      }
   return dd;
}

// Close /dev/cryptocore to give access to physical addresses
void close_physical (int dd)
{
   close (dd);
}
