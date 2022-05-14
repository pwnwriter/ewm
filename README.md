# ewm ( Elite optimised* Window Manager )
Summary
-------
ewm is a very simple and lightweight tiling window manager.
I will try to stay under 8000 SLOC.

<a href="https://raw.githubusercontent.com/Iyamnabeen/ewm/main/Ouu/ouu.jpg"><img src="https://raw.githubusercontent.com/Iyamnabeen/ewm/main/Ouu/ouu.jpg" width="43%" align="right"></a>

Features
-------
- Floating only.
- Fullscreen toggle.
- Window centering.
- Mix of mouse and keyboard workflow.
- Focus with cursor.

 <a href="https://raw.githubusercontent.com/Iyamnabeen/ewm/main/Ouu/ouu.jpg"><img src="https://raw.githubusercontent.com/Iyamnabeen/ewm/main/Ouu/ok.jpg" width="43%" align="right"></a>

- Alt-Tab window focusing.
- All windows die on exit.
- No window borders.
- [No ICCCM](https://web.archive.org/web/20190617214524/https://raw.githubusercontent.com/kfish/xsel/1a1c5edf0dc129055f7764c666da2dd468df6016/rant.txt).
- No EWMH.
- etc etc etc

Default Keybindings
-------

| combo                      | action                  |
| -------------------------- | ------------------------|
| `Mouse`                    | focus under cursor      |
| `MOD4` + `Left Mouse`      | move window             |
| `MOD4` + `Right Mouse`     | resize window           |
| `MOD4` + `f`               | maximize toggle         |
| `MOD4` + `r`               | resize window(touchpads)|
| `MOD4` + `x`               | center window           |
| `MOD4` + `c`               | kill window             |
| `MOD4` + `1-6`             | desktop swap            |
| `MOD4` + `Shift` +`1-6`    | send window to desktop  |
| `MOD1` + `TAB` (*alt-tab*) | focus cycle             |

Aditional programs 
-------------------


| combo                    | action           | program        |
| ------------------------ | ---------------- | -------------- |
| `MOD4` + `Return`        | terminal         | `st`           |
| `MOD4` + `space`         | dmenu            | `dmenu_run`    |
| `MOD4` + `p`             | maim             | `maim`         |
| `XF86_AudioLowerVolume`  | volume down      | `amixer`       |
| `XF86_AudioRaiseVolume`  | volume up        | `amixer`       |
| `XF86_AudioMute`         | volume toggle    | `amixer`       |
| `XF86_MonBrightnessUp`   | brightness up    | `light`        |
| `XF86_MonBrightnessDown` | brightness down  | `light`        |




Installation
------------

Need Xlib, then:
    `$ make`
    `# make clean install`

Bugs
----
 * No bugs for the moment ;) ( left, You tell me 🙆‍♂️ ;)


Thanks
------

 * [The suckless team](http://suckless.org/)
 * [Dylanaraps](https://github.com/dylanaraps)
 * [Mrsafalpiya](https://github.com/mrsafalpiya)

