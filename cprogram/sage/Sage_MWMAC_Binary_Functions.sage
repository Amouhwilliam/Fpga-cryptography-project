prec = 191

F = GF(2^191, 'g', modulus = x^191 + x^9 + 1)
F.inject_variables()
R.<x,y> = F[]

def str_to_poly(str):
	I=Integer(str, base=16)
	v=F(0)
	for i in range (0,F.degree()):
		if(I >> i) & 1 > 0:
			v = v + g^i
	return v

def poly_to_str(poly):
	vec=poly._vector_()
	string = ""
	for i in range(0,len(vec)):
		string = string + str(vec[len(vec) - i - 1])
	return hex(Integer(string, base=2))

n = 0x800000000000000000000000000000000000000000000201

npoly = str_to_poly(n)
	
def Binary_MontMult(a,b,n,prec):
	r=(2^prec).__xor__(n); rpoly = str_to_poly(r)
	r2poly = rpoly*rpoly; r2 = poly_to_str(r2poly)
	rinvpoly = rpoly^-1; rinv = poly_to_str(rinvpoly)
	
	apoly = str_to_poly(a); bpoly = str_to_poly(b)
	
	cpoly = apoly * bpoly * rinvpoly; c = poly_to_str(cpoly)	

	return (c,cpoly)

def Binary_MontR(n,prec):
	r=(2^prec).__xor__(n); rpoly = str_to_poly(r); r = poly_to_str(rpoly)

	return(r,rpoly)

def Binary_MontR2(n,prec):
	r=(2^prec).__xor__(n); rpoly = str_to_poly(r);
	r2poly = rpoly*rpoly; r2 = poly_to_str(r2poly)

	return(r2,r2poly)

def Binary_MontExp(b,e,n,prec):
	r=(2^prec).__xor__(n); rpoly = str_to_poly(r)
	r2poly = rpoly*rpoly; r2 = poly_to_str(r2poly)
	rinvpoly = rpoly^-1; rinv = poly_to_str(rinvpoly)

	bpoly = str_to_poly(b)
	
	xpoly = (1 * r2poly * rinvpoly)
	exp = e
	for i in reversed(xrange(prec)):
		xpoly = xpoly * xpoly * rinvpoly
		if(exp.digits(base=2,padto=prec)[i] == 1):
			xpoly = bpoly * xpoly * rinvpoly
	cpoly = xpoly; c = poly_to_str(cpoly)

	return(c,cpoly)

def Binary_ModAdd(a,b,n,prec):
	apoly = str_to_poly(a); bpoly = str_to_poly(b)
	
	cpoly = apoly + bpoly; c = poly_to_str(cpoly)

	return (c,cpoly)

def Binary_ModSub(a,b,n,prec):
	apoly = str_to_poly(a); bpoly = str_to_poly(b)
	
	cpoly = apoly + bpoly; c = poly_to_str(cpoly)

	return (c,cpoly)	
	
def Binary_MontMult1(b,n,prec):
	r=(2^prec).__xor__(n); rpoly = str_to_poly(r)
	r2poly = rpoly*rpoly; r2 = poly_to_str(r2poly)
	rinvpoly = rpoly^-1; rinv = poly_to_str(rinvpoly)
	
	bpoly = str_to_poly(b)
	
	cpoly = 1 * bpoly * rinvpoly; c = poly_to_str(cpoly)	

	return (c,cpoly)

def Binary_ModExp(b,e,n,prec):

	bpoly = str_to_poly(b)
	
	xpoly = (1)
	exp = e
	for i in reversed(xrange(prec)):
		xpoly = xpoly * xpoly
		if(exp.digits(base=2,padto=prec)[i] == 1):
			xpoly = bpoly * xpoly
	cpoly = xpoly; c = poly_to_str(cpoly)

	return(c,cpoly)
