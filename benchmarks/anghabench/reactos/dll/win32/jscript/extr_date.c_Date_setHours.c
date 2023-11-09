#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  JS_E_MISSING_ARG ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  day (double) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 double local_time (int /*<<< orphan*/ ,TYPE_1__*) ; 
 double make_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_time (double,double,double,double) ; 
 double min_from_time (double) ; 
 double ms_from_time (double) ; 
 double sec_from_time (double) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_clip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  utc (double,TYPE_1__*) ; 

__attribute__((used)) static HRESULT Date_setHours(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    DateInstance *date;
    double t, hour, min, sec, ms;
    HRESULT hres;

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    if(!argc)
        return throw_type_error(ctx, JS_E_MISSING_ARG, NULL);

    t = local_time(date->time, date);

    hres = to_number(ctx, argv[0], &hour);
    if(FAILED(hres))
        return hres;

    if(argc > 1) {
        hres = to_number(ctx, argv[1], &min);
        if(FAILED(hres))
            return hres;
    }else {
        min = min_from_time(t);
    }

    if(argc > 2) {
        hres = to_number(ctx, argv[2], &sec);
        if(FAILED(hres))
            return hres;
    }else {
        sec = sec_from_time(t);
    }

    if(argc > 3) {
        hres = to_number(ctx, argv[3], &ms);
        if(FAILED(hres))
            return hres;
    }else {
        ms = ms_from_time(t);
    }

    t = make_date(day(t), make_time(hour, min, sec, ms));
    date->time = time_clip(utc(t, date));

    if(r)
        *r = jsval_number(date->time);
    return S_OK;
}