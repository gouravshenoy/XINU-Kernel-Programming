#include <xinu.h>

/*------------------------------------------------------------------------
 * xsh_reset - reset xinu shell
 *------------------------------------------------------------------------
 */

shellcmd xsh_reset(int nargs, char *args[]){

	// get the address of the register
	volatile uint32 *prm_rstcrtl = (volatile uint32 *) 0x44E00F00;

	// generate a warm software reset (setting LSB to 1)
	*prm_rstcrtl = 0x01;
	
	return 0;
}
