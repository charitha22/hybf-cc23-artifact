#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ CullFaceMode; } ;
struct TYPE_7__ {int /*<<< orphan*/  NewState; TYPE_1__ Polygon; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_BACK ; 
 scalar_t__ GL_FRONT ; 
 scalar_t__ GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NEW_POLYGON ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void gl_CullFace( GLcontext *ctx, GLenum mode )
{
   if (mode!=GL_FRONT && mode!=GL_BACK && mode!=GL_FRONT_AND_BACK) {
      gl_error( ctx, GL_INVALID_ENUM, "glCullFace" );
      return;
   }
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glCullFace" );
      return;
   }
   ctx->Polygon.CullFaceMode = mode;
   ctx->NewState |= NEW_POLYGON;
}