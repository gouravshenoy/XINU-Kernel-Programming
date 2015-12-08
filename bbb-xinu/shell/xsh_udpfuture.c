/* xsh_udpfuture.c - xsh_udpfuture */

#include <network_future.h>

/*global futures definittion */
future *fut1;

/*------------------------------------------------------------------------
 * xsh_udpfuture - shell command that can send a message to a remote UDP
 *			server and receive a reply
 *------------------------------------------------------------------------
 */
shellcmd xsh_udpfuture(int nargs, char *args[])
{
	int	i;			/* index into buffer		*/
	int	retval;			/* return value			*/
	char	msg[] = "Xinu network_future test"; /* message to send	*/
	char	inbuf[1500];		/* buffer for incoming reply	*/
	int32	slot;			/* UDP slot to use		*/
	int32	msglen;			/* length of outgoing message	*/
	uint32	remoteip;		/* remote IP address to use	*/
	uint16	echoport= 21234;	/* port number for UDP send	*/
	uint16	locport	= 52743;	/* local port to use		*/
	int32	retries	= 3;		/* number of retries		*/
	int32	delay	= 2000;		/* reception delay in ms	*/
	int	fut_msg = 15;		/* test fut value		*/

	/* For argument '--help', emit help about the 'udpecho' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s  REMOTEIP\n\n", args[0]);
		printf("Description:\n");
		printf("\tReceive a message from a remote UDP server and send a reply\n");
		printf("Options:\n");
		printf("\tREMOTEIP:\tIP address in dotted decimal\n");
		printf("\t--help\t display this help and exit\n");
		printf("\tTIME: %d\n", clktime);
		return 0;
	}

	/* Check for valid IP address argument */

	if (nargs != 2) {
		fprintf(stderr, "%s: invalid argument(s)\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	if (dot2ip(args[1], &remoteip) == SYSERR) {
		fprintf(stderr, "%s: invalid IP address argument\r\n",
			args[0]);
		return 1;
	}

	/* register local UDP port */

	slot = udp_register(remoteip, echoport, locport);
	if (slot == SYSERR) {
		fprintf(stderr, "%s: could not reserve UDP port %d\n",
				args[0], locport);
		return 1;
	}

	/* Allocate futures */
	fut1= network_future_alloc(FUTURE_EXCLUSIVE);

	/* create the network_cons process */
	resume( create(network_cons, 1024, 20, "network_cons", 2, fut1, currpid) );

	/* Retry sending outgoing datagram and getting response */

	msglen = strnlen(msg, 1200);
	for (i=0; i<retries; i++) {
		//fprintf(stdout, "Inside for loop \n");
		retval = udp_send(slot, msg, msglen);
		if (retval == SYSERR) {
			fprintf(stderr, "%s: error sending UDP \n",
				args[0]);
			return 1;
		}

		fprintf(stdout, "Sent UDP message to remote: %s\n", msg);

		retval = udp_recv(slot, inbuf, sizeof(inbuf), delay);

		if (retval == TIMEOUT) {
			fprintf(stderr, "%s: timeout...\n", args[0]);
			continue;
		} else if (retval == SYSERR) {
			fprintf(stderr, "%s: error from udp_recv \n",
				args[0]);
			udp_release(slot);
			return 1;
		}
		break;
	}

	udp_release(slot);
	if (retval == TIMEOUT) {
		fprintf(stderr, "%s: retry limit exceeded\n",
			args[0]);
		return 1;
	}
	
	fprintf(stdout, "Received UDP message from remote: %s\n", inbuf);
	network_future_set(fut1, &fut_msg);


	/* wait for a message */
	receive();

	/* de-allocate the futures created */
	network_future_free(fut1);
	fprintf(stdout, "network_futures test successful.\n");
	
	return 0;
}
