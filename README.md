# Enable live audio for DJI FPV Goggles/AU 
Enables the live audio transmission from Airunit to Goggles.

Will not work simultaneously with msp-osd.

Currently working only with Goggles V1 and the standard Airunit that has an integrated microphone. Will not work with Caddx Vista.

## Installation

Install enable-live-audio:
- `opkg install enable-live-audio`


Or manually:
- `make ipk`
- adb push ...
- `opkg install "package-name"`


## Usage

Live audio will auto start on boot or when the AU is restarted after switching batteries. It can take up to 30s after powering on the goggles and about 15s when restarting the AU.

Audio volume can be set:
- by playing back a video that doesn't contain any audio and adjust the volume with the goggles joystick up/down commands.
- manually with `setprop persist.dji.volume.headphone 6` with persistent values from 1-6.


## Known bugs

- This feature is not compatible with msp-osd(https://github.com/bri3d/msp-osd) since it relies on the dji_glasses service being enabled.
- When liveview audio is started videos containing audio can't be played back.
