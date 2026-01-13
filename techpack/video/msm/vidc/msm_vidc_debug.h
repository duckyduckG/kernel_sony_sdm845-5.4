/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MSM_VIDC_DEBUG__
#define __MSM_VIDC_DEBUG__
#include <linux/debugfs.h>
#include <linux/delay.h>
#include "msm_vidc_internal.h"

/* Mock all the missing parts for successful compilation starts here */
#include <linux/types.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <soc/qcom/subsystem_restart.h>
#include "msm_vidc_internal.h"

#define MAX_TRACER_LOG_LENGTH 128

#define trace_msm_vidc_printf(trace_logbuf, log_length) (void) log_length
#define trace_msm_v4l2_vidc_fw_load_start(s)
#define trace_msm_v4l2_vidc_fw_load_end(s)

void trace_msm_v4l2_vidc_open_start(char *s);
void trace_msm_v4l2_vidc_open_end(char *s);
void trace_msm_v4l2_vidc_close_start(char *s);
void trace_msm_v4l2_vidc_close_end(char *s);
void trace_msm_vidc_common_state_change(void*, enum instance_state ins_state, int state);
void trace_msm_smem_buffer_iommu_op_start(char *s, int i, int j, unsigned long k,
										  dma_addr_t iova, unsigned long l);
void trace_msm_smem_buffer_iommu_op_end(char *s, int i, int j, unsigned long k,
										  dma_addr_t iova, unsigned long l);
void trace_msm_smem_buffer_dma_op_start(char *s, u32 buffer_type, unsigned long heap_mask,
										size_t size, u32 align, u32 flags,
										int map_kernel);
void trace_msm_smem_buffer_dma_op_end(char *s, u32 buffer_type, unsigned long heap_mask,
										size_t size, u32 align, u32 flags,
										int map_kernel);
void trace_msm_v4l2_vidc_buffer_counter(char *s, int etb, int ebd, int ftb, int fbd);
void trace_msm_vidc_perf_clock_scale(const char *name, u32 freq);
void trace_venus_hfi_var_done(u32 cp_start, u32 cp_size,
							  u32 cp_nonpixel_start, u32 cp_nonpixel_size);
void trace_msm_v4l2_vidc_buffer_event_start(char *event_type, u32 device_addr,
											int64_t timestamp, u32 alloc_len,
											u32 filled_len, u32 offset);
void trace_msm_v4l2_vidc_buffer_event_end(char *event_type, u32 device_addr,
											int64_t timestamp, u32 alloc_len,
											u32 filled_len, u32 offset);

// void disable_irq_nosync(unsigned int irq);
// void enable_irq(unsigned int irq);

struct msm_bus_client_handle {
	char *name;
	int mas;
	int slv;
	int first_hop;
	// struct device *mas_dev;
	u64 cur_act_ib;
	u64 cur_act_ab;
	u64 cur_dual_ib;
	u64 cur_dual_ab;
	bool active_only;
};

int msm_bus_scale_update_bw(struct msm_bus_client_handle *cl, u64 ab, u64 ib);
int msm_bus_scale_update_bw(struct msm_bus_client_handle *cl, u64 ab, u64 ib);
struct msm_bus_client_handle* msm_bus_scale_register(uint32_t mas, uint32_t slv,
                                                     char *name, bool active_only);
void msm_bus_scale_unregister(struct msm_bus_client_handle *cl);

void do_gettimeofday(struct timeval *__ddl_tv);

#ifndef CONFIG_VIDEOBUF2_CORE
int vb2_reqbufs(struct vb2_queue *q, struct v4l2_requestbuffers *req);
int vb2_qbuf(struct vb2_queue *q, struct media_device *mdev,
			 struct v4l2_buffer *b);
int vb2_dqbuf(struct vb2_queue *q, struct v4l2_buffer *b, bool nonblocking);
int vb2_streamon(struct vb2_queue *q, enum v4l2_buf_type type);
int vb2_streamoff(struct vb2_queue *q, enum v4l2_buf_type type);
int vb2_queue_init(struct vb2_queue *q);
void vb2_buffer_done(struct vb2_buffer *vb, enum vb2_buffer_state state);
#endif

#define SMEM_IMAGE_VERSION_TABLE 469
/* Mock all the missing parts for successful compilation ends */

#ifndef VIDC_DBG_LABEL
#define VIDC_DBG_LABEL "msm_vidc"
#endif

/*
 * This enforces a rate limit: not more than 6 messages
 * in every 1s.
 */

#define VIDC_DBG_SESSION_RATELIMIT_INTERVAL (1 * HZ)
#define VIDC_DBG_SESSION_RATELIMIT_BURST 6

#define VIDC_DBG_TAG VIDC_DBG_LABEL ": %4s: "

/* To enable messages OR these values and
 * echo the result to debugfs file.
 *
 * To enable all messages set debug_level = 0x101F
 */

enum vidc_msg_prio {
	VIDC_ERR  = 0x0001,
	VIDC_WARN = 0x0002,
	VIDC_INFO = 0x0004,
	VIDC_DBG  = 0x0008,
	VIDC_PROF = 0x0010,
	VIDC_PKT  = 0x0020,
	VIDC_FW   = 0x1000,
};

enum vidc_msg_out {
	VIDC_OUT_PRINTK = 0,
};

enum msm_vidc_debugfs_event {
	MSM_VIDC_DEBUGFS_EVENT_ETB,
	MSM_VIDC_DEBUGFS_EVENT_EBD,
	MSM_VIDC_DEBUGFS_EVENT_FTB,
	MSM_VIDC_DEBUGFS_EVENT_FBD,
};

extern int msm_vidc_debug;
extern int msm_vidc_debug_out;
extern int msm_vidc_fw_debug;
extern int msm_vidc_fw_debug_mode;
extern int msm_vidc_fw_low_power_mode;
extern bool msm_vidc_fw_coverage;
extern bool msm_vidc_thermal_mitigation_disabled;
extern int msm_vidc_clock_voting;
extern bool msm_vidc_syscache_disable;

#define dprintk(__level, __fmt, arg...)	\
	do { \
		if (msm_vidc_debug & __level) { \
			if (msm_vidc_debug_out == VIDC_OUT_PRINTK) { \
				pr_info(VIDC_DBG_TAG __fmt, \
					get_debug_level_str(__level),	\
					## arg); \
			} \
		} \
	} while (0)

#define dprintk_ratelimit(__level, __fmt, arg...) \
	do { \
		if (msm_vidc_debug & __level) { \
			if (msm_vidc_debug_out == VIDC_OUT_PRINTK && \
					msm_vidc_check_ratelimit()) { \
				pr_info(VIDC_DBG_TAG __fmt, \
					get_debug_level_str(__level),	\
					## arg); \
			} \
		} \
	} while (0)

#define MSM_VIDC_ERROR(value)					\
	do {	if (value)					\
			dprintk(VIDC_DBG, "BugOn");		\
		BUG_ON(value);					\
	} while (0)


struct dentry *msm_vidc_debugfs_init_drv(void);
struct dentry *msm_vidc_debugfs_init_core(struct msm_vidc_core *core,
		struct dentry *parent);
struct dentry *msm_vidc_debugfs_init_inst(struct msm_vidc_inst *inst,
		struct dentry *parent);
void msm_vidc_debugfs_deinit_inst(struct msm_vidc_inst *inst);
void msm_vidc_debugfs_update(struct msm_vidc_inst *inst,
		enum msm_vidc_debugfs_event e);
int msm_vidc_check_ratelimit(void);

static inline char *get_debug_level_str(int level)
{
	switch (level) {
	case VIDC_ERR:
		return "err";
	case VIDC_WARN:
		return "warn";
	case VIDC_INFO:
		return "info";
	case VIDC_DBG:
		return "dbg";
	case VIDC_PROF:
		return "prof";
	case VIDC_PKT:
		return "pkt";
	case VIDC_FW:
		return "fw";
	default:
		return "???";
	}
}

static inline void tic(struct msm_vidc_inst *i, enum profiling_points p,
				 char *b)
{
	struct timeval __ddl_tv;

	if (!i->debug.pdata[p].name[0])
		memcpy(i->debug.pdata[p].name, b, 64);
	if ((msm_vidc_debug & VIDC_PROF) &&
		i->debug.pdata[p].sampling) {
		do_gettimeofday(&__ddl_tv);
		i->debug.pdata[p].start =
			(__ddl_tv.tv_sec * 1000) + (__ddl_tv.tv_usec / 1000);
			i->debug.pdata[p].sampling = false;
	}
}

static inline void toc(struct msm_vidc_inst *i, enum profiling_points p)
{
	struct timeval __ddl_tv;

	if ((msm_vidc_debug & VIDC_PROF) &&
		!i->debug.pdata[p].sampling) {
		do_gettimeofday(&__ddl_tv);
		i->debug.pdata[p].stop = (__ddl_tv.tv_sec * 1000)
			+ (__ddl_tv.tv_usec / 1000);
		i->debug.pdata[p].cumulative += i->debug.pdata[p].stop -
			i->debug.pdata[p].start;
		i->debug.pdata[p].sampling = true;
	}
}

static inline void show_stats(struct msm_vidc_inst *i)
{
	int x;

	for (x = 0; x < MAX_PROFILING_POINTS; x++) {
		if (i->debug.pdata[x].name[0] &&
				(msm_vidc_debug & VIDC_PROF)) {
			if (i->debug.samples) {
				dprintk(VIDC_PROF, "%s averaged %d ms/sample\n",
						i->debug.pdata[x].name,
						i->debug.pdata[x].cumulative /
						i->debug.samples);
			}

			dprintk(VIDC_PROF, "%s Samples: %d\n",
					i->debug.pdata[x].name,
					i->debug.samples);
		}
	}
}

static inline void msm_vidc_res_handle_fatal_hw_error(
	struct msm_vidc_platform_resources *resources,
	bool enable_fatal)
{
	enable_fatal &= resources->debug_timeout;
	MSM_VIDC_ERROR(enable_fatal);
}

static inline void msm_vidc_handle_hw_error(struct msm_vidc_core *core)
{
	bool enable_fatal = true;

	/*
	 * In current implementation user-initiated SSR triggers
	 * a fatal error from hardware. However, there is no way
	 * to know if fatal error is due to SSR or not. Handle
	 * user SSR as non-fatal.
	 */
	if (core->trigger_ssr) {
		core->trigger_ssr = false;
		enable_fatal = false;
	}

	/* Video driver can decide FATAL handling of HW errors
	 * based on multiple factors. This condition check will
	 * be enhanced later.
	 */
	msm_vidc_res_handle_fatal_hw_error(&core->resources, enable_fatal);
}

#endif
