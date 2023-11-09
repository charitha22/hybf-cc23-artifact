#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int NameStackDepth; void** NameStack; scalar_t__ HitFlag; } ;
struct TYPE_8__ {scalar_t__ RenderMode; TYPE_1__ Select; } ;
typedef  void* GLuint ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 scalar_t__ GL_SELECT ; 
 scalar_t__ INSIDE_BEGIN_END (TYPE_2__*) ; 
 int MAX_NAME_STACK_DEPTH ; 
 int /*<<< orphan*/  gl_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_hit_record (TYPE_2__*) ; 

void gl_LoadName( GLcontext *ctx, GLuint name )
{
   if (INSIDE_BEGIN_END(ctx)) {
      gl_error( ctx, GL_INVALID_OPERATION, "glLoadName" );
      return;
   }
   if (ctx->RenderMode!=GL_SELECT) {
      return;
   }
   if (ctx->Select.NameStackDepth==0) {
      gl_error( ctx, GL_INVALID_OPERATION, "glLoadName" );
      return;
   }
   if (ctx->Select.HitFlag) {
      write_hit_record( ctx );
   }
   if (ctx->Select.NameStackDepth<MAX_NAME_STACK_DEPTH) {
      ctx->Select.NameStack[ctx->Select.NameStackDepth-1] = name;
   }
   else {
      ctx->Select.NameStack[MAX_NAME_STACK_DEPTH-1] = name;
   }
}