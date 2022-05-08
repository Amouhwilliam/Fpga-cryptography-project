def Generate_ElGamal_key(PRECISION):    
    
    #--------------------------------------
    # Domain Parameters
    
    # choose a safe-prime and a generator
    
    p512 = 0xe8866e4b8b4cafa263f190c635bbc098e8950a1bff87418d574ea3f90dab411d378820215274e9c171e70ebf598c9656b834a93de4c8122505a347019c3a9c3f
    p768 = 0x937107d3bb60f83596b32bad38372343383044d3577a2d8fb88a7c1e54b17c102c0291d5d0f2850804fb739005c03d2255b288bf37ecd6363ad70a7aba7b07dea971cc0d4c22245b7b982149cffb1da56ba4fb9e4c91da8651b5623068daad8f
    p1024 = 0xe7bcc3b6beb2dc5431820b46b1cbc1ffabc62d886f19283f4c2818861b1a108af57d99d380efe4898411fec011beb50149b573d20bec2fe688ce7e00376cd81558438741b0b6a515b19dfeb0658d607d5c96f1574da631baa11c99dc7408294523daaf81754f00a8a5f749958659ab1f41131179bddb1c826155f711d3f0929f
    p1536 = 0xb504e26adccf2e54e382c9c12f7a2c6081a982e7136be670317d0310ad1c1735fe6854f6a4cb2725534c6588d2d2a1e48b6cf2a35f8d80ef73f67b5924ad9bbca68150054b0aa6d5c74f098965d88e7b8debfb4b8f37636ce90e219fc3282c8d8f78435f4fa6660195098bc019f918d7e0caedb58b3a4d664112549a4d39e74db250a4117e65ee59edf4da3f68cb91cd8682fe4958e7d157d6a16340a7ce4f66fd430d6a550aacd497bc9a281b27abe5cc89a4659414b1cc0f40b6f7186870b7
    p2048 = 0xb99033d7e4d61624be196183c09b1b198470667714492b8c5cd1f09cbb7e89348e1dabb8824299e5180411fc8c80577ef872cdba7e576f28ea4f668e62f6d749014af8f52ca4f21bd186938c494b1a8babc93ab3b8e44301b537bf3ddc0c33f1a4c82fcac1e4372b3547270444857f6957a640938821399950c79ac326431243b7ca01f9c2983bbcba2e9a6d1287385b97033cf999e282bfb18df00955b7a36b36c58dad27daced7c086055644c7149c72fba128d5e1ad25b39baf751d66b1112b52b207f76be46f470597d11cb13af489663a488b0cff717c1fdb1a0ce505006e7abd0148b68b7aee14333452988d37ef7964672737e4708f3f3fac58219857
    p3072 = 0xcc4efa72bf6480d527bb4087a9953a0b75e8485b3ddf067a9d4d4bd8cd9be917fe210876ab5f75fbf3aa920aa963170d1251dbda77c62a94dbf4de6d0c7f6d711932610041d1c3e5f7417b6f9fa96aa14ddb0267c5283d148ae209de3abd97854097123680679eb87d9f4532cbf61f24f3506dfde4bd03e073096fa1fc98f0ca3a5f6a7adf7737dad035e0833cdc89a12d7dd3a5de0c85a8efb8bdba332edfa96d07236751b2ed93815ca9708d78ba7872c1cd16829d24671a210207857ffabd3f5da732ebb44dc774b30cbbf86415b5e6a678499dadfda782d1a2e9b62fb65352198cfa72bd41c964ee60ba08239b69070fe42cdacfe9494b17354c5c106cc5ec783c7153ec4ba1369ed5b3a917aa7bdbd4849c862562aabe7829b6f9e158cb4a385e37e67940a9676c7a6f3754c2fcfde5b34cc606048af6330fc311da60e3766314745031331cf6071f5682a6b2e95d25f514a0fb487e68d8277d51a6a52b7c99bc56709a55c1a6645e48f14a89a69c9ef8dd8302f383819a099aa2691ca7
    p4096 = 0xf4c35aa86e9318703e6fbd231f00470e3ac5a249446e003ff351cb234a0295ad6a23b414f4bbc35ae1b1f853d693c03b843ccf6c62e119d37803a963a29a70e35ab158edba30022321395f620173a8463e7be0360ac60b8508a1bb967d64c0fbe2b1a3f586b1b8910d1c02ce0346bfc700fe40b7385d8a73dfe5035916734d0d898bd08b83a1261fe3a4d24023c1dd347ecacbad884d0d137624176ffbf0a611720d5a151017f1aceb268c97bc2bb8af9e25e0d8d386631b183af1b4610aeff9bff21baca8663ab1ccebbb87e49db367368c05892d415e135d8a650e0d6d90ab14e8f47aa86b5ba812c05073105472e6032758ca98ccd30b099a10c54cdeade0d8b863abd52794f66143c4176d9665431cb1264ff068ab75ee8f910a7fc9bc6ae03980a858c6031caecbd7f8c00b6329c103d76ce82872b9b13e49acc4e4cf9dd6fab254eadde42f2632015cdebbfab55bc734fe0622627ffd160456ee17af655dc9428926c68a96edc7574bfb5a18514af87539bc024e36e25438a31fdfe7eb83f8be247389427b6a1f3f67515b77a0017709d2133bc1a5afe38ea35b05a4f57a42eeb4c9d043baeac4d0347b6e1568922ff2745efea5faa70dc43a21e4b3718d9e3508a42f641669f7c8d73f43740612d0f895380c9f89ab23d403cc18a11990e77126ae67fabf8a961ff218407b20cbfb016769392026cec58af214022b4f

    if PRECISION == 512:
        p = p512
    elif PRECISION == 768:
        p = p768
    elif PRECISION == 1024:
        p = p1024
    elif PRECISION == 1536:
        p = p1536
    elif PRECISION == 2048:
        p = p2048
    elif PRECISION == 3072:
        p = p3072
    elif PRECISION == 4096:
        p = p4096

#   Generator
    g = 2
    
    print("Precision: ",PRECISION)
    print("Safe prime: ", p)
    print("Generator: ", g)
    
    #--------------------------------------
    # Generate Key Pair
    
    # choose private key
    
    a = Integer(getrandbits(PRECISION-1)) | 2^(PRECISION-2)
    print("Private key a: ", a)
    
    # Calc MontR2 - R2 = MontR2(p)
    r = (2^PRECISION) % p; r2 = (r*r) % p; rinv = inverse_mod(r,p)
    
    # Montgomerize the Base (Generator g) - MontMult
    g_MD = (g * r2 * rinv) % p
    
    # Montgomery Exponentiation - MontExp
    x = (1 * r2 * rinv) % p
    exp = a
    for i in reversed(range(PRECISION)):
        x = (x * x * rinv) % p
        if(Integer(exp).digits(base=2,padto=PRECISION)[i] == 1):
            x = (g_MD * x * rinv) % p
    A_MD = x

    # Demontgomerize A_MD - MontMult1
    A = (A_MD * 1 * rinv) % p

    #--------------------------------------
    # Encryption
    
    # choose random value b (each time!)
    b = Integer(getrandbits(PRECISION-1)) | 2^(PRECISION-2)
    print("Value of b: ", b)

    # choose random message m
    m = Integer(getrandbits(PRECISION-1)) | 2^(PRECISION-2)
    
    print ("Random message m: ",hex(m))

    # Montgomery Exponentiation - MontExp
    x = (1 * r2 * rinv) % p
    exp = b
    for i in reversed(range(PRECISION)):
        x = (x * x * rinv) % p
        if(Integer(exp).digits(base=2,padto=PRECISION)[i] == 1):
            x = (A_MD * x * rinv) % p
    t_MD = x

    # Calc c by MontMult
    c = (t_MD * m * rinv) % p
    print("Encrypted message: ", c)
    
    #--------------------------------------
    # Decryption
    
    # calc exponent (x = p-1-a)
    ex = p-1-a
    
    # Montgomery Exponentiation - MontExp
    x = (1 * r2 * rinv) % p
    exp = b
    for i in reversed(range(PRECISION)):
        x = (x * x * rinv) % p
        if(Integer(exp).digits(base=2,padto=PRECISION)[i] == 1):
            x = (g_MD * x * rinv) % p
    B_MD = x

    # Demontgomerize B_MD - MontMult1
    B = (B_MD * 1 * rinv) % p
  
    # Montgomery Exponentiation - MontExp
    x = (1 * r2 * rinv) % p
    exp = ex
    for i in reversed(range(PRECISION)):
        x = (x * x * rinv) % p
        if(Integer(exp).digits(base=2,padto=PRECISION)[i] == 1):
            x = (B_MD * x * rinv) % p
    t_MD = x

    # Calc m by MontMult
    m_result = (t_MD * c * rinv) % p
    
    print ("Decrypted message: ",hex(m_result))
    
    print("Message is Succesfully Decrypted!")
    
    #--------------------------------------
    
    return
    
Generate_ElGamal_key(4096)