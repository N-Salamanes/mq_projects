/**********************************/
/*         SID - 43690599         */
/**********************************/

/**********************************/
/*     Part A - Hash Function     */
/**********************************/

/**********************************/
/*      Predefined Functions      */
/**********************************/

\\convert a string of characters to a decimal number based on 7 bit ASCII representation of a character

{StringToDecimal(S) =
	local(T, V, i, j, tmp);
	T = "";
	V = [];
	for(i = 1, length(S),
		for(j = 32, 127, U = Strchr(j); tmp = concat(T, U); if(S < tmp, V = concat(V, j - 1);T = concat(T, Strchr(j - 1)); break)));
return(subst(Pol(V),x,128))};

\\list of symbols used for hexadecimal notation
symbol = ["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","_"];

\\convert a decimal number to hexadecimal notation
{DecimalToHexa(nb) =
local(t, w, i);
if(nb == 0, return(x0),
    w = "";
    t = nb;
    while( t != 0,
           i = t%16;
           t = (t - i)/16;
           w = concat(symbol[i+1], w);
         );
    return(concat("0x",w));
  );
};

/**********************************/
/*             Setup              */
/**********************************/

\\for tasks 1 & 2
t_1 = 56;
p_1 = 41741174983174439;
alpha_1 = 36926743833962135;
beta_1 = 22414020065828731;

\\for tasks 3
t_3 = 32;
p_3 = 2333241047;
alpha_3 = 1371996871;
beta_3 = 1957652601;

\\for task 4
t_4 = 56;
p_4 = 41741174983174439;
alpha_4 = 36926743833962135;
beta_4 = 22414020065828731;

/**********************************/
/*          My Functions          */
/**********************************/

DecimalToDigest(N, ALPHA, BETA, P, T_NUM) = {
	new_T_NUM = T_NUM - 1;
	n1 = N \ (2 ^ new_T_NUM);
	expandedn1 = n1 * (2 ^ new_T_NUM);
	n2 = N - expandedn1;
	
	alphaDASH = lift(Mod(ALPHA, P) ^ n1);
	betaDASH = lift(Mod(BETA, P) ^ n2);
	
	result = (alphaDASH * betaDASH) % P;
	
	return(result);
};

StringToDigest(S, ALPHA, BETA, P, T_NUM) = {
	new_T_NUM = T_NUM - 1;
	n = StringToDecimal(S);
	n1 = n \ (2 ^ new_T_NUM);
	expandedn1 = n1 * (2 ^ new_T_NUM);
	n2 = n - expandedn1;
	
	alphaDASH = lift(Mod(ALPHA, P) ^ n1);
	betaDASH = lift(Mod(BETA, P) ^ n2);
	
	result = (alphaDASH * betaDASH) % P;
	
	return(result);
};

StringToDigestHex(S, ALPHA, BETA, P, T_NUM) = {
	Digest = StringToDigest(S, ALPHA, BETA, P, T_NUM);
	resultHEX = DecimalToHexa(Digest);
	
	return(resultHEX);
};

/**********************************/
/*      Task 1. [15 marks]        */
/**********************************/
\\What is the digest of "oCHOD3803T5c" using the hash function defined with the parameters above?

S = "oCHOD3803T5c";

task1() = {
	strDigest = StringToDigestHex(S, alpha_1, beta_1, p_1, t_1);
	return(strDigest);
}

/**********************************/
/*      Task 2. [25 marks]        */
/**********************************/
\\Find a password whose digest is equal to "0x234D6475132EEE" using the hash function defined with the parameters above

DigestToMatch = "0x234D6475132EEE";

\\WL = word list,
\\word list must be in the format of a single list containing words
task2(WL) = {
	n = 1;
	for (n = 1, length(WL), findDigest(WL[n]));
}

findDigest(str) = {
	strDigest = StringToDigestHex(str, alpha_1, beta_1, p_1, t_1);
	if(strDigest == DigestToMatch, print(str));
}

/**********************************/
/*      Task 3. [5 marks]         */
/**********************************/
\\Find a collision (i.e. two different integers < 2^(2*t-2) which evaluate to the same value) for the hash function defined with the following parameters:

M_Digests = Map();
limit_3 = 2^(2 * t_3 - 2);

task3() = {
	while(continue() == true,);
}

continue() = {
	num = random(limit_3);
	digest = DecimalToDigest(num, alpha_3, beta_3, p_3, t_3);
	
	if(!mapisdefined(M_Digests, digest),
	mapput(M_Digests, digest, num),
	print("Collision #1: ", num, " : ", digest);
	print("Collision #2: ", mapget(M_Digests, digest), " : ", digest);
	return(false); );
	
	return(true)
}

/**********************************/
/*      Task 4. [5 marks]         */
/**********************************/
\\Find a collision (i.e. two different integers < 2^(2*t-2) which evaluate to the same value) for the hash function defined with the following parameters:

n_4 = p_4 - 1;
N_4 = p_4;

limit_4 = 2^(2 * t_4 - 2);

task4() = {
	x = 1; a = 0; b = 0;
	X = x; A = a; B = b;
	
	int_i = 1;
	
	while( x != X; int_i < limit_4, \\conditions
	int_i = int_i + 1;	\\increment i
	new_xab_tup = new_xab(x, a, b); x = new_xab_tup[1]; a = new_xab_tup[2]; b = new_xab_tup[3];
	new_xab_tup = new_xab(X, A, B); X = new_xab_tup[1]; A = new_xab_tup[2]; B = new_xab_tup[3];
	new_xab_tup = new_xab(X, A, B); X = new_xab_tup[1]; A = new_xab_tup[2]; B = new_xab_tup[3];
	
	if (x == X, break);
	
	if (int_i % 1000000 == 0, print(int_i, "| x:", x, " a:", a, " b:", b, " X:", X, " A:", A, " B:", B));
	
	);
	
	print(int_i, "| x:", x, " a:", a, " b:", b, " X:", X, " A:", A, " B:", B);
	
	\\collision 1 consists of a & b
	coll1 = a;
	coll1 = coll1 * (2 ^ (t_4-1)); \\create enough space to concat both integers
	coll1 = coll1 + b;	\\concat
	\\collision 2 consists of A & B
	coll2 = A;
	coll2 = coll2 * (2 ^ (t_4-1)); \\create enough space to concat both integers
	coll2 = coll2 + B;	\\concat
	
	print("Collision #1: ", coll1, " : ", DecimalToDigest(coll1, alpha_4, beta_4, p_4, t_4));
	print("Collision #2: ", coll2, " : ", DecimalToDigest(coll2, alpha_4, beta_4, p_4, t_4));
}

new_xab(x, a, b) = {
	
	xMod3 = x % 3;
	
	if (xMod3 == 0, \\condition
	NEW_x = x * x % N_4;
	NEW_a = a * 2 % n_4;
	NEW_b = b * 2 % n_4;	
	return([NEW_x, NEW_a, NEW_b])
	);
	
	if (xMod3 == 1, \\condition
	NEW_x = x * alpha_4 % N_4;
	NEW_a = (a + 1) % n_4;
	NEW_b = b; \\we need to return a tuple
	return([NEW_x, NEW_a, NEW_b])
	);

	if (xMod3 == 2, \\condition
	NEW_x = x * beta_4 % N_4;
	NEW_a = a; \\we need to return a tuple
	NEW_b = (b + 1) % n_4;
	return([NEW_x, NEW_a, NEW_b])
	);
}

/**********************************/
/* Part B - Elliptic Curve Crypto */
/**********************************/

/**********************************/
/*             Setup              */
/**********************************/

p_pB = 566664694857199;
a_pB = 473792106600036;
b_pB = 13241554027609;

\\E is defined by: y^2 = x^3 + a*x + b (mod p)

P_pB = [331528354083331, 347343495874327]; \\is a point on E of order 566664693609221

nA = 508764086488465;					\\Alice's   private key:  nA = 508764086488465
PA = [551849066628960, 458550993333869]; \\Alice's   public key :  PA = nA*P = [551849066628960, 458550993333869]
										\\Bob's     private key:  nB = ?
PB = [43999599516736, 239004859880623];  \\Bob's     public key :  PB = nB*P = [43999599516736, 239004859880623]
										\\Charlie's private key:  nC = ?
PC = [285790648271248, 268925417979946]; \\Charlie's public key :  PC = nC*P = [285790648271248, 268925417979946]

/**********************************/
/*      Task 5. [15 marks]        */
/**********************************/

\\Find the point Q with smallest possible x-coordinate > 0 and with corresponding y coordinate < p/2
\\Find the point R with largest  possible positive x-coordinate < p and with corresponding y coordinate > p/2
\\Compute Q + R

pDiv2 = p_pB \ 2;

task5() = {
	\\define elliptic curve
	e = ellinit([0,0,0,a_pB, b_pB]*Mod(1, p_pB));
	
	Q = findQ(e);
	R = findR(e);
	
	print(lift(elladd(e, Q, R)));
}

findQ(e) = {
	\\smallest possible x-coordinate > 0 and with corresponding y coordinate < p/2
	int_x = 1;
	
	while (int_x < p_pB, 									\\ while condition
		yPts = lift(ellordinate(e, int_x)); 				\\ get y points
		for (yIndex = 1, length(yPts),						\\ go through y points
			if(yPts[yIndex] < pDiv2,						\\ if y point matches condition
				if(ellisoncurve(e, [int_x, yPts[yIndex]]),	\\ if x,y point is on curve
					return([int_x, yPts[yIndex]])			\\ return it
					)
			)
		);
		int_x = int_x + 1									\\increment x
	);
}

findR(e) = {
	\\smallest possible x-coordinate > 0 and with corresponding y coordinate < p/2
	int_x = p_pB;
	
	while (int_x > 0,	 									\\ while condition
		yPts = lift(ellordinate(e, int_x)); 				\\ get y points
		for (yIndex = 1, length(yPts),						\\ go through y points
			if(yPts[yIndex] > pDiv2,						\\ if y point matches condition
				if(ellisoncurve(e, [int_x, yPts[yIndex]]),	\\ if x,y point is on curve
					return([int_x, yPts[yIndex]])			\\ return it
					)
			)
		);
		int_x = int_x - 1									\\decrement x
	);
}

/**********************************/
/*      Task 6. [25 marks]        */
/**********************************/

\\Bob encrypted his birthday and sent it to Alice in the
\\form of the following point C = [517323948695448, 231807069390648]
\\What is Bob's birthday?

C = [517323948695448, 231807069390648];

task6() = {
	\\ set up elliptic curve
	e = ellinit([0,0,0,a_pB, b_pB]*Mod(1, p_pB));
	
	\\ nA times point PB on elliptic curve e
	multiply = ellmul(e, PB, nA);
	
	M = lift(ellsub(e, C, multiply));
	print(M[1]);
}


/**********************************/
/*      Task 7. [5 marks]         */
/**********************************/

\\Retrieve Bob's private key
task7() = {
	e = ellinit([0,0,0,a_pB, b_pB]*Mod(1, p_pB));
	found = false;
	count = 1;
	
	while (found == false, 						\\condition
		num = random(p_pB);						\\grab random number
		mulPt = lift(ellmul(e, P_pB, num));		\\multiply shared point with random number
		if (mulPt == PB,						\\if point matches bobs public key
			found = true;						
			print("FOUND: ", num));				\\print out private key
			
		count = count + 1;
	)
	
}
/**********************************/
/*      Task 8. [5 marks]         */
/**********************************/

\\Retrieve Charlie's private key







