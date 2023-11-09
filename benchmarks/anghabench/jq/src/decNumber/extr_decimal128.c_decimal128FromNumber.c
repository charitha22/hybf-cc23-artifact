#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_15__ {scalar_t__ bytes; } ;
typedef  TYPE_1__ decimal128 ;
struct TYPE_16__ {scalar_t__ exponent; int digits; int bits; scalar_t__* lsu; } ;
typedef  TYPE_2__ decNumber ;
struct TYPE_17__ {int status; int /*<<< orphan*/  round; } ;
typedef  TYPE_3__ decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DECIMAL128_Bias ; 
 int DECIMAL128_Ehigh ; 
 scalar_t__ DECIMAL128_Emax ; 
 scalar_t__ DECIMAL128_Emin ; 
 int DECIMAL128_Pmax ; 
 int DECIMAL_Inf ; 
 int DECIMAL_NaN ; 
 int DECIMAL_sNaN ; 
 int DECINF ; 
 scalar_t__ DECLITEND ; 
 int DECNAN ; 
 int DECNEG ; 
 int DECSPECIAL ; 
 int DEC_Clamped ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL128 ; 
 int /*<<< orphan*/  UBFROMUI (scalar_t__,int) ; 
 int /*<<< orphan*/  decContextDefault (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decContextSetStatus (TYPE_3__*,int) ; 
 int /*<<< orphan*/  decDigitsToDPD (TYPE_2__ const*,int*,scalar_t__) ; 
 scalar_t__ decNumberIsZero (TYPE_2__ const*) ; 
 int /*<<< orphan*/  decNumberPlus (TYPE_2__*,TYPE_2__ const*,TYPE_3__*) ; 
 int targhi ; 
 int targlo ; 
 int targmh ; 
 int targml ; 

decimal128 * decimal128FromNumber(decimal128 *d128, const decNumber *dn,
                                  decContext *set) {
  uInt status=0;                   // status accumulator
  Int ae;                          // adjusted exponent
  decNumber  dw;                   // work
  decContext dc;                   // ..
  uInt comb, exp;                  // ..
  uInt uiwork;                     // for macros
  uInt targar[4]={0,0,0,0};        // target 128-bit
  #define targhi targar[3]         // name the word with the sign
  #define targmh targar[2]         // name the words
  #define targml targar[1]         // ..
  #define targlo targar[0]         // ..

  // If the number has too many digits, or the exponent could be
  // out of range then reduce the number under the appropriate
  // constraints.  This could push the number to Infinity or zero,
  // so this check and rounding must be done before generating the
  // decimal128]
  ae=dn->exponent+dn->digits-1;              // [0 if special]
  if (dn->digits>DECIMAL128_Pmax             // too many digits
   || ae>DECIMAL128_Emax                     // likely overflow
   || ae<DECIMAL128_Emin) {                  // likely underflow
    decContextDefault(&dc, DEC_INIT_DECIMAL128); // [no traps]
    dc.round=set->round;                     // use supplied rounding
    decNumberPlus(&dw, dn, &dc);             // (round and check)
    // [this changes -0 to 0, so enforce the sign...]
    dw.bits|=dn->bits&DECNEG;
    status=dc.status;                        // save status
    dn=&dw;                                  // use the work number
    } // maybe out of range

  if (dn->bits&DECSPECIAL) {                      // a special value
    if (dn->bits&DECINF) targhi=DECIMAL_Inf<<24;
     else {                                       // sNaN or qNaN
      if ((*dn->lsu!=0 || dn->digits>1)           // non-zero coefficient
       && (dn->digits<DECIMAL128_Pmax)) {         // coefficient fits
        decDigitsToDPD(dn, targar, 0);
        }
      if (dn->bits&DECNAN) targhi|=DECIMAL_NaN<<24;
       else targhi|=DECIMAL_sNaN<<24;
      } // a NaN
    } // special

   else { // is finite
    if (decNumberIsZero(dn)) {               // is a zero
      // set and clamp exponent
      if (dn->exponent<-DECIMAL128_Bias) {
        exp=0;                               // low clamp
        status|=DEC_Clamped;
        }
       else {
        exp=dn->exponent+DECIMAL128_Bias;    // bias exponent
        if (exp>DECIMAL128_Ehigh) {          // top clamp
          exp=DECIMAL128_Ehigh;
          status|=DEC_Clamped;
          }
        }
      comb=(exp>>9) & 0x18;             // msd=0, exp top 2 bits ..
      }
     else {                             // non-zero finite number
      uInt msd;                         // work
      Int pad=0;                        // coefficient pad digits

      // the dn is known to fit, but it may need to be padded
      exp=(uInt)(dn->exponent+DECIMAL128_Bias);    // bias exponent
      if (exp>DECIMAL128_Ehigh) {                  // fold-down case
        pad=exp-DECIMAL128_Ehigh;
        exp=DECIMAL128_Ehigh;                      // [to maximum]
        status|=DEC_Clamped;
        }

      // [fastpath for common case is not a win, here]
      decDigitsToDPD(dn, targar, pad);
      // save and clear the top digit
      msd=targhi>>14;
      targhi&=0x00003fff;

      // create the combination field
      if (msd>=8) comb=0x18 | ((exp>>11) & 0x06) | (msd & 0x01);
             else comb=((exp>>9) & 0x18) | msd;
      }
    targhi|=comb<<26;              // add combination field ..
    targhi|=(exp&0xfff)<<14;       // .. and exponent continuation
    } // finite

  if (dn->bits&DECNEG) targhi|=0x80000000; // add sign bit

  // now write to storage; this is endian
  if (DECLITEND) {
    // lo -> hi
    UBFROMUI(d128->bytes,    targlo);
    UBFROMUI(d128->bytes+4,  targml);
    UBFROMUI(d128->bytes+8,  targmh);
    UBFROMUI(d128->bytes+12, targhi);
    }
   else {
    // hi -> lo
    UBFROMUI(d128->bytes,    targhi);
    UBFROMUI(d128->bytes+4,  targmh);
    UBFROMUI(d128->bytes+8,  targml);
    UBFROMUI(d128->bytes+12, targlo);
    }

  if (status!=0) decContextSetStatus(set, status); // pass on status
  // decimal128Show(d128);
  return d128;
  }