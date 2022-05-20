#!/system/bin/sh

beep()
{
    test_pwm 0 2600 50 1 1
    sleep 0.25
    test_pwm 0 2600 50 1 0
}

modmanager_restart_liveaudio()
{
    modmanager disable diy_glasses enable_live_audio
    sleep 4
    modmanager enable diy_glasses enable_live_audio
}


audio_flag=0
disable_flag=0

while [ true ]
do

    headphone_volume=`getprop persist.dji.volume.headphone`

    if [[ ($headphone_volume -eq 0 && $disable_flag -eq 0) ]]; then
        
        modmanager disable diy_glasses enable_live_audio
        disable_flag=1
        audio_flag=0
        
    else if [ $headphone_volume -gt 0 ]; then
        
        disable_flag=0
        liveview_flag=`busybox devmem 0xfffc1106 16`
    
            if [[ ($liveview_flag != '0x0000' && $audio_flag -eq 0) ]]; then
                
                audio_flag=1
                modmanager_restart_liveaudio
                beep
                
            else
                
                if [[ ($liveview_flag == '0x0000' && $audio_flag -eq 1) ]]; then
                
                    audio_flag=0
                    beep
                    
                fi
            fi
        fi
    fi
    
sleep 1

done
