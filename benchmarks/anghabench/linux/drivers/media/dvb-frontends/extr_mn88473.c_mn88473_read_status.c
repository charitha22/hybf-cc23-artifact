#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct mn88473_dev {int /*<<< orphan*/ * regmap; int /*<<< orphan*/  active; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {TYPE_11__* stat; } ;
struct TYPE_13__ {TYPE_9__* stat; } ;
struct TYPE_23__ {TYPE_7__* stat; } ;
struct TYPE_21__ {TYPE_5__* stat; } ;
struct TYPE_19__ {TYPE_3__* stat; } ;
struct TYPE_17__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {int delivery_system; TYPE_12__ block_count; TYPE_10__ block_error; TYPE_8__ post_bit_count; TYPE_6__ post_bit_error; TYPE_4__ cnr; TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_24__ {unsigned int uvalue; void* scale; } ;
struct TYPE_22__ {unsigned int uvalue; void* scale; } ;
struct TYPE_20__ {unsigned int uvalue; void* scale; } ;
struct TYPE_18__ {int svalue; void* scale; } ;
struct TYPE_16__ {unsigned int uvalue; void* scale; } ;
struct TYPE_14__ {unsigned int uvalue; void* scale; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
#define  SYS_DVBC_ANNEX_A 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int div_u64 (int,int) ; 
 struct mn88473_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int intlog10 (unsigned int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int mn88473_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct mn88473_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i, stmp;
	unsigned int utmp, utmp1, utmp2;
	u8 buf[5];

	if (!dev->active) {
		ret = -EAGAIN;
		goto err;
	}

	/* Lock detection */
	switch (c->delivery_system) {
	case SYS_DVBT:
		ret = regmap_read(dev->regmap[0], 0x62, &utmp);
		if (ret)
			goto err;

		if (!(utmp & 0xa0)) {
			if ((utmp & 0x0f) >= 0x09)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI | FE_HAS_SYNC |
					  FE_HAS_LOCK;
			else if ((utmp & 0x0f) >= 0x03)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		} else {
			*status = 0;
		}
		break;
	case SYS_DVBT2:
		ret = regmap_read(dev->regmap[2], 0x8b, &utmp);
		if (ret)
			goto err;

		if (!(utmp & 0x40)) {
			if ((utmp & 0x0f) >= 0x0d)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI | FE_HAS_SYNC |
					  FE_HAS_LOCK;
			else if ((utmp & 0x0f) >= 0x0a)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					  FE_HAS_VITERBI;
			else if ((utmp & 0x0f) >= 0x07)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		} else {
			*status = 0;
		}
		break;
	case SYS_DVBC_ANNEX_A:
		ret = regmap_read(dev->regmap[1], 0x85, &utmp);
		if (ret)
			goto err;

		if (!(utmp & 0x40)) {
			ret = regmap_read(dev->regmap[1], 0x89, &utmp);
			if (ret)
				goto err;

			if (utmp & 0x01)
				*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
						FE_HAS_VITERBI | FE_HAS_SYNC |
						FE_HAS_LOCK;
		} else {
			*status = 0;
		}
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	/* Signal strength */
	if (*status & FE_HAS_SIGNAL) {
		for (i = 0; i < 2; i++) {
			ret = regmap_bulk_read(dev->regmap[2], 0x86 + i,
					       &buf[i], 1);
			if (ret)
				goto err;
		}

		/* AGCRD[15:6] gives us a 10bit value ([5:0] are always 0) */
		utmp1 = buf[0] << 8 | buf[1] << 0 | buf[0] >> 2;
		dev_dbg(&client->dev, "strength=%u\n", utmp1);

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = utmp1;
	} else {
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* CNR */
	if (*status & FE_HAS_VITERBI && c->delivery_system == SYS_DVBT) {
		/* DVB-T CNR */
		ret = regmap_bulk_read(dev->regmap[0], 0x8f, buf, 2);
		if (ret)
			goto err;

		utmp = buf[0] << 8 | buf[1] << 0;
		if (utmp) {
			/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
			/* log10(65536) = 80807124, 0.2 = 3355443 */
			stmp = div_u64(((u64)80807124 - intlog10(utmp)
					+ 3355443) * 10000, 1 << 24);
			dev_dbg(&client->dev, "cnr=%d value=%u\n", stmp, utmp);
		} else {
			stmp = 0;
		}

		c->cnr.stat[0].svalue = stmp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	} else if (*status & FE_HAS_VITERBI &&
		   c->delivery_system == SYS_DVBT2) {
		/* DVB-T2 CNR */
		for (i = 0; i < 3; i++) {
			ret = regmap_bulk_read(dev->regmap[2], 0xb7 + i,
					       &buf[i], 1);
			if (ret)
				goto err;
		}

		utmp = buf[1] << 8 | buf[2] << 0;
		utmp1 = (buf[0] >> 2) & 0x01; /* 0=SISO, 1=MISO */
		if (utmp) {
			if (utmp1) {
				/* CNR[dB]: 10 * (log10(16384 / value) - 0.6) */
				/* log10(16384) = 70706234, 0.6 = 10066330 */
				stmp = div_u64(((u64)70706234 - intlog10(utmp)
						- 10066330) * 10000, 1 << 24);
				dev_dbg(&client->dev, "cnr=%d value=%u MISO\n",
					stmp, utmp);
			} else {
				/* CNR[dB]: 10 * (log10(65536 / value) + 0.2) */
				/* log10(65536) = 80807124, 0.2 = 3355443 */
				stmp = div_u64(((u64)80807124 - intlog10(utmp)
						+ 3355443) * 10000, 1 << 24);
				dev_dbg(&client->dev, "cnr=%d value=%u SISO\n",
					stmp, utmp);
			}
		} else {
			stmp = 0;
		}

		c->cnr.stat[0].svalue = stmp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	} else if (*status & FE_HAS_VITERBI &&
		   c->delivery_system == SYS_DVBC_ANNEX_A) {
		/* DVB-C CNR */
		ret = regmap_bulk_read(dev->regmap[1], 0xa1, buf, 4);
		if (ret)
			goto err;

		utmp1 = buf[0] << 8 | buf[1] << 0; /* signal */
		utmp2 = buf[2] << 8 | buf[3] << 0; /* noise */
		if (utmp1 && utmp2) {
			/* CNR[dB]: 10 * log10(8 * (signal / noise)) */
			/* log10(8) = 15151336 */
			stmp = div_u64(((u64)15151336 + intlog10(utmp1)
					- intlog10(utmp2)) * 10000, 1 << 24);
			dev_dbg(&client->dev, "cnr=%d signal=%u noise=%u\n",
				stmp, utmp1, utmp2);
		} else {
			stmp = 0;
		}

		c->cnr.stat[0].svalue = stmp;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	} else {
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* BER */
	if (*status & FE_HAS_LOCK && (c->delivery_system == SYS_DVBT ||
				      c->delivery_system == SYS_DVBC_ANNEX_A)) {
		/* DVB-T & DVB-C BER */
		ret = regmap_bulk_read(dev->regmap[0], 0x92, buf, 5);
		if (ret)
			goto err;

		utmp1 = buf[0] << 16 | buf[1] << 8 | buf[2] << 0;
		utmp2 = buf[3] << 8 | buf[4] << 0;
		utmp2 = utmp2 * 8 * 204;
		dev_dbg(&client->dev, "post_bit_error=%u post_bit_count=%u\n",
			utmp1, utmp2);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += utmp1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += utmp2;
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* PER */
	if (*status & FE_HAS_LOCK) {
		ret = regmap_bulk_read(dev->regmap[0], 0xdd, buf, 4);
		if (ret)
			goto err;

		utmp1 = buf[0] << 8 | buf[1] << 0;
		utmp2 = buf[2] << 8 | buf[3] << 0;
		dev_dbg(&client->dev, "block_error=%u block_count=%u\n",
			utmp1, utmp2);

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += utmp1;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue += utmp2;
	} else {
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}