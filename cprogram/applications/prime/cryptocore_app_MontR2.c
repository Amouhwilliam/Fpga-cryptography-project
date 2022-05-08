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

	MontR2_params_t MontR2_512_test = { 512,
	1,
	0,
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	};

	printf("N: 0x");
	for(i=0; i<MontR2_512_test.prec/32; i++){
		printf("%08x", MontR2_512_test.n[i]);
	}
	printf("\n\n");	
	
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTR2, &MontR2_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);
	
	printf("R2 = MontR2(N,A): 0x");
	for(i=0; i<MontR2_512_test.prec/32; i++){
		printf("%08x", MontR2_512_test.r2[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("MontR2 512 took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("MontR2 512 took about %.5f us\n\n", seconds*1000000.0);	

	// Clear r2
	for(i=0; i<MontR2_512_test.prec/32; i++){
		MontR2_512_test.r2[i] = 0;
	}	
	
	MontR2_512_test.sec_calc = 1;	

	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTR2, &MontR2_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);
	
	printf("R2 = MontR2(N,A): 0x");
	for(i=0; i<MontR2_512_test.prec/32; i++){
		printf("%08x", MontR2_512_test.r2[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("MontR2 512 (sec calc) took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("MontR2 512 (sec calc) took about %.5f us\n\n", seconds*1000000.0);
	
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
