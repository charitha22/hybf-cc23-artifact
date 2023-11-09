; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -slp-vectorizer -mtriple=x86_64--                 -S | FileCheck %s
; RUN: opt < %s -slp-vectorizer -mtriple=x86_64-- -mattr=avx512vl -S | FileCheck %s

declare void @use1(i1)

define i1 @logical_and_icmp(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp(
; CHECK-NEXT:    [[TMP1:%.*]] = icmp slt <4 x i32> [[X:%.*]], zeroinitializer
; CHECK-NEXT:    [[TMP2:%.*]] = freeze <4 x i1> [[TMP1]]
; CHECK-NEXT:    [[TMP3:%.*]] = call i1 @llvm.vector.reduce.and.v4i1(<4 x i1> [[TMP2]])
; CHECK-NEXT:    ret i1 [[TMP3]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 0
  %c1 = icmp slt i32 %x1, 0
  %c2 = icmp slt i32 %x2, 0
  %c3 = icmp slt i32 %x3, 0
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  ret i1 %s3
}

define i1 @logical_or_icmp(<4 x i32> %x, <4 x i32> %y) {
; CHECK-LABEL: @logical_or_icmp(
; CHECK-NEXT:    [[TMP1:%.*]] = icmp slt <4 x i32> [[X:%.*]], [[Y:%.*]]
; CHECK-NEXT:    [[TMP2:%.*]] = freeze <4 x i1> [[TMP1]]
; CHECK-NEXT:    [[TMP3:%.*]] = call i1 @llvm.vector.reduce.or.v4i1(<4 x i1> [[TMP2]])
; CHECK-NEXT:    ret i1 [[TMP3]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %y0 = extractelement <4 x i32> %y, i32 0
  %y1 = extractelement <4 x i32> %y, i32 1
  %y2 = extractelement <4 x i32> %y, i32 2
  %y3 = extractelement <4 x i32> %y, i32 3
  %c0 = icmp slt i32 %x0, %y0
  %c1 = icmp slt i32 %x1, %y1
  %c2 = icmp slt i32 %x2, %y2
  %c3 = icmp slt i32 %x3, %y3
  %s1 = select i1 %c0, i1 true, i1 %c1
  %s2 = select i1 %s1, i1 true, i1 %c2
  %s3 = select i1 %s2, i1 true, i1 %c3
  ret i1 %s3
}

define i1 @logical_and_fcmp(<4 x float> %x) {
; CHECK-LABEL: @logical_and_fcmp(
; CHECK-NEXT:    [[TMP1:%.*]] = fcmp olt <4 x float> [[X:%.*]], zeroinitializer
; CHECK-NEXT:    [[TMP2:%.*]] = freeze <4 x i1> [[TMP1]]
; CHECK-NEXT:    [[TMP3:%.*]] = call i1 @llvm.vector.reduce.and.v4i1(<4 x i1> [[TMP2]])
; CHECK-NEXT:    ret i1 [[TMP3]]
;
  %x0 = extractelement <4 x float> %x, i32 0
  %x1 = extractelement <4 x float> %x, i32 1
  %x2 = extractelement <4 x float> %x, i32 2
  %x3 = extractelement <4 x float> %x, i32 3
  %c0 = fcmp olt float %x0, 0.0
  %c1 = fcmp olt float %x1, 0.0
  %c2 = fcmp olt float %x2, 0.0
  %c3 = fcmp olt float %x3, 0.0
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  ret i1 %s3
}

define i1 @logical_or_fcmp(<4 x float> %x) {
; CHECK-LABEL: @logical_or_fcmp(
; CHECK-NEXT:    [[TMP1:%.*]] = fcmp olt <4 x float> [[X:%.*]], zeroinitializer
; CHECK-NEXT:    [[TMP2:%.*]] = freeze <4 x i1> [[TMP1]]
; CHECK-NEXT:    [[TMP3:%.*]] = call i1 @llvm.vector.reduce.or.v4i1(<4 x i1> [[TMP2]])
; CHECK-NEXT:    ret i1 [[TMP3]]
;
  %x0 = extractelement <4 x float> %x, i32 0
  %x1 = extractelement <4 x float> %x, i32 1
  %x2 = extractelement <4 x float> %x, i32 2
  %x3 = extractelement <4 x float> %x, i32 3
  %c0 = fcmp olt float %x0, 0.0
  %c1 = fcmp olt float %x1, 0.0
  %c2 = fcmp olt float %x2, 0.0
  %c3 = fcmp olt float %x3, 0.0
  %s1 = select i1 %c0, i1 true, i1 %c1
  %s2 = select i1 %s1, i1 true, i1 %c2
  %s3 = select i1 %s2, i1 true, i1 %c3
  ret i1 %s3
}

define i1 @logical_and_icmp_diff_preds(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_diff_preds(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp ult i32 [[X0]], 0
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 0
; CHECK-NEXT:    [[C2:%.*]] = icmp sgt i32 [[X2]], 0
; CHECK-NEXT:    [[C3:%.*]] = icmp slt i32 [[X3]], 0
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    [[S3:%.*]] = select i1 [[S2]], i1 [[C3]], i1 false
; CHECK-NEXT:    ret i1 [[S3]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp ult i32 %x0, 0
  %c1 = icmp slt i32 %x1, 0
  %c2 = icmp sgt i32 %x2, 0
  %c3 = icmp slt i32 %x3, 0
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  ret i1 %s3
}

define i1 @logical_and_icmp_diff_const(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_diff_const(
; CHECK-NEXT:    [[TMP1:%.*]] = icmp sgt <4 x i32> [[X:%.*]], <i32 0, i32 1, i32 2, i32 3>
; CHECK-NEXT:    [[TMP2:%.*]] = freeze <4 x i1> [[TMP1]]
; CHECK-NEXT:    [[TMP3:%.*]] = call i1 @llvm.vector.reduce.and.v4i1(<4 x i1> [[TMP2]])
; CHECK-NEXT:    ret i1 [[TMP3]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp sgt i32 %x0, 0
  %c1 = icmp sgt i32 %x1, 1
  %c2 = icmp sgt i32 %x2, 2
  %c3 = icmp sgt i32 %x3, 3
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  ret i1 %s3
}

define i1 @mixed_logical_icmp(<4 x i32> %x) {
; CHECK-LABEL: @mixed_logical_icmp(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp sgt i32 [[X0]], 0
; CHECK-NEXT:    [[C1:%.*]] = icmp sgt i32 [[X1]], 0
; CHECK-NEXT:    [[C2:%.*]] = icmp sgt i32 [[X2]], 0
; CHECK-NEXT:    [[C3:%.*]] = icmp sgt i32 [[X3]], 0
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 true, i1 [[C2]]
; CHECK-NEXT:    [[S3:%.*]] = select i1 [[S2]], i1 [[C3]], i1 false
; CHECK-NEXT:    ret i1 [[S3]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp sgt i32 %x0, 0
  %c1 = icmp sgt i32 %x1, 0
  %c2 = icmp sgt i32 %x2, 0
  %c3 = icmp sgt i32 %x3, 0
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 true, i1 %c2
  %s3 = select i1 %s2, i1 %c3, i1 false
  ret i1 %s3
}

define i1 @logical_and_icmp_subvec(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_subvec(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[C0:%.*]] = icmp slt i32 [[X0]], 0
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 0
; CHECK-NEXT:    [[C2:%.*]] = icmp slt i32 [[X2]], 0
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    ret i1 [[S2]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %c0 = icmp slt i32 %x0, 0
  %c1 = icmp slt i32 %x1, 0
  %c2 = icmp slt i32 %x2, 0
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  ret i1 %s2
}

; TODO: This is better than all-scalar and still safe,
;       but we want this to be 2 reductions with glue
;       logic...or a wide reduction?

define i1 @logical_and_icmp_clamp(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_clamp(
; CHECK-NEXT:    [[TMP1:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 3
; CHECK-NEXT:    [[TMP2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[TMP3:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[TMP4:%.*]] = extractelement <4 x i32> [[X]], i32 0
; CHECK-NEXT:    [[TMP5:%.*]] = icmp slt <4 x i32> [[X]], <i32 42, i32 42, i32 42, i32 42>
; CHECK-NEXT:    [[D0:%.*]] = icmp sgt i32 [[TMP4]], 17
; CHECK-NEXT:    [[D1:%.*]] = icmp sgt i32 [[TMP3]], 17
; CHECK-NEXT:    [[D2:%.*]] = icmp sgt i32 [[TMP2]], 17
; CHECK-NEXT:    [[D3:%.*]] = icmp sgt i32 [[TMP1]], 17
; CHECK-NEXT:    [[TMP6:%.*]] = freeze <4 x i1> [[TMP5]]
; CHECK-NEXT:    [[TMP7:%.*]] = call i1 @llvm.vector.reduce.and.v4i1(<4 x i1> [[TMP6]])
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[TMP7]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  %c3 = icmp slt i32 %x3, 42
  %d0 = icmp sgt i32 %x0, 17
  %d1 = icmp sgt i32 %x1, 17
  %d2 = icmp sgt i32 %x2, 17
  %d3 = icmp sgt i32 %x3, 17
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  %s4 = select i1 %s3, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}

define i1 @logical_and_icmp_clamp_extra_use_cmp(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_clamp_extra_use_cmp(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp slt i32 [[X0]], 42
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 42
; CHECK-NEXT:    [[C2:%.*]] = icmp slt i32 [[X2]], 42
; CHECK-NEXT:    call void @use1(i1 [[C2]])
; CHECK-NEXT:    [[C3:%.*]] = icmp slt i32 [[X3]], 42
; CHECK-NEXT:    [[D0:%.*]] = icmp sgt i32 [[X0]], 17
; CHECK-NEXT:    [[D1:%.*]] = icmp sgt i32 [[X1]], 17
; CHECK-NEXT:    [[D2:%.*]] = icmp sgt i32 [[X2]], 17
; CHECK-NEXT:    [[D3:%.*]] = icmp sgt i32 [[X3]], 17
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    [[S3:%.*]] = select i1 [[S2]], i1 [[C3]], i1 false
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[S3]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  call void @use1(i1 %c2)
  %c3 = icmp slt i32 %x3, 42
  %d0 = icmp sgt i32 %x0, 17
  %d1 = icmp sgt i32 %x1, 17
  %d2 = icmp sgt i32 %x2, 17
  %d3 = icmp sgt i32 %x3, 17
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  %s4 = select i1 %s3, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}

define i1 @logical_and_icmp_clamp_extra_use_select(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_clamp_extra_use_select(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp slt i32 [[X0]], 42
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 42
; CHECK-NEXT:    [[C2:%.*]] = icmp slt i32 [[X2]], 42
; CHECK-NEXT:    [[C3:%.*]] = icmp slt i32 [[X3]], 42
; CHECK-NEXT:    [[D0:%.*]] = icmp sgt i32 [[X0]], 17
; CHECK-NEXT:    [[D1:%.*]] = icmp sgt i32 [[X1]], 17
; CHECK-NEXT:    [[D2:%.*]] = icmp sgt i32 [[X2]], 17
; CHECK-NEXT:    [[D3:%.*]] = icmp sgt i32 [[X3]], 17
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    call void @use1(i1 [[S2]])
; CHECK-NEXT:    [[S3:%.*]] = select i1 [[S2]], i1 [[C3]], i1 false
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[S3]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  %c3 = icmp slt i32 %x3, 42
  %d0 = icmp sgt i32 %x0, 17
  %d1 = icmp sgt i32 %x1, 17
  %d2 = icmp sgt i32 %x2, 17
  %d3 = icmp sgt i32 %x3, 17
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  call void @use1(i1 %s2)
  %s3 = select i1 %s2, i1 %c3, i1 false
  %s4 = select i1 %s3, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}

define i1 @logical_and_icmp_clamp_v8i32(<8 x i32> %x, <8 x i32> %y) {
; CHECK-LABEL: @logical_and_icmp_clamp_v8i32(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <8 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <8 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <8 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <8 x i32> [[X]], i32 3
; CHECK-NEXT:    [[Y0:%.*]] = extractelement <8 x i32> [[Y:%.*]], i32 0
; CHECK-NEXT:    [[Y1:%.*]] = extractelement <8 x i32> [[Y]], i32 1
; CHECK-NEXT:    [[Y2:%.*]] = extractelement <8 x i32> [[Y]], i32 2
; CHECK-NEXT:    [[Y3:%.*]] = extractelement <8 x i32> [[Y]], i32 3
; CHECK-NEXT:    [[TMP1:%.*]] = insertelement <4 x i32> poison, i32 [[X0]], i32 0
; CHECK-NEXT:    [[TMP2:%.*]] = insertelement <4 x i32> [[TMP1]], i32 [[X1]], i32 1
; CHECK-NEXT:    [[TMP3:%.*]] = insertelement <4 x i32> [[TMP2]], i32 [[X2]], i32 2
; CHECK-NEXT:    [[TMP4:%.*]] = insertelement <4 x i32> [[TMP3]], i32 [[X3]], i32 3
; CHECK-NEXT:    [[TMP5:%.*]] = icmp slt <4 x i32> [[TMP4]], <i32 42, i32 42, i32 42, i32 42>
; CHECK-NEXT:    [[D0:%.*]] = icmp slt i32 [[X0]], [[Y0]]
; CHECK-NEXT:    [[D1:%.*]] = icmp slt i32 [[X1]], [[Y1]]
; CHECK-NEXT:    [[D2:%.*]] = icmp slt i32 [[X2]], [[Y2]]
; CHECK-NEXT:    [[D3:%.*]] = icmp slt i32 [[X3]], [[Y3]]
; CHECK-NEXT:    [[TMP6:%.*]] = freeze <4 x i1> [[TMP5]]
; CHECK-NEXT:    [[TMP7:%.*]] = call i1 @llvm.vector.reduce.and.v4i1(<4 x i1> [[TMP6]])
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[TMP7]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <8 x i32> %x, i32 0
  %x1 = extractelement <8 x i32> %x, i32 1
  %x2 = extractelement <8 x i32> %x, i32 2
  %x3 = extractelement <8 x i32> %x, i32 3
  %y0 = extractelement <8 x i32> %y, i32 0
  %y1 = extractelement <8 x i32> %y, i32 1
  %y2 = extractelement <8 x i32> %y, i32 2
  %y3 = extractelement <8 x i32> %y, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  %c3 = icmp slt i32 %x3, 42
  %d0 = icmp slt i32 %x0, %y0
  %d1 = icmp slt i32 %x1, %y1
  %d2 = icmp slt i32 %x2, %y2
  %d3 = icmp slt i32 %x3, %y3
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  %s4 = select i1 %s3, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}

define i1 @logical_and_icmp_clamp_partial(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_clamp_partial(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp slt i32 [[X0]], 42
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 42
; CHECK-NEXT:    [[C2:%.*]] = icmp slt i32 [[X2]], 42
; CHECK-NEXT:    [[D0:%.*]] = icmp sgt i32 [[X0]], 17
; CHECK-NEXT:    [[D1:%.*]] = icmp sgt i32 [[X1]], 17
; CHECK-NEXT:    [[D2:%.*]] = icmp sgt i32 [[X2]], 17
; CHECK-NEXT:    [[D3:%.*]] = icmp sgt i32 [[X3]], 17
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[S2]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  ; remove an element from the previous test
  %d0 = icmp sgt i32 %x0, 17
  %d1 = icmp sgt i32 %x1, 17
  %d2 = icmp sgt i32 %x2, 17
  %d3 = icmp sgt i32 %x3, 17
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  ; remove an element from the previous test
  %s4 = select i1 %s2, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}

define i1 @logical_and_icmp_clamp_pred_diff(<4 x i32> %x) {
; CHECK-LABEL: @logical_and_icmp_clamp_pred_diff(
; CHECK-NEXT:    [[X0:%.*]] = extractelement <4 x i32> [[X:%.*]], i32 0
; CHECK-NEXT:    [[X1:%.*]] = extractelement <4 x i32> [[X]], i32 1
; CHECK-NEXT:    [[X2:%.*]] = extractelement <4 x i32> [[X]], i32 2
; CHECK-NEXT:    [[X3:%.*]] = extractelement <4 x i32> [[X]], i32 3
; CHECK-NEXT:    [[C0:%.*]] = icmp slt i32 [[X0]], 42
; CHECK-NEXT:    [[C1:%.*]] = icmp slt i32 [[X1]], 42
; CHECK-NEXT:    [[C2:%.*]] = icmp slt i32 [[X2]], 42
; CHECK-NEXT:    [[C3:%.*]] = icmp ult i32 [[X3]], 42
; CHECK-NEXT:    [[D0:%.*]] = icmp sgt i32 [[X0]], 17
; CHECK-NEXT:    [[D1:%.*]] = icmp sgt i32 [[X1]], 17
; CHECK-NEXT:    [[D2:%.*]] = icmp sgt i32 [[X2]], 17
; CHECK-NEXT:    [[D3:%.*]] = icmp sgt i32 [[X3]], 17
; CHECK-NEXT:    [[S1:%.*]] = select i1 [[C0]], i1 [[C1]], i1 false
; CHECK-NEXT:    [[S2:%.*]] = select i1 [[S1]], i1 [[C2]], i1 false
; CHECK-NEXT:    [[S3:%.*]] = select i1 [[S2]], i1 [[C3]], i1 false
; CHECK-NEXT:    [[S4:%.*]] = select i1 [[S3]], i1 [[D0]], i1 false
; CHECK-NEXT:    [[S5:%.*]] = select i1 [[S4]], i1 [[D1]], i1 false
; CHECK-NEXT:    [[S6:%.*]] = select i1 [[S5]], i1 [[D2]], i1 false
; CHECK-NEXT:    [[S7:%.*]] = select i1 [[S6]], i1 [[D3]], i1 false
; CHECK-NEXT:    ret i1 [[S7]]
;
  %x0 = extractelement <4 x i32> %x, i32 0
  %x1 = extractelement <4 x i32> %x, i32 1
  %x2 = extractelement <4 x i32> %x, i32 2
  %x3 = extractelement <4 x i32> %x, i32 3
  %c0 = icmp slt i32 %x0, 42
  %c1 = icmp slt i32 %x1, 42
  %c2 = icmp slt i32 %x2, 42
  %c3 = icmp ult i32 %x3, 42 ; predicate changed
  %d0 = icmp sgt i32 %x0, 17
  %d1 = icmp sgt i32 %x1, 17
  %d2 = icmp sgt i32 %x2, 17
  %d3 = icmp sgt i32 %x3, 17
  %s1 = select i1 %c0, i1 %c1, i1 false
  %s2 = select i1 %s1, i1 %c2, i1 false
  %s3 = select i1 %s2, i1 %c3, i1 false
  %s4 = select i1 %s3, i1 %d0, i1 false
  %s5 = select i1 %s4, i1 %d1, i1 false
  %s6 = select i1 %s5, i1 %d2, i1 false
  %s7 = select i1 %s6, i1 %d3, i1 false
  ret i1 %s7
}