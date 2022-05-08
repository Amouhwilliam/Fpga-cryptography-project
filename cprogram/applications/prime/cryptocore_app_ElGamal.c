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
	
	MontMult1_params_t MontMult1_512_test = { 512,
	1,
	0,
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	{  },
	};

	ModSub_params_t ModSub_512_test = { 512,
	1,
	0,
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000001 },
	{  },
	};

	MontExp_params_t MontExp_512_test = { 512,
	1,
	0,
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	{  },
	{  },
	};
	
	MontMult_params_t MontMult_512_test = { 512,
	1,
	0,
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	{  },
	{  },
	};

	Encryption_params_t Encryption_512_test = { 512,
	1,
	0,
	{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	  0x00000000, 0x00000000, 0x00000000, 0x00000002},
	  
	{ 0xe8866e4b, 0x8b4cafa2, 0x63f190c6, 0x35bbc098, 
	  0xe8950a1b, 0xff87418d, 0x574ea3f9, 0x0dab411d, 
	  0x37882021, 0x5274e9c1, 0x71e70ebf, 0x598c9656, 
	  0xb834a93d, 0xe4c81225, 0x05a34701, 0x9c3a9c3f },
	{  },
	{  },
	{  },
	{  },
	{  },
	{  }
	};
	
	// Read random 'a' word from TRNG FIRO and clear msb
	i = 0;
	while (i < 1) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			trng_val &= 0x7FFFFFFF;
			Encryption_512_test.a[0] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	

	// Read remaining random 'a' words from TRNG FIRO
	i = 1;
	while (i < Encryption_512_test.prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			Encryption_512_test.a[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	
	
	printf("A: 0x");
	for(i=0; i<Encryption_512_test.prec/32; i++){
		printf("%08x", Encryption_512_test.a[i]);
	}
	printf("\n\n");
	
	// Read random 'b' word from TRNG FIRO and clear msb
	i = 0;
	while (i < 1) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			trng_val &= 0x7FFFFFFF;
			Encryption_512_test.b[0] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	

	// Read remaining random 'b' words from TRNG FIRO
	i = 1;
	while (i < Encryption_512_test.prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			Encryption_512_test.b[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	
	
	printf("B: 0x");
	for(i=0; i<Encryption_512_test.prec/32; i++){
		printf("%08x", Encryption_512_test.b[i]);
	}
	printf("\n\n");	
	
	// Read random m from TRNG FIRO
	i = 0;
	while (i < Encryption_512_test.prec/32) {
		ret_val = ioctl(dd, IOCTL_READ_TRNG_FIFO, &trng_val);
		if(ret_val == 0) {
			Encryption_512_test.m[i] = trng_val;
			i++;
		} else if (ret_val == -EAGAIN) {
			printf("TRNG FIFO empty\n");
		} else {
			printf("Error occured\n");
		}
	}	
	
	printf("M: 0x");
	for(i=0; i<Encryption_512_test.prec/32; i++){
		printf("%08x", Encryption_512_test.m[i]);
	}
	printf("\n\n");
	

	printf("N: 0x");
	for(i=0; i<Encryption_512_test.prec/32; i++){
		printf("%08x", Encryption_512_test.n[i]);
	}
	printf("\n\n");	
	
	
	//Set values for 1st Montgomery exponentiation
	// Set b
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.b[i] = Encryption_512_test.g[i];
	}
	// Set e
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.e[i] = Encryption_512_test.a[i];
	}
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTEXP, &MontExp_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 225\n");
		return 0;
	}
	
	//Set values for 2nd Montgomery exponentiation
	// Set b
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.b[i] = MontExp_512_test.c[i];
	}
	// Set e
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.e[i] = Encryption_512_test.b[i];
	}
	//Clear c
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.c[i] = 0;
	}
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTEXP, &MontExp_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 244\n");
		return 0;
	}
	// Set kab
	for(i=0; i<Encryption_512_test.prec/32; i++){
		Encryption_512_test.kab[i] = MontExp_512_test.c[i];
	}
	
	//Set values for Montgomery multiplication
	// Set a
	for(i=0; i<MontMult_512_test.prec/32; i++){
		MontMult_512_test.a[i] = Encryption_512_test.kab[i];
	}
	// Set b
	for(i=0; i<MontMult_512_test.prec/32; i++){
		MontMult_512_test.b[i] = Encryption_512_test.m[i];
	}
	
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTMULT, &MontMult_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 265\n");
		return 0;
	}
	
	// Set encrypt variable c
	for(i=0; i<MontMult_512_test.prec/32; i++){
		Encryption_512_test.c[i] = MontMult_512_test.c[i];
	}
	
	
	//subtraction
	for(i=0; i<ModSub_512_test.prec/32; i++){
		ModSub_512_test.a[i] = ModSub_512_test.n[i];
	}
	
	ret_val = ioctl(dd, IOCTL_MWMAC_MODSUB, &ModSub_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 297\n");
		return 0;
	}
	
	for(i=0; i<ModSub_512_test.prec/32; i++){
		ModSub_512_test.a[i] = ModSub_512_test.c[i];
	}
	
	for(i=0; i<ModSub_512_test.prec/32; i++){
		ModSub_512_test.b[i] = Encryption_512_test.a[i];
	}
	
	//Clear c
	for(i=0; i<ModSub_512_test.prec/32; i++){
		ModSub_512_test.c[i] = 0;
	}
	
	ret_val = ioctl(dd, IOCTL_MWMAC_MODSUB, &ModSub_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
		return 0;
	}
	
	//Set values for Montgomery exponentiation
	// Set b
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.b[i] = Encryption_512_test.b[i];
	}
	// Set e
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.e[i] = ModSub_512_test.c[i];
	}
	//Clear c
	for(i=0; i<MontExp_512_test.prec/32; i++){
		MontExp_512_test.c[i] = 0;
	}
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTEXP, &MontExp_512_test);
	if(ret_val != 0) {
		printf("Error occured\n");
		return 0;
	}
	
	//Set values for Montgomery multiplication
	// Set a
	for(i=0; i<MontMult_512_test.prec/32; i++){
		MontMult_512_test.a[i] = MontExp_512_test.c[i];
	}
	// Set b
	for(i=0; i<MontMult_512_test.prec/32; i++){
		MontMult_512_test.b[i] = Encryption_512_test.c[i];
	}
	//Clear c
	for(i=0; i<MontMult_512_test.prec/32; i++){
		MontMult_512_test.c[i] = 0;
	}
	
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTMULT, &MontMult_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 264\n");
		return 0;
	}	
	
	for(i=0; i<MontMult1_512_test.prec/32; i++){
		MontMult1_512_test.b[i] = MontMult_512_test.c[i];
	}
	
	ret_val = ioctl(dd, IOCTL_MWMAC_MONTMULT1, &MontMult1_512_test);
	if(ret_val != 0) {
		printf("Error occured at line 264\n");
		return 0;
	}	
	
	clock_gettime(CLOCK_MONOTONIC, &tend);
	
	
	// Set decrpyted d
	for(i=0; i<MontMult_512_test.prec/32; i++){
		Encryption_512_test.d[i] = MontMult1_512_test.c[i];
	}

	printf("D: 0x");
	for(i=0; i<Encryption_512_test.prec/32; i++){
		printf("%08x", Encryption_512_test.d[i]);
	}
	printf("\n\n");

	seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	if (seconds*1000000.0 > 1000.0)
		printf("MontExp 512 took about %.5f ms\n\n", seconds*1000.0);
	else 
		printf("MontExp 512 took about %.5f us\n\n", seconds*1000000.0);	

	// Clear c
	for(i=0; i<Encryption_512_test.prec/32; i++){
		Encryption_512_test.c[i] = 0;
	}	
	
//	Encryption_512_test.sec_calc = 1;	

	// clock_gettime(CLOCK_MONOTONIC, &tstart);
	// ret_val = ioctl(dd, IOCTL_MWMAC_MONTEXP, &Encryption_512_test);
	// if(ret_val != 0) {
		// printf("Error occured\n");
	// }

	// clock_gettime(CLOCK_MONOTONIC, &tend);

	// printf("C = MontExp(B,B,E,B,P): 0x");
	// for(i=0; i<Encryption_512_test.prec/32; i++){
		// printf("%08x", Encryption_512_test.c[i]);
	// }
	// printf("\n\n");

	// seconds = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec);
	// if (seconds*1000000.0 > 1000.0)
		// printf("MontExp 512 (sec calc) took about %.5f ms\n\n", seconds*1000.0);
	// else 
		// printf("MontExp 512 (sec calc) took about %.5f us\n\n", seconds*1000000.0);
	
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
