#!/system/bin/sh

audio_flag=0

while [ true ]
do
    liveview_flag=`busybox devmem 0xfffc1106 16`
    headphone_volume=`getprop persist.dji.volume.headphone`

    if [[ ($liveview_flag != '0x0000' && $audio_flag -eq 0 && $headphone_volume -gt 0) ]]; then
        # echo "Liveview on"
        audio_flag=1
        modmanager disable diy_glasses enable_live_audio
        sleep 1
        printf '\x00' | busybox dd of=/blackbox/glass_user_setting.dat bs=1 seek=157 count=1 conv=notrunc
        sleep 1
        modmanager enable diy_glasses enable_live_audio
        test_pwm 0 2600 50 1 1
        sleep 0.25
        test_pwm 0 2600 50 1 0
    else
        # echo "Liveview off"
        if [[ ($liveview_flag == '0x0000' && $audio_flag -eq 1 && $headphone_volume -gt 0) ]]; then
            # echo "disabled"
            audio_flag=0
            test_pwm 0 2600 50 1 1
            sleep 0.25
            test_pwm 0 2600 50 1 0
        fi
    fi

sleep 1

done
