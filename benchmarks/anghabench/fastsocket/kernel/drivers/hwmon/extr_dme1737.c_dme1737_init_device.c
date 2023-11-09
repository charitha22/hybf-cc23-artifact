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
typedef  int u8 ;
struct i2c_client {int addr; } ;
struct dme1737_data {scalar_t__ type; int config; int config2; int has_fan; int has_pwm; int* pwm_config; int* pwm_acz; int /*<<< orphan*/  vrm; int /*<<< orphan*/  in_nominal; struct i2c_client* client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME1737_REG_CONFIG ; 
 int /*<<< orphan*/  DME1737_REG_CONFIG2 ; 
 int /*<<< orphan*/  DME1737_REG_PWM (int) ; 
 int /*<<< orphan*/  DME1737_REG_PWM_CONFIG (int) ; 
 int /*<<< orphan*/  DME1737_REG_TACH_PWM ; 
 int EFAULT ; 
 int /*<<< orphan*/  IN_NOMINAL (scalar_t__) ; 
 int PWM_EN_FROM_REG (int) ; 
 int PWM_EN_TO_REG (int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct dme1737_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 scalar_t__ dme1737 ; 
 scalar_t__ dme1737_i2c_get_features (int,struct dme1737_data*) ; 
 void* dme1737_read (struct dme1737_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme1737_write (struct dme1737_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  force_start ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int dme1737_init_device(struct device *dev)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int ix;
	u8 reg;

	/* Point to the right nominal voltages array */
	data->in_nominal = IN_NOMINAL(data->type);

	data->config = dme1737_read(data, DME1737_REG_CONFIG);
	/* Inform if part is not monitoring/started */
	if (!(data->config & 0x01)) {
		if (!force_start) {
			dev_err(dev, "Device is not monitoring. "
				"Use the force_start load parameter to "
				"override.\n");
			return -EFAULT;
		}

		/* Force monitoring */
		data->config |= 0x01;
		dme1737_write(data, DME1737_REG_CONFIG, data->config);
	}
	/* Inform if part is not ready */
	if (!(data->config & 0x04)) {
		dev_err(dev, "Device is not ready.\n");
		return -EFAULT;
	}

	/* Determine which optional fan and pwm features are enabled/present */
	if (client) {   /* I2C chip */
		data->config2 = dme1737_read(data, DME1737_REG_CONFIG2);
		/* Check if optional fan3 input is enabled */
		if (data->config2 & 0x04) {
			data->has_fan |= (1 << 2);
		}

		/* Fan4 and pwm3 are only available if the client's I2C address
		 * is the default 0x2e. Otherwise the I/Os associated with
		 * these functions are used for addr enable/select. */
		if (client->addr == 0x2e) {
			data->has_fan |= (1 << 3);
			data->has_pwm |= (1 << 2);
		}

		/* Determine which of the optional fan[5-6] and pwm[5-6]
		 * features are enabled. For this, we need to query the runtime
		 * registers through the Super-IO LPC interface. Try both
		 * config ports 0x2e and 0x4e. */
		if (dme1737_i2c_get_features(0x2e, data) &&
		    dme1737_i2c_get_features(0x4e, data)) {
			dev_warn(dev, "Failed to query Super-IO for optional "
				 "features.\n");
		}
	} else {   /* ISA chip */
		/* Fan3 and pwm3 are always available. Fan[4-5] and pwm[5-6]
		 * don't exist in the ISA chip. */
		data->has_fan |= (1 << 2);
		data->has_pwm |= (1 << 2);
	}

	/* Fan1, fan2, pwm1, and pwm2 are always present */
	data->has_fan |= 0x03;
	data->has_pwm |= 0x03;

	dev_info(dev, "Optional features: pwm3=%s, pwm5=%s, pwm6=%s, "
		 "fan3=%s, fan4=%s, fan5=%s, fan6=%s.\n",
		 (data->has_pwm & (1 << 2)) ? "yes" : "no",
		 (data->has_pwm & (1 << 4)) ? "yes" : "no",
		 (data->has_pwm & (1 << 5)) ? "yes" : "no",
		 (data->has_fan & (1 << 2)) ? "yes" : "no",
		 (data->has_fan & (1 << 3)) ? "yes" : "no",
		 (data->has_fan & (1 << 4)) ? "yes" : "no",
		 (data->has_fan & (1 << 5)) ? "yes" : "no");

	reg = dme1737_read(data, DME1737_REG_TACH_PWM);
	/* Inform if fan-to-pwm mapping differs from the default */
	if (client && reg != 0xa4) {   /* I2C chip */
		dev_warn(dev, "Non-standard fan to pwm mapping: "
			 "fan1->pwm%d, fan2->pwm%d, fan3->pwm%d, "
			 "fan4->pwm%d. Please report to the driver "
			 "maintainer.\n",
			 (reg & 0x03) + 1, ((reg >> 2) & 0x03) + 1,
			 ((reg >> 4) & 0x03) + 1, ((reg >> 6) & 0x03) + 1);
	} else if (!client && reg != 0x24) {   /* ISA chip */
		dev_warn(dev, "Non-standard fan to pwm mapping: "
			 "fan1->pwm%d, fan2->pwm%d, fan3->pwm%d. "
			 "Please report to the driver maintainer.\n",
			 (reg & 0x03) + 1, ((reg >> 2) & 0x03) + 1,
			 ((reg >> 4) & 0x03) + 1);
	}

	/* Switch pwm[1-3] to manual mode if they are currently disabled and
	 * set the duty-cycles to 0% (which is identical to the PWMs being
	 * disabled). */
	if (!(data->config & 0x02)) {
		for (ix = 0; ix < 3; ix++) {
			data->pwm_config[ix] = dme1737_read(data,
						DME1737_REG_PWM_CONFIG(ix));
			if ((data->has_pwm & (1 << ix)) &&
			    (PWM_EN_FROM_REG(data->pwm_config[ix]) == -1)) {
				dev_info(dev, "Switching pwm%d to "
					 "manual mode.\n", ix + 1);
				data->pwm_config[ix] = PWM_EN_TO_REG(1,
							data->pwm_config[ix]);
				dme1737_write(data, DME1737_REG_PWM(ix), 0);
				dme1737_write(data,
					      DME1737_REG_PWM_CONFIG(ix),
					      data->pwm_config[ix]);
			}
		}
	}

	/* Initialize the default PWM auto channels zone (acz) assignments */
	data->pwm_acz[0] = 1;	/* pwm1 -> zone1 */
	data->pwm_acz[1] = 2;	/* pwm2 -> zone2 */
	data->pwm_acz[2] = 4;	/* pwm3 -> zone3 */

	/* Set VRM */
	if (data->type == dme1737) {
		data->vrm = vid_which_vrm();
	}

	return 0;
}