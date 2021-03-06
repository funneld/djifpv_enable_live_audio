#include <time.h>

typedef enum gs_link_stat_t {
    GS_LINK_STAT_NORMAL=0,
    GS_LINK_STAT_WEAK=1,
    GS_LINK_STAT_LOST=2,
    GS_LINK_STAT_UKNOWN=3
} gs_link_stat_t;

static void *guiLib = 0;
static bool restart_lv_audio = false;
static int32_t (* gs_modem_get_link_state_wrap)(void *, enum gs_link_stat_t *) = 0;
static uint32_t (* timeOut)(void *this) = 0;
static uint32_t (* getInstance)() = 0;
struct timespec start, now;
static uint32_t (*gs_enable_audio_liveview)(void *_gs_info, bool b_enable) = 0;
static uint32_t (*gs_get_uav_hardware_version)(void *_gs_info, char *_hw_ver) = 0;
bool is_fpv_lite(void *gs_info);
bool fpv_lite = true;
