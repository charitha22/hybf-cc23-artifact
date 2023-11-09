#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BotFreeCharacterStrings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/ ** botcharacters ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

void BotFreeCharacter2(int handle)
{
	if (handle <= 0 || handle > MAX_CLIENTS)
	{
		botimport.Print(PRT_FATAL, "character handle %d out of range\n", handle);
		return;
	} //end if
	if (!botcharacters[handle])
	{
		botimport.Print(PRT_FATAL, "invalid character %d\n", handle);
		return;
	} //end if
	BotFreeCharacterStrings(botcharacters[handle]);
	FreeMemory(botcharacters[handle]);
	botcharacters[handle] = NULL;
}