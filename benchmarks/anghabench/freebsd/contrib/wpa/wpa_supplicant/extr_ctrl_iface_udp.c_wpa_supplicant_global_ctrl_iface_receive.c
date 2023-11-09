#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_global {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct ctrl_iface_global_priv {int /*<<< orphan*/  ctrl_dst; int /*<<< orphan*/  cookie; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int COOKIE_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_1__) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_attach (int /*<<< orphan*/ *,struct sockaddr_in*,int) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_detach (int /*<<< orphan*/ *,struct sockaddr_in*,int) ; 
 char* wpa_supplicant_global_ctrl_iface_process (struct wpa_global*,char*,size_t*) ; 
 char* wpa_supplicant_global_get_cookie (struct ctrl_iface_global_priv*,size_t*) ; 

__attribute__((used)) static void wpa_supplicant_global_ctrl_iface_receive(int sock, void *eloop_ctx,
						     void *sock_ctx)
{
	struct wpa_global *global = eloop_ctx;
	struct ctrl_iface_global_priv *priv = sock_ctx;
	char buf[4096], *pos;
	int res;
#ifdef CONFIG_CTRL_IFACE_UDP_IPV6
	struct sockaddr_in6 from;
#else /* CONFIG_CTRL_IFACE_UDP_IPV6 */
	struct sockaddr_in from;
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
	socklen_t fromlen = sizeof(from);
	char *reply = NULL;
	size_t reply_len;
	u8 cookie[COOKIE_LEN];

	res = recvfrom(sock, buf, sizeof(buf) - 1, 0,
		       (struct sockaddr *) &from, &fromlen);
	if (res < 0) {
		wpa_printf(MSG_ERROR, "recvfrom(ctrl_iface): %s",
			   strerror(errno));
		return;
	}

#ifndef CONFIG_CTRL_IFACE_UDP_REMOTE
#ifndef CONFIG_CTRL_IFACE_UDP_IPV6
	if (from.sin_addr.s_addr != htonl((127 << 24) | 1)) {
		/*
		 * The OS networking stack is expected to drop this kind of
		 * frames since the socket is bound to only localhost address.
		 * Just in case, drop the frame if it is coming from any other
		 * address.
		 */
		wpa_printf(MSG_DEBUG, "CTRL: Drop packet from unexpected "
			   "source %s", inet_ntoa(from.sin_addr));
		return;
	}
#endif /* CONFIG_CTRL_IFACE_UDP_IPV6 */
#endif /* CONFIG_CTRL_IFACE_UDP_REMOTE */

	buf[res] = '\0';

	if (os_strcmp(buf, "GET_COOKIE") == 0) {
		reply = wpa_supplicant_global_get_cookie(priv, &reply_len);
		goto done;
	}

	if (os_strncmp(buf, "COOKIE=", 7) != 0) {
		wpa_printf(MSG_DEBUG, "CTLR: No cookie in the request - "
			   "drop request");
		return;
	}

	if (hexstr2bin(buf + 7, cookie, COOKIE_LEN) < 0) {
		wpa_printf(MSG_DEBUG, "CTLR: Invalid cookie format in the "
			   "request - drop request");
		return;
	}

	if (os_memcmp(cookie, priv->cookie, COOKIE_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "CTLR: Invalid cookie in the request - "
			   "drop request");
		return;
	}

	pos = buf + 7 + 2 * COOKIE_LEN;
	while (*pos == ' ')
		pos++;

	if (os_strcmp(pos, "ATTACH") == 0) {
		if (wpa_supplicant_ctrl_iface_attach(&priv->ctrl_dst,
						     &from, fromlen))
			reply_len = 1;
		else
			reply_len = 2;
	} else if (os_strcmp(pos, "DETACH") == 0) {
		if (wpa_supplicant_ctrl_iface_detach(&priv->ctrl_dst,
						     &from, fromlen))
			reply_len = 1;
		else
			reply_len = 2;
	} else {
		reply = wpa_supplicant_global_ctrl_iface_process(global, pos,
								 &reply_len);
	}

 done:
	if (reply) {
		sendto(sock, reply, reply_len, 0, (struct sockaddr *) &from,
		       fromlen);
		os_free(reply);
	} else if (reply_len == 1) {
		sendto(sock, "FAIL\n", 5, 0, (struct sockaddr *) &from,
		       fromlen);
	} else if (reply_len == 2) {
		sendto(sock, "OK\n", 3, 0, (struct sockaddr *) &from,
		       fromlen);
	}
}