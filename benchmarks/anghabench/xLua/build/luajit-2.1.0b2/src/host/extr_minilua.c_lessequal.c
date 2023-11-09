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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  TM_LE ; 
 int /*<<< orphan*/  TM_LT ; 
 int call_orderTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ l_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int luaG_ordererror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int luai_numle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int lessequal(lua_State*L,const TValue*l,const TValue*r){
int res;
if(ttype(l)!=ttype(r))
return luaG_ordererror(L,l,r);
else if(ttisnumber(l))
return luai_numle(nvalue(l),nvalue(r));
else if(ttisstring(l))
return l_strcmp(rawtsvalue(l),rawtsvalue(r))<=0;
else if((res=call_orderTM(L,l,r,TM_LE))!=-1)
return res;
else if((res=call_orderTM(L,r,l,TM_LT))!=-1)
return!res;
return luaG_ordererror(L,l,r);
}