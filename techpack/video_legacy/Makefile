# SPDX-License-Identifier: GPL-2.0-only
# auto-detect subdirs
ifeq ($(CONFIG_ARCH_SDM845), y)
include $(srctree)/techpack/video_legacy/config/sdm845.conf
LINUXINCLUDE    += -include $(srctree)/techpack/video_legacy/config/sdm845.h

LINUXINCLUDE    += -I$(srctree)/techpack/video_legacy/include \
                   -I$(srctree)/techpack/video_legacy/include/uapi

USERINCLUDE     += -I$(srctree)/techpack/video_legacy/include/uapi

obj-y +=msm/
endif
