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
typedef  int uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  idx; struct amdgpu_device* adev; } ;
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int amdgpu_emu_mode ; 
 int /*<<< orphan*/  amdgpu_gfx_scratch_free (struct amdgpu_device*,int) ; 
 int amdgpu_gfx_scratch_get (struct amdgpu_device*,int*) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v10_0_ring_test_ring(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t scratch;
	uint32_t tmp = 0;
	unsigned i;
	int r;

	r = amdgpu_gfx_scratch_get(adev, &scratch);
	if (r) {
		DRM_ERROR("amdgpu: cp failed to get scratch reg (%d).\n", r);
		return r;
	}

	WREG32(scratch, 0xCAFEDEAD);

	r = amdgpu_ring_alloc(ring, 3);
	if (r) {
		DRM_ERROR("amdgpu: cp failed to lock ring %d (%d).\n",
			  ring->idx, r);
		amdgpu_gfx_scratch_free(adev, scratch);
		return r;
	}

	amdgpu_ring_write(ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
	amdgpu_ring_write(ring, (scratch - PACKET3_SET_UCONFIG_REG_START));
	amdgpu_ring_write(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF)
			break;
		if (amdgpu_emu_mode == 1)
			msleep(1);
		else
			udelay(1);
	}
	if (i < adev->usec_timeout) {
		if (amdgpu_emu_mode == 1)
			DRM_INFO("ring test on %d succeeded in %d msecs\n",
				 ring->idx, i);
		else
			DRM_INFO("ring test on %d succeeded in %d usecs\n",
				 ring->idx, i);
	} else {
		DRM_ERROR("amdgpu: ring %d test failed (scratch(0x%04X)=0x%08X)\n",
			  ring->idx, scratch, tmp);
		r = -EINVAL;
	}
	amdgpu_gfx_scratch_free(adev, scratch);

	return r;
}