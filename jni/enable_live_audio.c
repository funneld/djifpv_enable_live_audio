#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "enable_live_audio.h"


bool is_fpv_lite(void *gs_info){
	char hw_ver[16];
	memset(hw_ver, 0, 0x10);

	gs_get_uav_hardware_version(gs_info, hw_ver);	
	
	int fpv_lite = strncmp(hw_ver,"LT150 VT Ver.A",0x10);
	
	if(fpv_lite == 0)return true;

	return false;
}


int32_t _ZN19GlassRacingChnlMenu7timeOutEv(void* this){

	int32_t ret = 0;

	if (!timeOut && !getInstance){

		timeOut = dlsym (RTLD_NEXT, "_ZN19GlassRacingChnlMenu7timeOutEv");
		if (timeOut == 0){
			guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);
			timeOut = dlsym (guiLib, "_ZN19GlassRacingChnlMenu7timeOutEv");
			if (timeOut == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return 0;
			}
		}

		getInstance = dlsym (RTLD_NEXT, "_ZN17GlassUserSettings11getInstanceEv");
		if (getInstance == 0){
			if(!guiLib){guiLib = dlopen("/system/lib/libtp1801_gui.so", 1);}
			getInstance = dlsym (guiLib, "_ZN17GlassUserSettings11getInstanceEv");
			if (getInstance == 0)
			{
				printf("dlsym: %s\n", dlerror());
				return 0;
			}
		}

	}

	uint32_t inst = getInstance();

	uint32_t *gs_gui_config = (uint32_t *)*(uint32_t *)((int)inst + 0xe4);
	uint32_t *gs_info = (uint32_t *)*(uint32_t *)((int)gs_gui_config + 0x4c);
	gs_get_uav_hardware_version = (void *)*(uint32_t *)((int)gs_gui_config + 0x3a8);
	
	fpv_lite = is_fpv_lite(gs_info);

	if(!fpv_lite){
		gs_modem_get_link_state_wrap = (void *)*(uint32_t *)((int)gs_gui_config + 0x228);
		gs_enable_audio_liveview = (void *)*(uint32_t *)((int)gs_gui_config + 0x3e0);
		
		gs_link_stat_t link = GS_LINK_STAT_UKNOWN;
		gs_link_stat_t *link_state = &link;
		gs_modem_get_link_state_wrap(gs_info, link_state);

		if(link != GS_LINK_STAT_NORMAL){
			clock_gettime(CLOCK_MONOTONIC, &start);
		}

		clock_gettime(CLOCK_MONOTONIC, &now);

		if((link == GS_LINK_STAT_NORMAL) && !restart_lv_audio && ((now.tv_sec - start.tv_sec) > 9)){
			restart_lv_audio = true;
			gs_enable_audio_liveview(gs_info, true);
			printf("setAudioLiveViewEnable ENABLED\n");
		}
		else if((link == GS_LINK_STAT_LOST) && restart_lv_audio){
			restart_lv_audio = false;
			gs_enable_audio_liveview(gs_info, false);
			printf("setAudioLiveViewEnable DISABLED\n");
		}
	}

	ret = timeOut(this);

	return ret;
}
