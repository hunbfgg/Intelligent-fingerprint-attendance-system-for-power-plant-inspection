/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Sergio R. Caprile - "commonalization" from prior samples and/or documentation extension
 *******************************************************************************/

#include "transport.h"
#include "stm32f10x_usart.h"
#include "common.h" 
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if !defined(SOCKET_ERROR)
	/** error in socket operation */
	#define SOCKET_ERROR -1
#endif


/**
This simple low-level implementation assumes a single connection for a single thread. Thus, a static
variable is used for that connection.
On other scenarios, the user must solve this by taking into account that the current implementation of
MQTTPacket_read() has a function pointer for a function call to get the data to a buffer, but no provisions
to know the caller or other indicator (the socket id): int (*getfn)(unsigned char*, int)
*/
int transport_sendPacketBuffer(USART_TypeDef *USART,unsigned char* buf, int buflen)
{
	u8 i;
	for(i=0;i<buflen;i++)  //发送连接报文
	{
		while((USART->SR&0x0080)==0);
		USART->DR=buf[i];
	}
	return 0;
}


int transport_getdata(unsigned char* buf, int count)
{
		memcpy(buf, (void*)&USART3_RX_BUF[0], count);
    //read_buf_len += count;
    return count;

}

int transport_getdatanb(void *sck, unsigned char* buf, int count)
{
//	int sock = *((int *)sck); 	/* sck: pointer to whatever the system may use to identify the transport */
//	/* this call will return after the timeout set on initialization if no bytes;
//	   in your system you will use whatever you use to get whichever outstanding
//	   bytes your socket equivalent has ready to be extracted right now, if any,
//	   or return immediately */
//	int rc = recv(sock, buf, count, 0);	
//	if (rc == -1) {
//		/* check error conditions from your system here, and return -1 */
//		return 0;
//	}
	return 0;
}

/**
return >=0 for a socket descriptor, <0 for an error code
@todo Basically moved from the sample without changes, should accomodate same usage for 'sock' for clarity,
removing indirections
*/
int transport_open(char* addr, int port)
{
	
	return 0;
}

int transport_close(int sock)
{

	return 0;
}


