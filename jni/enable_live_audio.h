
typedef enum gs_link_stat_t {
    GS_LINK_STAT_NORMAL=0,
    GS_LINK_STAT_WEAK=1,
    GS_LINK_STAT_LOST=2,
    GS_LINK_STAT_UKNOWN=3
} gs_link_stat_t;

static bool restart_lv_audio = false;
static int32_t (* gs_modem_get_link_state_wrap)(void *, enum gs_link_stat_t *) = 0;
static uint32_t (* timeOut)(void *this) = 0;
static uint32_t (* getInstance)() = 0;
