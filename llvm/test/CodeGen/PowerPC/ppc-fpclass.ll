; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=powerpcle-unknown-linux-gnu -verify-machineinstrs -o - %s | FileCheck %s


define i1 @isnan_float(float %x) nounwind {
; CHECK-LABEL: isnan_float:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:    fcmpu 0, 1, 1
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 3, .LBB0_1
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB0_1: # %entry
; CHECK-NEXT:    addi 3, 4, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.f32(float %x)
  ret i1 %0
}

define i1 @isnan_double(double %x) nounwind {
; CHECK-LABEL: isnan_double:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:    fcmpu 0, 1, 1
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 3, .LBB1_1
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB1_1: # %entry
; CHECK-NEXT:    addi 3, 4, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.f64(double %x)
  ret i1 %0
}

define i1 @isnan_ldouble(ppc_fp128 %x) nounwind {
; CHECK-LABEL: isnan_ldouble:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -32(1)
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 4, 20(1)
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    lwz 5, 28(1)
; CHECK-NEXT:    cmplw 1, 4, 3
; CHECK-NEXT:    lwz 3, 24(1)
; CHECK-NEXT:    xoris 4, 4, 32752
; CHECK-NEXT:    lwz 6, 16(1)
; CHECK-NEXT:    clrlwi. 5, 5, 1
; CHECK-NEXT:    cmplwi 5, 5, 0
; CHECK-NEXT:    crandc 24, 1, 22
; CHECK-NEXT:    cmpwi 3, 0
; CHECK-NEXT:    crandc 20, 22, 2
; CHECK-NEXT:    cmpwi 6, 0
; CHECK-NEXT:    cmplwi 7, 4, 0
; CHECK-NEXT:    or 3, 3, 5
; CHECK-NEXT:    crandc 21, 5, 30
; CHECK-NEXT:    crandc 22, 30, 2
; CHECK-NEXT:    cmplwi 3, 0
; CHECK-NEXT:    cror 20, 20, 24
; CHECK-NEXT:    cror 21, 22, 21
; CHECK-NEXT:    crandc 20, 20, 2
; CHECK-NEXT:    crand 21, 2, 21
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    li 3, 1
; CHECK-NEXT:    bc 12, 20, .LBB2_1
; CHECK-NEXT:    b .LBB2_2
; CHECK-NEXT:  .LBB2_1: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB2_2: # %entry
; CHECK-NEXT:    addi 1, 1, 32
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.ppcf128(ppc_fp128 %x)
  ret i1 %0
}


define i1 @isnan_float_strictfp(float %x) strictfp nounwind {
; CHECK-LABEL: isnan_float_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -16(1)
; CHECK-NEXT:    stfs 1, 12(1)
; CHECK-NEXT:    lis 3, 32640
; CHECK-NEXT:    lwz 4, 12(1)
; CHECK-NEXT:    clrlwi 4, 4, 1
; CHECK-NEXT:    cmpw 4, 3
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 1, .LBB3_1
; CHECK-NEXT:    b .LBB3_2
; CHECK-NEXT:  .LBB3_1: # %entry
; CHECK-NEXT:    addi 3, 4, 0
; CHECK-NEXT:  .LBB3_2: # %entry
; CHECK-NEXT:    addi 1, 1, 16
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.f32(float %x)
  ret i1 %0
}

define i1 @isnan_double_strictfp(double %x) strictfp nounwind {
; CHECK-LABEL: isnan_double_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -16(1)
; CHECK-NEXT:    stfd 1, 8(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 4, 12(1)
; CHECK-NEXT:    lwz 5, 8(1)
; CHECK-NEXT:    clrlwi 4, 4, 1
; CHECK-NEXT:    cmpw 4, 3
; CHECK-NEXT:    xoris 3, 4, 32752
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    crandc 20, 1, 6
; CHECK-NEXT:    cmpwi 5, 0
; CHECK-NEXT:    crandc 21, 6, 2
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    li 3, 1
; CHECK-NEXT:    bc 12, 20, .LBB4_1
; CHECK-NEXT:    b .LBB4_2
; CHECK-NEXT:  .LBB4_1: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB4_2: # %entry
; CHECK-NEXT:    addi 1, 1, 16
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.f64(double %x)
  ret i1 %0
}

define i1 @isnan_ldouble_strictfp(ppc_fp128 %x) strictfp nounwind {
; CHECK-LABEL: isnan_ldouble_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -32(1)
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 4, 20(1)
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    lwz 5, 28(1)
; CHECK-NEXT:    cmplw 1, 4, 3
; CHECK-NEXT:    lwz 3, 24(1)
; CHECK-NEXT:    xoris 4, 4, 32752
; CHECK-NEXT:    lwz 6, 16(1)
; CHECK-NEXT:    clrlwi. 5, 5, 1
; CHECK-NEXT:    cmplwi 5, 5, 0
; CHECK-NEXT:    crandc 24, 1, 22
; CHECK-NEXT:    cmpwi 3, 0
; CHECK-NEXT:    crandc 20, 22, 2
; CHECK-NEXT:    cmpwi 6, 0
; CHECK-NEXT:    cmplwi 7, 4, 0
; CHECK-NEXT:    or 3, 3, 5
; CHECK-NEXT:    crandc 21, 5, 30
; CHECK-NEXT:    crandc 22, 30, 2
; CHECK-NEXT:    cmplwi 3, 0
; CHECK-NEXT:    cror 20, 20, 24
; CHECK-NEXT:    cror 21, 22, 21
; CHECK-NEXT:    crandc 20, 20, 2
; CHECK-NEXT:    crand 21, 2, 21
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    li 3, 1
; CHECK-NEXT:    bc 12, 20, .LBB5_1
; CHECK-NEXT:    b .LBB5_2
; CHECK-NEXT:  .LBB5_1: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB5_2: # %entry
; CHECK-NEXT:    addi 1, 1, 32
; CHECK-NEXT:    blr
entry:
  %0 = tail call i1 @llvm.isnan.ppcf128(ppc_fp128 %x)
  ret i1 %0
}


define <1 x i1> @isnan_float_vec1(<1 x float> %x) nounwind {
; CHECK-LABEL: isnan_float_vec1:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:    fcmpu 0, 1, 1
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 3, .LBB6_1
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB6_1: # %entry
; CHECK-NEXT:    addi 3, 4, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call <1 x i1> @llvm.isnan.v1f32(<1 x float> %x)
  ret <1 x i1> %0
}

define <1 x i1> @isnan_double_vec1(<1 x double> %x) nounwind {
; CHECK-LABEL: isnan_double_vec1:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:    fcmpu 0, 1, 1
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 3, .LBB7_1
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB7_1: # %entry
; CHECK-NEXT:    addi 3, 4, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call <1 x i1> @llvm.isnan.v1f64(<1 x double> %x)
  ret <1 x i1> %0
}

define <1 x i1> @isnan_ldouble_vec1(<1 x ppc_fp128> %x) nounwind {
; CHECK-LABEL: isnan_ldouble_vec1:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -32(1)
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 4, 20(1)
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    lwz 5, 28(1)
; CHECK-NEXT:    cmplw 1, 4, 3
; CHECK-NEXT:    lwz 3, 24(1)
; CHECK-NEXT:    xoris 4, 4, 32752
; CHECK-NEXT:    lwz 6, 16(1)
; CHECK-NEXT:    clrlwi. 5, 5, 1
; CHECK-NEXT:    cmplwi 5, 5, 0
; CHECK-NEXT:    crandc 24, 1, 22
; CHECK-NEXT:    cmpwi 3, 0
; CHECK-NEXT:    crandc 20, 22, 2
; CHECK-NEXT:    cmpwi 6, 0
; CHECK-NEXT:    cmplwi 7, 4, 0
; CHECK-NEXT:    or 3, 3, 5
; CHECK-NEXT:    crandc 21, 5, 30
; CHECK-NEXT:    crandc 22, 30, 2
; CHECK-NEXT:    cmplwi 3, 0
; CHECK-NEXT:    cror 20, 20, 24
; CHECK-NEXT:    cror 21, 22, 21
; CHECK-NEXT:    crandc 20, 20, 2
; CHECK-NEXT:    crand 21, 2, 21
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    li 3, 1
; CHECK-NEXT:    bc 12, 20, .LBB8_1
; CHECK-NEXT:    b .LBB8_2
; CHECK-NEXT:  .LBB8_1: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB8_2: # %entry
; CHECK-NEXT:    addi 1, 1, 32
; CHECK-NEXT:    blr
entry:
  %0 = tail call <1 x i1> @llvm.isnan.v1ppcf128(<1 x ppc_fp128> %x)
  ret <1 x i1> %0
}


define <2 x i1> @isnan_float_vec2(<2 x float> %x) nounwind {
; CHECK-LABEL: isnan_float_vec2:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:    fcmpu 0, 2, 2
; CHECK-NEXT:    fcmpu 1, 1, 1
; CHECK-NEXT:    li 5, 1
; CHECK-NEXT:    bc 12, 7, .LBB9_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB9_3
; CHECK-NEXT:  .LBB9_2: # %entry
; CHECK-NEXT:    addi 3, 5, 0
; CHECK-NEXT:  .LBB9_3: # %entry
; CHECK-NEXT:    bc 12, 3, .LBB9_4
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB9_4: # %entry
; CHECK-NEXT:    addi 4, 5, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2f32(<2 x float> %x)
  ret <2 x i1> %0
}

define <2 x i1> @isnan_double_vec2(<2 x double> %x) nounwind {
; CHECK-LABEL: isnan_double_vec2:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:    fcmpu 0, 2, 2
; CHECK-NEXT:    fcmpu 1, 1, 1
; CHECK-NEXT:    li 5, 1
; CHECK-NEXT:    bc 12, 7, .LBB10_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB10_3
; CHECK-NEXT:  .LBB10_2: # %entry
; CHECK-NEXT:    addi 3, 5, 0
; CHECK-NEXT:  .LBB10_3: # %entry
; CHECK-NEXT:    bc 12, 3, .LBB10_4
; CHECK-NEXT:    blr
; CHECK-NEXT:  .LBB10_4: # %entry
; CHECK-NEXT:    addi 4, 5, 0
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2f64(<2 x double> %x)
  ret <2 x i1> %0
}

define <2 x i1> @isnan_ldouble_vec2(<2 x ppc_fp128> %x) nounwind {
; CHECK-LABEL: isnan_ldouble_vec2:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -48(1)
; CHECK-NEXT:    stfd 3, 32(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 8, 32(1)
; CHECK-NEXT:    stfd 4, 40(1)
; CHECK-NEXT:    lwz 9, 44(1)
; CHECK-NEXT:    cmpwi 1, 8, 0
; CHECK-NEXT:    lwz 10, 36(1)
; CHECK-NEXT:    lwz 8, 40(1)
; CHECK-NEXT:    clrlwi. 9, 9, 1
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    cmplwi 5, 9, 0
; CHECK-NEXT:    lwz 5, 20(1)
; CHECK-NEXT:    crandc 24, 1, 22
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    cmpwi 8, 0
; CHECK-NEXT:    lwz 4, 16(1)
; CHECK-NEXT:    cmplw 7, 10, 3
; CHECK-NEXT:    lwz 7, 28(1)
; CHECK-NEXT:    xoris 10, 10, 32752
; CHECK-NEXT:    crandc 20, 22, 2
; CHECK-NEXT:    cmplwi 10, 0
; CHECK-NEXT:    lwz 6, 24(1)
; CHECK-NEXT:    crandc 21, 29, 2
; CHECK-NEXT:    cmplw 7, 5, 3
; CHECK-NEXT:    xoris 3, 5, 32752
; CHECK-NEXT:    crandc 22, 2, 6
; CHECK-NEXT:    cmplwi 3, 0
; CHECK-NEXT:    cmpwi 1, 4, 0
; CHECK-NEXT:    crandc 23, 29, 2
; CHECK-NEXT:    crandc 25, 2, 6
; CHECK-NEXT:    clrlwi. 3, 7, 1
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    crandc 26, 1, 6
; CHECK-NEXT:    cmpwi 6, 0
; CHECK-NEXT:    or 4, 8, 9
; CHECK-NEXT:    crandc 27, 6, 2
; CHECK-NEXT:    cmplwi 4, 0
; CHECK-NEXT:    or 3, 6, 3
; CHECK-NEXT:    cror 20, 20, 24
; CHECK-NEXT:    cror 21, 22, 21
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    cror 22, 25, 23
; CHECK-NEXT:    crandc 20, 20, 2
; CHECK-NEXT:    crand 21, 2, 21
; CHECK-NEXT:    cror 23, 27, 26
; CHECK-NEXT:    crand 22, 6, 22
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    crandc 21, 23, 6
; CHECK-NEXT:    crnor 21, 22, 21
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 21, .LBB11_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB11_3
; CHECK-NEXT:  .LBB11_2: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB11_3: # %entry
; CHECK-NEXT:    bc 12, 20, .LBB11_4
; CHECK-NEXT:    b .LBB11_5
; CHECK-NEXT:  .LBB11_4: # %entry
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:  .LBB11_5: # %entry
; CHECK-NEXT:    addi 1, 1, 48
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2ppcf128(<2 x ppc_fp128> %x)
  ret <2 x i1> %0
}


define <2 x i1> @isnan_float_vec2_strictfp(<2 x float> %x) strictfp nounwind {
; CHECK-LABEL: isnan_float_vec2_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -16(1)
; CHECK-NEXT:    stfs 1, 8(1)
; CHECK-NEXT:    lis 3, 32640
; CHECK-NEXT:    stfs 2, 12(1)
; CHECK-NEXT:    lwz 4, 12(1)
; CHECK-NEXT:    lwz 5, 8(1)
; CHECK-NEXT:    clrlwi 4, 4, 1
; CHECK-NEXT:    cmpw 4, 3
; CHECK-NEXT:    clrlwi 5, 5, 1
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:    cmpw 1, 5, 3
; CHECK-NEXT:    li 5, 1
; CHECK-NEXT:    bc 12, 5, .LBB12_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB12_3
; CHECK-NEXT:  .LBB12_2: # %entry
; CHECK-NEXT:    addi 3, 5, 0
; CHECK-NEXT:  .LBB12_3: # %entry
; CHECK-NEXT:    bc 12, 1, .LBB12_4
; CHECK-NEXT:    b .LBB12_5
; CHECK-NEXT:  .LBB12_4: # %entry
; CHECK-NEXT:    addi 4, 5, 0
; CHECK-NEXT:  .LBB12_5: # %entry
; CHECK-NEXT:    addi 1, 1, 16
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2f32(<2 x float> %x)
  ret <2 x i1> %0
}

define <2 x i1> @isnan_double_vec2_strictfp(<2 x double> %x) strictfp nounwind {
; CHECK-LABEL: isnan_double_vec2_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -32(1)
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 5, 28(1)
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    lwz 6, 20(1)
; CHECK-NEXT:    clrlwi 5, 5, 1
; CHECK-NEXT:    lwz 7, 24(1)
; CHECK-NEXT:    cmpw 5, 3
; CHECK-NEXT:    xoris 5, 5, 32752
; CHECK-NEXT:    lwz 4, 16(1)
; CHECK-NEXT:    cmplwi 1, 5, 0
; CHECK-NEXT:    crandc 20, 1, 6
; CHECK-NEXT:    cmpwi 7, 0
; CHECK-NEXT:    clrlwi 5, 6, 1
; CHECK-NEXT:    crandc 21, 6, 2
; CHECK-NEXT:    cmpw 5, 3
; CHECK-NEXT:    xoris 3, 5, 32752
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    crandc 22, 1, 6
; CHECK-NEXT:    cmpwi 4, 0
; CHECK-NEXT:    crandc 23, 6, 2
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    crnor 21, 23, 22
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 21, .LBB13_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB13_3
; CHECK-NEXT:  .LBB13_2: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB13_3: # %entry
; CHECK-NEXT:    bc 12, 20, .LBB13_4
; CHECK-NEXT:    b .LBB13_5
; CHECK-NEXT:  .LBB13_4: # %entry
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:  .LBB13_5: # %entry
; CHECK-NEXT:    addi 1, 1, 32
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2f64(<2 x double> %x)
  ret <2 x i1> %0
}

define <2 x i1> @isnan_ldouble_vec2_strictfp(<2 x ppc_fp128> %x) strictfp nounwind {
; CHECK-LABEL: isnan_ldouble_vec2_strictfp:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    stwu 1, -48(1)
; CHECK-NEXT:    stfd 3, 32(1)
; CHECK-NEXT:    lis 3, 32752
; CHECK-NEXT:    lwz 8, 32(1)
; CHECK-NEXT:    stfd 4, 40(1)
; CHECK-NEXT:    lwz 9, 44(1)
; CHECK-NEXT:    cmpwi 1, 8, 0
; CHECK-NEXT:    lwz 10, 36(1)
; CHECK-NEXT:    lwz 8, 40(1)
; CHECK-NEXT:    clrlwi. 9, 9, 1
; CHECK-NEXT:    stfd 1, 16(1)
; CHECK-NEXT:    cmplwi 5, 9, 0
; CHECK-NEXT:    lwz 5, 20(1)
; CHECK-NEXT:    crandc 24, 1, 22
; CHECK-NEXT:    stfd 2, 24(1)
; CHECK-NEXT:    cmpwi 8, 0
; CHECK-NEXT:    lwz 4, 16(1)
; CHECK-NEXT:    cmplw 7, 10, 3
; CHECK-NEXT:    lwz 7, 28(1)
; CHECK-NEXT:    xoris 10, 10, 32752
; CHECK-NEXT:    crandc 20, 22, 2
; CHECK-NEXT:    cmplwi 10, 0
; CHECK-NEXT:    lwz 6, 24(1)
; CHECK-NEXT:    crandc 21, 29, 2
; CHECK-NEXT:    cmplw 7, 5, 3
; CHECK-NEXT:    xoris 3, 5, 32752
; CHECK-NEXT:    crandc 22, 2, 6
; CHECK-NEXT:    cmplwi 3, 0
; CHECK-NEXT:    cmpwi 1, 4, 0
; CHECK-NEXT:    crandc 23, 29, 2
; CHECK-NEXT:    crandc 25, 2, 6
; CHECK-NEXT:    clrlwi. 3, 7, 1
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    crandc 26, 1, 6
; CHECK-NEXT:    cmpwi 6, 0
; CHECK-NEXT:    or 4, 8, 9
; CHECK-NEXT:    crandc 27, 6, 2
; CHECK-NEXT:    cmplwi 4, 0
; CHECK-NEXT:    or 3, 6, 3
; CHECK-NEXT:    cror 20, 20, 24
; CHECK-NEXT:    cror 21, 22, 21
; CHECK-NEXT:    cmplwi 1, 3, 0
; CHECK-NEXT:    cror 22, 25, 23
; CHECK-NEXT:    crandc 20, 20, 2
; CHECK-NEXT:    crand 21, 2, 21
; CHECK-NEXT:    cror 23, 27, 26
; CHECK-NEXT:    crand 22, 6, 22
; CHECK-NEXT:    crnor 20, 21, 20
; CHECK-NEXT:    crandc 21, 23, 6
; CHECK-NEXT:    crnor 21, 22, 21
; CHECK-NEXT:    li 4, 1
; CHECK-NEXT:    bc 12, 21, .LBB14_2
; CHECK-NEXT:  # %bb.1: # %entry
; CHECK-NEXT:    ori 3, 4, 0
; CHECK-NEXT:    b .LBB14_3
; CHECK-NEXT:  .LBB14_2: # %entry
; CHECK-NEXT:    li 3, 0
; CHECK-NEXT:  .LBB14_3: # %entry
; CHECK-NEXT:    bc 12, 20, .LBB14_4
; CHECK-NEXT:    b .LBB14_5
; CHECK-NEXT:  .LBB14_4: # %entry
; CHECK-NEXT:    li 4, 0
; CHECK-NEXT:  .LBB14_5: # %entry
; CHECK-NEXT:    addi 1, 1, 48
; CHECK-NEXT:    blr
entry:
  %0 = tail call <2 x i1> @llvm.isnan.v2ppcf128(<2 x ppc_fp128> %x)
  ret <2 x i1> %0
}


declare i1 @llvm.isnan.f32(float)
declare i1 @llvm.isnan.f64(double)
declare i1 @llvm.isnan.ppcf128(ppc_fp128)
declare <1 x i1> @llvm.isnan.v1f32(<1 x float>)
declare <1 x i1> @llvm.isnan.v1f64(<1 x double>)
declare <1 x i1> @llvm.isnan.v1ppcf128(<1 x ppc_fp128>)
declare <2 x i1> @llvm.isnan.v2f32(<2 x float>)
declare <2 x i1> @llvm.isnan.v2f64(<2 x double>)
declare <2 x i1> @llvm.isnan.v2ppcf128(<2 x ppc_fp128>)
