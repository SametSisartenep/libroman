#include <u.h>
#include <libc.h>
#include <ctype.h>
#include "roman.h"

static int decimal[] = {
	1000, 900,
	500, 400,
	100, 90,
	50, 40,
	10, 9,
	5, 4,
	1
};
static char *roman[] = {
	"M", "CM",
	"D", "CD",
	"C", "XC",
	"L", "XL",
	"X", "IX",
	"V", "IV",
	"I"
};
static int alpha2roman[] = {
	/* A, B,   C,   D, E, F, G, H, I, J, K,  L,    M */
	   0, 0, 100, 500, 0, 0, 0, 0, 1, 1, 0, 50, 1000,
	/* N, O, P, Q, R, S, T, U, V, W,  X, Y, Z */
	   0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 10, 0, 0
};


static int
getroman(char c)
{
	if(!isalpha(c))
		return -1;
	return alpha2roman[toupper(c) - 'A'];
}

int
dectoroman(int n, char *buf, ulong len)
{
	char *p;
	int i, o;

	o = 0;

	for(i = 0; i < nelem(decimal); i++){
		while(n >= decimal[i] && o < len-1){
			for(p = roman[i]; *p != 0 && o < len-1; )
				buf[o++] = *p++;
			n -= decimal[i];
		}
	}
	buf[o] = 0;
	return 0;
}

int
romantodec(char *buf)
{
	char *ebuf, *larger;
	int curno, largerno, dec;

	ebuf = strchr(buf, '\0');
	dec = 0;

	while(buf < ebuf){
		curno = getroman(*buf);
		if(curno < 0)
			return -1;
		larger = buf;
		do{
			largerno = getroman(*larger);
			if(largerno < 0)
				return -1;
			if(largerno > curno)
				break;
		}while(*++larger != 0);
		if(*larger == 0)
			dec += curno;
		else{
			dec += largerno;
			while(buf < larger)
				dec -= getroman(*buf++);
		}
		buf++;
	}
	return dec;
}
