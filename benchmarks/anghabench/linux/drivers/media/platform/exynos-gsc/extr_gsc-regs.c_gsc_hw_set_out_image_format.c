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
typedef  size_t u32 ;
struct gsc_frame {TYPE_1__* fmt; } ;
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_ctx {scalar_t__ out_path; struct gsc_frame d_frame; struct gsc_dev* gsc_dev; } ;
struct TYPE_2__ {size_t num_planes; int num_comp; int /*<<< orphan*/  corder; int /*<<< orphan*/  yorder; scalar_t__* depth; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSC_CBCR ; 
 scalar_t__ GSC_DMA ; 
 int /*<<< orphan*/  GSC_LSB_Y ; 
 size_t GSC_OUT_CHROMA_ORDER_CBCR ; 
 size_t GSC_OUT_CHROMA_ORDER_CRCB ; 
 size_t GSC_OUT_CHROMA_ORDER_MASK ; 
 scalar_t__ GSC_OUT_CON ; 
 size_t GSC_OUT_FORMAT_MASK ; 
 size_t GSC_OUT_RGB_TYPE_MASK ; 
 size_t GSC_OUT_TILE_C_16x8 ; 
 size_t GSC_OUT_TILE_MODE ; 
 size_t GSC_OUT_TILE_TYPE_MASK ; 
 size_t GSC_OUT_YUV420_2P ; 
 size_t GSC_OUT_YUV420_3P ; 
 size_t GSC_OUT_YUV422_1P ; 
 size_t GSC_OUT_YUV422_1P_OEDER_LSB_C ; 
 size_t GSC_OUT_YUV422_1P_ORDER_LSB_Y ; 
 size_t GSC_OUT_YUV422_1P_ORDER_MASK ; 
 size_t GSC_OUT_YUV422_2P ; 
 size_t GSC_OUT_YUV444 ; 
 int /*<<< orphan*/  gsc_hw_set_out_image_rgb (struct gsc_ctx*) ; 
 scalar_t__ is_rgb (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tiled (TYPE_1__*) ; 
 size_t readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

void gsc_hw_set_out_image_format(struct gsc_ctx *ctx)
{
	struct gsc_dev *dev = ctx->gsc_dev;
	struct gsc_frame *frame = &ctx->d_frame;
	u32 i, depth = 0;
	u32 cfg;

	cfg = readl(dev->regs + GSC_OUT_CON);
	cfg &= ~(GSC_OUT_RGB_TYPE_MASK | GSC_OUT_YUV422_1P_ORDER_MASK |
		 GSC_OUT_CHROMA_ORDER_MASK | GSC_OUT_FORMAT_MASK |
		 GSC_OUT_TILE_TYPE_MASK | GSC_OUT_TILE_MODE);
	writel(cfg, dev->regs + GSC_OUT_CON);

	if (is_rgb(frame->fmt->color)) {
		gsc_hw_set_out_image_rgb(ctx);
		return;
	}

	if (ctx->out_path != GSC_DMA) {
		cfg |= GSC_OUT_YUV444;
		goto end_set;
	}

	for (i = 0; i < frame->fmt->num_planes; i++)
		depth += frame->fmt->depth[i];

	switch (frame->fmt->num_comp) {
	case 1:
		cfg |= GSC_OUT_YUV422_1P;
		if (frame->fmt->yorder == GSC_LSB_Y)
			cfg |= GSC_OUT_YUV422_1P_ORDER_LSB_Y;
		else
			cfg |= GSC_OUT_YUV422_1P_OEDER_LSB_C;
		if (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_OUT_CHROMA_ORDER_CBCR;
		else
			cfg |= GSC_OUT_CHROMA_ORDER_CRCB;
		break;
	case 2:
		if (depth == 12)
			cfg |= GSC_OUT_YUV420_2P;
		else
			cfg |= GSC_OUT_YUV422_2P;
		if (frame->fmt->corder == GSC_CBCR)
			cfg |= GSC_OUT_CHROMA_ORDER_CBCR;
		else
			cfg |= GSC_OUT_CHROMA_ORDER_CRCB;
		break;
	case 3:
		cfg |= GSC_OUT_YUV420_3P;
		break;
	}

	if (is_tiled(frame->fmt))
		cfg |= GSC_OUT_TILE_C_16x8 | GSC_OUT_TILE_MODE;

end_set:
	writel(cfg, dev->regs + GSC_OUT_CON);
}