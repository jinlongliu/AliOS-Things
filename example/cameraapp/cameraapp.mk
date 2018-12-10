NAME := cameraapp

$(NAME)_SOURCES := cameraapp.c

GLOBAL_DEFINES += AOS_NO_WIFI CONFIG_AOS_FATFS_SUPPORT_MMC

$(NAME)_COMPONENTS := yloop cli kernel.modules.fs.fatfs board.developerkit.camera_hal info_a

ifeq ($(BENCHMARKS),1)
$(NAME)_COMPONENTS  += benchmarks
GLOBAL_DEFINES      += CONFIG_CMD_BENCHMARKS
endif

