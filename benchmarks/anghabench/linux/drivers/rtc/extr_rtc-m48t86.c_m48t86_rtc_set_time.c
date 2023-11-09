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
struct rtc_time {unsigned char tm_sec; unsigned char tm_min; unsigned char tm_hour; unsigned char tm_mday; int tm_mon; int tm_year; unsigned char tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M48T86_B ; 
 unsigned char M48T86_B_DM ; 
 unsigned char M48T86_B_H24 ; 
 unsigned char M48T86_B_SET ; 
 int /*<<< orphan*/  M48T86_DOM ; 
 int /*<<< orphan*/  M48T86_DOW ; 
 int /*<<< orphan*/  M48T86_HOUR ; 
 int /*<<< orphan*/  M48T86_MIN ; 
 int /*<<< orphan*/  M48T86_MONTH ; 
 int /*<<< orphan*/  M48T86_SEC ; 
 int /*<<< orphan*/  M48T86_YEAR ; 
 unsigned char bin2bcd (int) ; 
 unsigned char m48t86_readb (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m48t86_writeb (struct device*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m48t86_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned char reg;

	reg = m48t86_readb(dev, M48T86_B);

	/* update flag and 24h mode */
	reg |= M48T86_B_SET | M48T86_B_H24;
	m48t86_writeb(dev, reg, M48T86_B);

	if (reg & M48T86_B_DM) {
		/* data (binary) mode */
		m48t86_writeb(dev, tm->tm_sec, M48T86_SEC);
		m48t86_writeb(dev, tm->tm_min, M48T86_MIN);
		m48t86_writeb(dev, tm->tm_hour, M48T86_HOUR);
		m48t86_writeb(dev, tm->tm_mday, M48T86_DOM);
		m48t86_writeb(dev, tm->tm_mon + 1, M48T86_MONTH);
		m48t86_writeb(dev, tm->tm_year % 100, M48T86_YEAR);
		m48t86_writeb(dev, tm->tm_wday, M48T86_DOW);
	} else {
		/* bcd mode */
		m48t86_writeb(dev, bin2bcd(tm->tm_sec), M48T86_SEC);
		m48t86_writeb(dev, bin2bcd(tm->tm_min), M48T86_MIN);
		m48t86_writeb(dev, bin2bcd(tm->tm_hour), M48T86_HOUR);
		m48t86_writeb(dev, bin2bcd(tm->tm_mday), M48T86_DOM);
		m48t86_writeb(dev, bin2bcd(tm->tm_mon + 1), M48T86_MONTH);
		m48t86_writeb(dev, bin2bcd(tm->tm_year % 100), M48T86_YEAR);
		m48t86_writeb(dev, bin2bcd(tm->tm_wday), M48T86_DOW);
	}

	/* update ended */
	reg &= ~M48T86_B_SET;
	m48t86_writeb(dev, reg, M48T86_B);

	return 0;
}