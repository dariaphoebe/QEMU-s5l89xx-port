#ifndef  HW_TCP_USB
#define  HW_TCP_USB

/*
 * USB over TCP driver.
 *
 * Copyright (c) 2011 Richard Ian Taylor.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include <pthread.h>

enum
{
	tcp_usb_setup = 1 << 0,
	tcp_usb_reset = 1 << 1,
};

typedef struct _tcp_usb_header
{
	uint8_t addr;
	uint8_t ep;
	uint8_t flags;
	int16_t length;

} __attribute__((packed)) tcp_usb_header_t;

struct _tcp_usb_state;
typedef int (*tcp_usb_callback_t)(struct _tcp_usb_state *_status, void *_arg, tcp_usb_header_t *_hdr, char *_buffer);

typedef struct _tcp_usb_state
{
	int socket;
	pthread_t thread;
	int closed;
	
	tcp_usb_callback_t callback;
	void *callback_arg;
} tcp_usb_state_t;

void tcp_usb_init(tcp_usb_state_t *_state, tcp_usb_callback_t _cb, void *_arg);
void tcp_usb_cleanup(tcp_usb_state_t *_state);

int tcp_usb_closed(tcp_usb_state_t *_state);

int tcp_usb_connect(tcp_usb_state_t *_state, char *_host, uint32_t _port);

int tcp_usb_request(tcp_usb_state_t *_state, tcp_usb_header_t *_header, const char *_data);

typedef struct _tcp_usb_host_state
{
	int socket;

} tcp_usb_host_state_t;

void tcp_usb_host_init(tcp_usb_host_state_t *_state);
void tcp_usb_host_cleanup(tcp_usb_host_state_t *_state);

int tcp_usb_host_okay(tcp_usb_host_state_t *_state);

int tcp_usb_host(tcp_usb_host_state_t *_state, uint32_t _port);
int tcp_usb_accept(tcp_usb_host_state_t *_host, tcp_usb_state_t *_client);

#endif //HW_TCP_USB