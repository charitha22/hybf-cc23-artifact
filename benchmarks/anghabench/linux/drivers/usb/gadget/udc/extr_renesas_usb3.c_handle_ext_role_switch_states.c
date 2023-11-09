#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct renesas_usb3 {int connection_state; int /*<<< orphan*/  driver; struct device* host_dev; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
#define  USB_ROLE_DEVICE 130 
#define  USB_ROLE_HOST 129 
#define  USB_ROLE_NONE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct renesas_usb3* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_attach (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int renesas_usb3_role_switch_get (struct device*) ; 
 int /*<<< orphan*/  usb3_connect (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_disconnect (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_mode (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_vbus_out (struct renesas_usb3*,int) ; 

__attribute__((used)) static void handle_ext_role_switch_states(struct device *dev,
					    enum usb_role role)
{
	struct renesas_usb3 *usb3 = dev_get_drvdata(dev);
	struct device *host = usb3->host_dev;
	enum usb_role cur_role = renesas_usb3_role_switch_get(dev);

	switch (role) {
	case USB_ROLE_NONE:
		usb3->connection_state = USB_ROLE_NONE;
		if (usb3->driver)
			usb3_disconnect(usb3);
		usb3_vbus_out(usb3, false);
		break;
	case USB_ROLE_DEVICE:
		if (usb3->connection_state == USB_ROLE_NONE) {
			usb3->connection_state = USB_ROLE_DEVICE;
			usb3_set_mode(usb3, false);
			if (usb3->driver)
				usb3_connect(usb3);
		} else if (cur_role == USB_ROLE_HOST)  {
			device_release_driver(host);
			usb3_set_mode(usb3, false);
			if (usb3->driver)
				usb3_connect(usb3);
		}
		usb3_vbus_out(usb3, false);
		break;
	case USB_ROLE_HOST:
		if (usb3->connection_state == USB_ROLE_NONE) {
			if (usb3->driver)
				usb3_disconnect(usb3);

			usb3->connection_state = USB_ROLE_HOST;
			usb3_set_mode(usb3, true);
			usb3_vbus_out(usb3, true);
			if (device_attach(host) < 0)
				dev_err(dev, "device_attach(host) failed\n");
		} else if (cur_role == USB_ROLE_DEVICE) {
			usb3_disconnect(usb3);
			/* Must set the mode before device_attach of the host */
			usb3_set_mode(usb3, true);
			/* This device_attach() might sleep */
			if (device_attach(host) < 0)
				dev_err(dev, "device_attach(host) failed\n");
		}
		break;
	default:
		break;
	}
}