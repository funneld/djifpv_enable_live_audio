# Enable live audio for DJI FPV Goggles/AU 
Enables the live audio transmission from Airunit to Goggles.

## Installation

Install wtfos-modloader

`opkg install wtfos-modloader`

Install enable-live-audio
`opkg install enable-live-audio`


or manually
`make ipk`
adb push ...
`opkg install "package-name"`


## Usage

After the liveview audio code is started the goggles make a short beep indicating live audio has started. Another short beep after the AU is disconnected indicates the liveview audio code stopped.

Audio volume can be set:
- by playing back a video that doesn't contain any audio and adjust the volume with the goggles joystick up/down commands. 0 volume disables the live audio code.
- manually with `setprop persist.dji.volume.headphone 6` with persistent values from 1-6. 0 disables the live audio code.



##Known bugs

- When liveview audio is started videos containing audio can't be played back.
- The glasses GUI will restart if signal is totally lost. Doesn't have any bad effect on the live video feed.
