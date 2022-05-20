#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>

int32_t setAudioLiveViewEnable (void* this, bool param_1, bool param_2) {

    int32_t *gs_gui_config = (int32_t *)*(int32_t *)(this + 0xe4);
    int32_t *gs_info = (int32_t *)*(int32_t *)(gs_gui_config + (0x4c / 4));
    
    static int32_t (*gs_enable_audio_liveview)(void *_gs_info, bool b_enable) = 0;
    gs_enable_audio_liveview = (void *)*(int32_t *)(gs_gui_config + (0x3e0 / 4));  //fptr @gs_gui_config + 0x3e0

    gs_enable_audio_liveview(gs_info, param_1);
    
    return 0;
    
}

int32_t _ZN17GlassUserSettings15performSettingsEv (void* this) {
    static int32_t (*real_perform_settings)(void *this) = 0;
    
    void *guiLib = dlopen("/system/lib/libtp1801_gui.so",1);
    
    printf("Hooked GlassUserSettings::performSettings!\n");
    
    if (! real_perform_settings) {
        real_perform_settings = dlsym (guiLib, "_ZN17GlassUserSettings15performSettingsEv");
        if (real_perform_settings == 0)
        {
            printf("dlsym: %s\n", dlerror());
            return 0;
        }
    }

    int32_t ret = 0;
    printf("Calling original GlassUserSettings::performSettings\n");
    ret = real_perform_settings(this);
    printf("Calling custom setAudioLiveViewEnable\n");
    setAudioLiveViewEnable(this, true, false);

    return ret;
    
}
