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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct mv_gpio_softc {scalar_t__ pin_num; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ GPIO (scalar_t__) ; 
 scalar_t__ GPIO_DATA_IN_POLAR ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_reg_clear (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ mv_gpio_reg_read (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mv_gpio_reg_set (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mv_gpio_polarity(device_t dev, uint32_t pin, uint8_t enable, uint8_t toggle)
{
	uint32_t reg, reg_val;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	if (pin >= sc->pin_num)
		return;

	reg = GPIO_DATA_IN_POLAR;

	if (toggle) {
		reg_val = mv_gpio_reg_read(dev, reg) & GPIO(pin);
		if (reg_val)
			mv_gpio_reg_clear(dev, reg, pin);
		else
			mv_gpio_reg_set(dev, reg, pin);
	} else if (enable)
		mv_gpio_reg_set(dev, reg, pin);
	else
		mv_gpio_reg_clear(dev, reg, pin);
}