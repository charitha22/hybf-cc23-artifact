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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; int tm_year; } ;
struct msm6242_priv {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSM6242_CF ; 
 int MSM6242_CF_24H ; 
 int /*<<< orphan*/  MSM6242_DAY1 ; 
 int /*<<< orphan*/  MSM6242_DAY10 ; 
 int /*<<< orphan*/  MSM6242_HOUR1 ; 
 int /*<<< orphan*/  MSM6242_HOUR10 ; 
 int MSM6242_HOUR10_PM ; 
 int /*<<< orphan*/  MSM6242_MINUTE1 ; 
 int /*<<< orphan*/  MSM6242_MINUTE10 ; 
 int /*<<< orphan*/  MSM6242_MONTH1 ; 
 int /*<<< orphan*/  MSM6242_MONTH10 ; 
 int /*<<< orphan*/  MSM6242_SECOND1 ; 
 int /*<<< orphan*/  MSM6242_SECOND10 ; 
 int /*<<< orphan*/  MSM6242_WEEK ; 
 int /*<<< orphan*/  MSM6242_YEAR1 ; 
 int /*<<< orphan*/  MSM6242_YEAR10 ; 
 struct msm6242_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msm6242_lock (struct msm6242_priv*) ; 
 int msm6242_read (struct msm6242_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm6242_unlock (struct msm6242_priv*) ; 
 int /*<<< orphan*/  msm6242_write (struct msm6242_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm6242_set_time(struct device *dev, struct rtc_time *tm)
{
	struct msm6242_priv *priv = dev_get_drvdata(dev);

	msm6242_lock(priv);

	msm6242_write(priv, tm->tm_sec / 10, MSM6242_SECOND10);
	msm6242_write(priv, tm->tm_sec % 10, MSM6242_SECOND1);
	msm6242_write(priv, tm->tm_min / 10, MSM6242_MINUTE10);
	msm6242_write(priv, tm->tm_min % 10, MSM6242_MINUTE1);
	if (msm6242_read(priv, MSM6242_CF) & MSM6242_CF_24H)
		msm6242_write(priv, tm->tm_hour / 10, MSM6242_HOUR10);
	else if (tm->tm_hour >= 12)
		msm6242_write(priv, MSM6242_HOUR10_PM + (tm->tm_hour - 12) / 10,
			      MSM6242_HOUR10);
	else
		msm6242_write(priv, tm->tm_hour / 10, MSM6242_HOUR10);
	msm6242_write(priv, tm->tm_hour % 10, MSM6242_HOUR1);
	msm6242_write(priv, tm->tm_mday / 10, MSM6242_DAY10);
	msm6242_write(priv, tm->tm_mday % 10, MSM6242_DAY1);
	if (tm->tm_wday != -1)
		msm6242_write(priv, tm->tm_wday, MSM6242_WEEK);
	msm6242_write(priv, (tm->tm_mon + 1) / 10, MSM6242_MONTH10);
	msm6242_write(priv, (tm->tm_mon + 1) % 10, MSM6242_MONTH1);
	if (tm->tm_year >= 100)
		tm->tm_year -= 100;
	msm6242_write(priv, tm->tm_year / 10, MSM6242_YEAR10);
	msm6242_write(priv, tm->tm_year % 10, MSM6242_YEAR1);

	msm6242_unlock(priv);
	return 0;
}