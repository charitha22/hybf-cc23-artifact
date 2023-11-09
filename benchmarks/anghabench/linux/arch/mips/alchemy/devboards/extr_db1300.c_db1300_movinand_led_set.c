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
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  BCSR_LEDS ; 
 int /*<<< orphan*/  BCSR_LEDS_LED1 ; 
 int LED_OFF ; 
 int /*<<< orphan*/  bcsr_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void db1300_movinand_led_set(struct led_classdev *led,
				    enum led_brightness brightness)
{
	if (brightness != LED_OFF)
		bcsr_mod(BCSR_LEDS, BCSR_LEDS_LED1, 0);
	else
		bcsr_mod(BCSR_LEDS, 0, BCSR_LEDS_LED1);
}