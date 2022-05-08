/* 
* cryptocore_ioctl_header.h - the header file with the ioctl definitions.
* The declarations here have to be in a header file, because
* they need to be known both the kernel module in *_driver.c
* and the application *_app.c 
*/

#include <linux/ioctl.h>

// CryptoCore Struct Declarations:
typedef struct MontMult_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 a[128];
	__u32 b[128];
	__u32 c[128];
} MontMult_params_t;

typedef struct MontR_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 r[128];
} MontR_params_t;

typedef struct MontR2_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 r2[128];
} MontR2_params_t;

typedef struct MontExp_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 b[128];
	__u32 e[128];
	__u32 c[128];
} MontExp_params_t;

typedef struct ModAdd_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 a[128];
	__u32 b[128];
	__u32 c[128];
} ModAdd_params_t;

typedef struct ModSub_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 a[128];
	__u32 b[128];
	__u32 c[128];
} ModSub_params_t;

typedef struct CopyH2V_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 a[128];
	__u32 acopy[128];
} CopyH2V_params_t;

typedef struct CopyV2V_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 a[128];
	__u32 acopy[128];
} CopyV2V_params_t;

typedef struct CopyH2H_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 a[128];
	__u32 acopy[128];
} CopyH2H_params_t;

typedef struct CopyV2H_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 a[128];
	__u32 acopy[128];
} CopyV2H_params_t;

typedef struct MontMult1_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 b[128];
	__u32 c[128];
} MontMult1_params_t;

typedef struct ModExp_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[128];
	__u32 b[128];
	__u32 e[128];
	__u32 c[128];
} ModExp_params_t;

typedef struct ModRed_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 n[64];
	__u32 a[128];
	__u32 c[128];
} ModRed_params_t ;

// Add CryptoCore Struct Declarations here...

typedef struct Encryption_params{
	__u32 prec;
	__u32 f_sel;
	__u32 sec_calc;
	__u32 g[128]; //generator
	__u32 n[128]; //prime
	__u32 a[128]; //private key
	__u32 b[128]; //private key
	__u32 m[128]; //original message
	__u32 c[128]; //encrypted result
	__u32 d[128]; //decrypted result
	__u32 kab[128]; //(g^a)^b [which is equal to (g^b)^a]
} Encryption_params_t;

#define IOCTL_BASE 'k' 					// magic number

// NOTE: magic | cmdnumber | size of data to pass
#define 	IOCTL_SET_TRNG_CMD			_IOW(IOCTL_BASE,   1, __u32)
#define 	IOCTL_SET_TRNG_CTR			_IOW(IOCTL_BASE,   2, __u32)
#define 	IOCTL_SET_TRNG_TSTAB		_IOW(IOCTL_BASE,   3, __u32)
#define 	IOCTL_SET_TRNG_TSAMPLE		_IOW(IOCTL_BASE,   4, __u32)
#define 	IOCTL_READ_TRNG_FIFO		_IOR(IOCTL_BASE,   5, __u32)

#define		IOCTL_MWMAC_MONTMULT		_IOWR(IOCTL_BASE,  6, MontMult_params_t)
#define		IOCTL_MWMAC_MONTR			_IOWR(IOCTL_BASE,  7, MontR_params_t)
#define		IOCTL_MWMAC_MONTR2			_IOWR(IOCTL_BASE,  8, MontR2_params_t)
#define		IOCTL_MWMAC_MONTEXP			_IOWR(IOCTL_BASE,  9, MontExp_params_t)
#define		IOCTL_MWMAC_MODADD			_IOWR(IOCTL_BASE, 10, ModAdd_params_t)
#define		IOCTL_MWMAC_MODSUB			_IOWR(IOCTL_BASE, 11, ModSub_params_t)
#define		IOCTL_MWMAC_COPYH2V			_IOWR(IOCTL_BASE, 12, CopyH2V_params_t)
#define		IOCTL_MWMAC_COPYV2V			_IOWR(IOCTL_BASE, 13, CopyV2V_params_t)
#define		IOCTL_MWMAC_COPYH2H			_IOWR(IOCTL_BASE, 14, CopyH2H_params_t)
#define		IOCTL_MWMAC_COPYV2H			_IOWR(IOCTL_BASE, 15, CopyV2H_params_t)
#define		IOCTL_MWMAC_MONTMULT1		_IOWR(IOCTL_BASE, 16, MontMult1_params_t)
#define		IOCTL_MWMAC_MONTEXP_FULL	_IOWR(IOCTL_BASE, 17, MontExp_params_t)
#define		IOCTL_MWMAC_MODEXP			_IOWR(IOCTL_BASE, 18, ModExp_params_t)
#define		IOCTL_MWMAC_MODRED			_IOWR(IOCTL_BASE, 19, ModRed_params_t)

// Define further IOCTL commands here...
// #define		IOCTL_MWMAC_ENCRYPTION		_IOWR(IOCTL_BASE, 20, Encryption_params_t)