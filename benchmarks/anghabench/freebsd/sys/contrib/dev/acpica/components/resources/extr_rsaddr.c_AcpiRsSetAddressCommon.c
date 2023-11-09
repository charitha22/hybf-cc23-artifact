#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  TypeSpecific; } ;
struct TYPE_12__ {scalar_t__ ResourceType; TYPE_1__ Info; } ;
struct TYPE_13__ {TYPE_2__ Address; } ;
struct TYPE_16__ {TYPE_3__ Data; } ;
struct TYPE_14__ {int /*<<< orphan*/  SpecificFlags; } ;
struct TYPE_15__ {TYPE_4__ Address; } ;
typedef  TYPE_5__ AML_RESOURCE ;
typedef  TYPE_6__ ACPI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ ACPI_IO_RANGE ; 
 scalar_t__ ACPI_MEMORY_RANGE ; 
 int /*<<< orphan*/  AcpiRsConvertGeneralFlags ; 
 int /*<<< orphan*/  AcpiRsConvertIoFlags ; 
 int /*<<< orphan*/  AcpiRsConvertMemFlags ; 
 int /*<<< orphan*/  AcpiRsConvertResourceToAml (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

void
AcpiRsSetAddressCommon (
    AML_RESOURCE            *Aml,
    ACPI_RESOURCE           *Resource)
{
    ACPI_FUNCTION_ENTRY ();


    /* Set the Resource Type and General Flags */

    (void) AcpiRsConvertResourceToAml (
        Resource, Aml, AcpiRsConvertGeneralFlags);

    /* Set the Type-Specific Flags (Memory and I/O descriptors only) */

    if (Resource->Data.Address.ResourceType == ACPI_MEMORY_RANGE)
    {
        (void) AcpiRsConvertResourceToAml (
            Resource, Aml, AcpiRsConvertMemFlags);
    }
    else if (Resource->Data.Address.ResourceType == ACPI_IO_RANGE)
    {
        (void) AcpiRsConvertResourceToAml (
            Resource, Aml, AcpiRsConvertIoFlags);
    }
    else
    {
        /* Generic resource type, just copy the TypeSpecific byte */

        Aml->Address.SpecificFlags =
            Resource->Data.Address.Info.TypeSpecific;
    }
}