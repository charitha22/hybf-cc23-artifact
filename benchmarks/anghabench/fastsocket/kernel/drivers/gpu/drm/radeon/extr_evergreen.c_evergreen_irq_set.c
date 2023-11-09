#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__* afmt; scalar_t__* hpd; int /*<<< orphan*/ * pflip; scalar_t__* crtc_vblank_int; int /*<<< orphan*/ * ring_int; int /*<<< orphan*/  installed; } ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct radeon_device {scalar_t__ family; int num_crtc; TYPE_1__ irq; TYPE_2__ ih; } ;

/* Variables and functions */
 scalar_t__ AFMT_AUDIO_PACKET_CONTROL ; 
 int AFMT_AZ_FORMAT_WTRIG_MASK ; 
 scalar_t__ CAYMAN_DMA1_CNTL ; 
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 scalar_t__ CHIP_CAYMAN ; 
 int CNTX_BUSY_INT_ENABLE ; 
 int CNTX_EMPTY_INT_ENABLE ; 
 scalar_t__ CP_INT_CNTL ; 
 scalar_t__ DC_HPD1_INT_CONTROL ; 
 scalar_t__ DC_HPD2_INT_CONTROL ; 
 scalar_t__ DC_HPD3_INT_CONTROL ; 
 scalar_t__ DC_HPD4_INT_CONTROL ; 
 scalar_t__ DC_HPD5_INT_CONTROL ; 
 scalar_t__ DC_HPD6_INT_CONTROL ; 
 int DC_HPDx_INT_EN ; 
 scalar_t__ DMA_CNTL ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 scalar_t__ GRBM_INT_CNTL ; 
 scalar_t__ GRPH_INT_CONTROL ; 
 scalar_t__ INT_MASK ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RB_INT_ENABLE ; 
 int RREG32 (scalar_t__) ; 
 int TIME_STAMP_INT_ENABLE ; 
 int TRAP_ENABLE ; 
 int VBLANK_INT_MASK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cayman_cp_int_cntl_setup (struct radeon_device*,int,int) ; 
 int /*<<< orphan*/  evergreen_disable_interrupt_state (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_disable_interrupts (struct radeon_device*) ; 

int evergreen_irq_set(struct radeon_device *rdev)
{
	u32 cp_int_cntl = CNTX_BUSY_INT_ENABLE | CNTX_EMPTY_INT_ENABLE;
	u32 cp_int_cntl1 = 0, cp_int_cntl2 = 0;
	u32 crtc1 = 0, crtc2 = 0, crtc3 = 0, crtc4 = 0, crtc5 = 0, crtc6 = 0;
	u32 hpd1, hpd2, hpd3, hpd4, hpd5, hpd6;
	u32 grbm_int_cntl = 0;
	u32 grph1 = 0, grph2 = 0, grph3 = 0, grph4 = 0, grph5 = 0, grph6 = 0;
	u32 afmt1 = 0, afmt2 = 0, afmt3 = 0, afmt4 = 0, afmt5 = 0, afmt6 = 0;
	u32 dma_cntl, dma_cntl1 = 0;

	if (!rdev->irq.installed) {
		WARN(1, "Can't enable IRQ/MSI because no handler is installed\n");
		return -EINVAL;
	}
	/* don't enable anything if the ih is disabled */
	if (!rdev->ih.enabled) {
		r600_disable_interrupts(rdev);
		/* force the active interrupt state to all disabled */
		evergreen_disable_interrupt_state(rdev);
		return 0;
	}

	hpd1 = RREG32(DC_HPD1_INT_CONTROL) & ~DC_HPDx_INT_EN;
	hpd2 = RREG32(DC_HPD2_INT_CONTROL) & ~DC_HPDx_INT_EN;
	hpd3 = RREG32(DC_HPD3_INT_CONTROL) & ~DC_HPDx_INT_EN;
	hpd4 = RREG32(DC_HPD4_INT_CONTROL) & ~DC_HPDx_INT_EN;
	hpd5 = RREG32(DC_HPD5_INT_CONTROL) & ~DC_HPDx_INT_EN;
	hpd6 = RREG32(DC_HPD6_INT_CONTROL) & ~DC_HPDx_INT_EN;

	afmt1 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
	afmt2 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
	afmt3 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
	afmt4 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
	afmt5 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;
	afmt6 = RREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET) & ~AFMT_AZ_FORMAT_WTRIG_MASK;

	dma_cntl = RREG32(DMA_CNTL) & ~TRAP_ENABLE;

	if (rdev->family >= CHIP_CAYMAN) {
		/* enable CP interrupts on all rings */
		if (atomic_read(&rdev->irq.ring_int[RADEON_RING_TYPE_GFX_INDEX])) {
			DRM_DEBUG("evergreen_irq_set: sw int gfx\n");
			cp_int_cntl |= TIME_STAMP_INT_ENABLE;
		}
		if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_CP1_INDEX])) {
			DRM_DEBUG("evergreen_irq_set: sw int cp1\n");
			cp_int_cntl1 |= TIME_STAMP_INT_ENABLE;
		}
		if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_CP2_INDEX])) {
			DRM_DEBUG("evergreen_irq_set: sw int cp2\n");
			cp_int_cntl2 |= TIME_STAMP_INT_ENABLE;
		}
	} else {
		if (atomic_read(&rdev->irq.ring_int[RADEON_RING_TYPE_GFX_INDEX])) {
			DRM_DEBUG("evergreen_irq_set: sw int gfx\n");
			cp_int_cntl |= RB_INT_ENABLE;
			cp_int_cntl |= TIME_STAMP_INT_ENABLE;
		}
	}

	if (atomic_read(&rdev->irq.ring_int[R600_RING_TYPE_DMA_INDEX])) {
		DRM_DEBUG("r600_irq_set: sw int dma\n");
		dma_cntl |= TRAP_ENABLE;
	}

	if (rdev->family >= CHIP_CAYMAN) {
		dma_cntl1 = RREG32(CAYMAN_DMA1_CNTL) & ~TRAP_ENABLE;
		if (atomic_read(&rdev->irq.ring_int[CAYMAN_RING_TYPE_DMA1_INDEX])) {
			DRM_DEBUG("r600_irq_set: sw int dma1\n");
			dma_cntl1 |= TRAP_ENABLE;
		}
	}

	if (rdev->irq.crtc_vblank_int[0] ||
	    atomic_read(&rdev->irq.pflip[0])) {
		DRM_DEBUG("evergreen_irq_set: vblank 0\n");
		crtc1 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[1] ||
	    atomic_read(&rdev->irq.pflip[1])) {
		DRM_DEBUG("evergreen_irq_set: vblank 1\n");
		crtc2 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[2] ||
	    atomic_read(&rdev->irq.pflip[2])) {
		DRM_DEBUG("evergreen_irq_set: vblank 2\n");
		crtc3 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[3] ||
	    atomic_read(&rdev->irq.pflip[3])) {
		DRM_DEBUG("evergreen_irq_set: vblank 3\n");
		crtc4 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[4] ||
	    atomic_read(&rdev->irq.pflip[4])) {
		DRM_DEBUG("evergreen_irq_set: vblank 4\n");
		crtc5 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.crtc_vblank_int[5] ||
	    atomic_read(&rdev->irq.pflip[5])) {
		DRM_DEBUG("evergreen_irq_set: vblank 5\n");
		crtc6 |= VBLANK_INT_MASK;
	}
	if (rdev->irq.hpd[0]) {
		DRM_DEBUG("evergreen_irq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[1]) {
		DRM_DEBUG("evergreen_irq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[2]) {
		DRM_DEBUG("evergreen_irq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[3]) {
		DRM_DEBUG("evergreen_irq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[4]) {
		DRM_DEBUG("evergreen_irq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.hpd[5]) {
		DRM_DEBUG("evergreen_irq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN;
	}
	if (rdev->irq.afmt[0]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 0\n");
		afmt1 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[1]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 1\n");
		afmt2 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[2]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 2\n");
		afmt3 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[3]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 3\n");
		afmt4 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[4]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 4\n");
		afmt5 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}
	if (rdev->irq.afmt[5]) {
		DRM_DEBUG("evergreen_irq_set: hdmi 5\n");
		afmt6 |= AFMT_AZ_FORMAT_WTRIG_MASK;
	}

	if (rdev->family >= CHIP_CAYMAN) {
		cayman_cp_int_cntl_setup(rdev, 0, cp_int_cntl);
		cayman_cp_int_cntl_setup(rdev, 1, cp_int_cntl1);
		cayman_cp_int_cntl_setup(rdev, 2, cp_int_cntl2);
	} else
		WREG32(CP_INT_CNTL, cp_int_cntl);

	WREG32(DMA_CNTL, dma_cntl);

	if (rdev->family >= CHIP_CAYMAN)
		WREG32(CAYMAN_DMA1_CNTL, dma_cntl1);

	WREG32(GRBM_INT_CNTL, grbm_int_cntl);

	WREG32(INT_MASK + EVERGREEN_CRTC0_REGISTER_OFFSET, crtc1);
	WREG32(INT_MASK + EVERGREEN_CRTC1_REGISTER_OFFSET, crtc2);
	if (rdev->num_crtc >= 4) {
		WREG32(INT_MASK + EVERGREEN_CRTC2_REGISTER_OFFSET, crtc3);
		WREG32(INT_MASK + EVERGREEN_CRTC3_REGISTER_OFFSET, crtc4);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(INT_MASK + EVERGREEN_CRTC4_REGISTER_OFFSET, crtc5);
		WREG32(INT_MASK + EVERGREEN_CRTC5_REGISTER_OFFSET, crtc6);
	}

	WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET, grph1);
	WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET, grph2);
	if (rdev->num_crtc >= 4) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET, grph3);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET, grph4);
	}
	if (rdev->num_crtc >= 6) {
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET, grph5);
		WREG32(GRPH_INT_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET, grph6);
	}

	WREG32(DC_HPD1_INT_CONTROL, hpd1);
	WREG32(DC_HPD2_INT_CONTROL, hpd2);
	WREG32(DC_HPD3_INT_CONTROL, hpd3);
	WREG32(DC_HPD4_INT_CONTROL, hpd4);
	WREG32(DC_HPD5_INT_CONTROL, hpd5);
	WREG32(DC_HPD6_INT_CONTROL, hpd6);

	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC0_REGISTER_OFFSET, afmt1);
	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC1_REGISTER_OFFSET, afmt2);
	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC2_REGISTER_OFFSET, afmt3);
	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC3_REGISTER_OFFSET, afmt4);
	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC4_REGISTER_OFFSET, afmt5);
	WREG32(AFMT_AUDIO_PACKET_CONTROL + EVERGREEN_CRTC5_REGISTER_OFFSET, afmt6);

	return 0;
}