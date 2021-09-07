# AfwBasedAudioHal

audio framework based audio hal with audio hal helper

# External dependency & expected path

| component | github url | expected path |
| :--- | :--- | :--- |
| audio framework | https://github.com/hidenorly/audioframework | ~/work/audioframework |
| Android Hal Helper | https://github.com/hidenorly/AndroidAudioHalHelper | ~/work/AndroidAudioHalHelper |


Note that this AfwBasedAudioHal is expected to be synced at ~/work/AfwBasedAudioHal

# Tentative way to execute for debugging

For a standalone buildable and executable:

```
$ ln -s /Users/xxx/work/audioframework/lib /Users/xxx/work/AfwBasedAudioHal
$ ln -s /Users/xxx/work/AndroidAudioHalHelper/lib/libaudiohalhelper.dylib /Users/xxx/work/AfwBasedAudioHal/lib
```

For permanent solution will be changed for actual hal implementation:

