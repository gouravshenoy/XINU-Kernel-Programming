#include<xinu.h>

int32 fn_rec(int count)
{
	if(count == 0) {
		return 1;
	}
	else {
		return (count * fn_rec(count-1));
	}
}
