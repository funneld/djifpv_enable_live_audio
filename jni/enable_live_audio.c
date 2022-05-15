#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int32_t _ZN17GlassUserSettings15performSettingsEv (void* this) {

    static int32_t (*real_perform_settings)(void* this) = 0;
    static int32_t (*setAudioLiveViewEnable)(void *this,bool param_1,bool param_2) = 0;
    
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

    if (! setAudioLiveViewEnable) {
        setAudioLiveViewEnable = dlsym (guiLib, "_ZN17GlassUserSettings22setAudioLiveviewEnableEbb");
        if (setAudioLiveViewEnable == 0)
        {
            printf("dlsym: %s\n", dlerror());
            return 0;
        }
    }

    int32_t ret = 0;
    printf("Calling original GlassUserSettings::performSettings\n");
    ret = real_perform_settings(this);
    printf("Calling GlassUserSettings::setAudioLiveViewEnable\n");
    setAudioLiveViewEnable(this, true, false);

    return ret;
    
}
