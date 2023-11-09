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
typedef  float real ;
typedef  scalar_t__ logical ;
typedef  int integer ;

/* Variables and functions */
 int c__1 ; 
 float c_b15 ; 
 float c_b29 ; 
 int ilaslr_ (int*,int*,float*,int*) ; 

int slarf_(char *side, integer *m, integer *n, real *v,
	integer *incv, real *tau, real *c__, integer *ldc, real *work)
{
    /* System generated locals */
    integer c_dim1, c_offset;
    real r__1;

    /* Local variables */
    static integer i__;
    static logical applyleft;
    extern /* Subroutine */ int sger_(integer *, integer *, real *, real *,
	    integer *, real *, integer *, real *, integer *);
    extern logical lsame_(char *, char *);
    static integer lastc;
    extern /* Subroutine */ int sgemv_(char *, integer *, integer *, real *,
	    real *, integer *, real *, integer *, real *, real *, integer *);
    static integer lastv;
    extern integer ilaslc_(integer *, integer *, real *, integer *), ilaslr_(
	    integer *, integer *, real *, integer *);


/*
    -- LAPACK auxiliary routine (version 3.2) --
    -- LAPACK is a software package provided by Univ. of Tennessee,    --
    -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
       November 2006


    Purpose
    =======

    SLARF applies a real elementary reflector H to a real m by n matrix
    C, from either the left or the right. H is represented in the form

          H = I - tau * v * v'

    where tau is a real scalar and v is a real vector.

    If tau = 0, then H is taken to be the unit matrix.

    Arguments
    =========

    SIDE    (input) CHARACTER*1
            = 'L': form  H * C
            = 'R': form  C * H

    M       (input) INTEGER
            The number of rows of the matrix C.

    N       (input) INTEGER
            The number of columns of the matrix C.

    V       (input) REAL array, dimension
                       (1 + (M-1)*abs(INCV)) if SIDE = 'L'
                    or (1 + (N-1)*abs(INCV)) if SIDE = 'R'
            The vector v in the representation of H. V is not used if
            TAU = 0.

    INCV    (input) INTEGER
            The increment between elements of v. INCV <> 0.

    TAU     (input) REAL
            The value tau in the representation of H.

    C       (input/output) REAL array, dimension (LDC,N)
            On entry, the m by n matrix C.
            On exit, C is overwritten by the matrix H * C if SIDE = 'L',
            or C * H if SIDE = 'R'.

    LDC     (input) INTEGER
            The leading dimension of the array C. LDC >= max(1,M).

    WORK    (workspace) REAL array, dimension
                           (N) if SIDE = 'L'
                        or (M) if SIDE = 'R'

    =====================================================================
*/


    /* Parameter adjustments */
    --v;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    applyleft = lsame_(side, "L");
    lastv = 0;
    lastc = 0;
    if (*tau != 0.f) {
/*
       Set up variables for scanning V.  LASTV begins pointing to the end
       of V.
*/
	if (applyleft) {
	    lastv = *m;
	} else {
	    lastv = *n;
	}
	if (*incv > 0) {
	    i__ = (lastv - 1) * *incv + 1;
	} else {
	    i__ = 1;
	}
/*     Look for the last non-zero row in V. */
	while(lastv > 0 && v[i__] == 0.f) {
	    --lastv;
	    i__ -= *incv;
	}
	if (applyleft) {
/*     Scan for the last non-zero column in C(1:lastv,:). */
	    lastc = ilaslc_(&lastv, n, &c__[c_offset], ldc);
	} else {
/*     Scan for the last non-zero row in C(:,1:lastv). */
	    lastc = ilaslr_(m, &lastv, &c__[c_offset], ldc);
	}
    }
/*
       Note that lastc.eq.0 renders the BLAS operations null; no special
       case is needed at this level.
*/
    if (applyleft) {

/*        Form  H * C */

	if (lastv > 0) {

/*           w(1:lastc,1) := C(1:lastv,1:lastc)' * v(1:lastv,1) */

	    sgemv_("Transpose", &lastv, &lastc, &c_b15, &c__[c_offset], ldc, &
		    v[1], incv, &c_b29, &work[1], &c__1);

/*           C(1:lastv,1:lastc) := C(...) - v(1:lastv,1) * w(1:lastc,1)' */

	    r__1 = -(*tau);
	    sger_(&lastv, &lastc, &r__1, &v[1], incv, &work[1], &c__1, &c__[
		    c_offset], ldc);
	}
    } else {

/*        Form  C * H */

	if (lastv > 0) {

/*           w(1:lastc,1) := C(1:lastc,1:lastv) * v(1:lastv,1) */

	    sgemv_("No transpose", &lastc, &lastv, &c_b15, &c__[c_offset],
		    ldc, &v[1], incv, &c_b29, &work[1], &c__1);

/*           C(1:lastc,1:lastv) := C(...) - w(1:lastc,1) * v(1:lastv,1)' */

	    r__1 = -(*tau);
	    sger_(&lastc, &lastv, &r__1, &work[1], &c__1, &v[1], incv, &c__[
		    c_offset], ldc);
	}
    }
    return 0;

/*     End of SLARF */

}