def Prime_MontMult(a,b,n,prec):
	r = (2^prec) % n; rinv = inverse_mod(r,n)

	c = (a * b * rinv) % n

	return (c)

def Prime_MontR(n,prec):
	r = (2^prec) % n;

	return(r)

def Prime_MontR2(n,prec):
	r = (2^prec) % n; r2 = (r*r) % n;

	return(r2)

def Prime_MontExp(b,e,n,prec):
	r = 2^prec % n; r2 = (r*r) % n; rinv = inverse_mod(r,n)
 
	x = (1 * r2 * rinv) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x * rinv) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x * rinv) % n
	c = x

	return(c)

def Prime_ModAdd(a,b,n,prec):
	
	c = (a + b) % n

	return (c)

def Prime_ModSub(a,b,n,prec):

	c = (a - b) % n

	return (c)

def Prime_MontMult1(b,n,prec):
	r = (2^prec) % n; rinv = inverse_mod(r,n)

	c = (1 * b * rinv) % n

	return (c)
	
def Prime_ModExp(b,e,n,prec):
 
	x = (1) % n
	exp = e
	for i in reversed(xrange(prec)):
		x = (x * x) % n
		if(Integer(exp).digits(base=2,padto=prec)[i] == 1):
			x = (b * x) % n
	c = x

	return(c)

def Prime_ModRed(a,n,prec):

	c = a % n

	return(c)