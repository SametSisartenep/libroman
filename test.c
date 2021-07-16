#include <u.h>
#include <libc.h>
#include "roman.h"

void
usage(void)
{
	fprint(2, "usage: %s [ -dr ] number\n", argv0);
	exits("usage");
}

void
main(int argc, char *argv[])
{
	int decimal;
	char *roman, buf[512];

	decimal = -1;
	roman = nil;

	ARGBEGIN{
	case 'd':
		roman = EARGF(usage());
		break;
	case 'r':
		decimal = strtol(EARGF(usage()), nil, 10);
		break;
	}ARGEND;
	if(argc != 0)
		usage();

	if(decimal > 0){
		if(dectoroman(decimal, buf, sizeof buf) < 0)
			sysfatal("dectoroman: %r");
		print("%s\n", buf);
	}else if(roman != nil){
		if((decimal = romantodec(roman)) < 0)
			sysfatal("romantodec: %r");
		print("%d\n", decimal);
	}else
		usage();

	exits(nil);
}
