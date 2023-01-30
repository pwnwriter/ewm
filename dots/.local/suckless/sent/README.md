# My build of Sent v1

### Slide:
![](https://i.postimg.cc/Z5GhP4v1/screenshot-20210520-019.png)

### Slide with inverted colors:
![](https://i.postimg.cc/pdKMq4Dy/screenshot-20210520-020.png)

This repository hosts the source code of my build of *Sent* made by [Suckless software](http://tools.suckless.org/sent/). It is based on *Sent* v1 and different patches have been applied in order to provide the features I like. The list applied patches can be found in the *patches* folder. It features:

* It is possible to invert colors for a dark theme (2 patches for this)
* A custom font (with colors) can be set for all slides
* Progress bar at the bottom

# Dependencies
The following packages are necessary in order to run this build of Sent properly:

* farbfeld (to display images)
* libxft (or libxft-bgra)

# Installation
Basically, just clone this repository (or download it), compile the build and install it. Type the following commands:

```
git clone --depth 1 https://github.com/astsu777/sent.git
cd sent
sudo make clean install
```

# Usage
*Sent* can be used simply by launching *sent <presentation_file>*. This program is using text files for slides. An example presentation is available in this repo: check the file called *example*. Additional arguments can be passed when running *sent*:

```
usage: sent [-c fgcolor] [-b bgcolor] [-f font] -i [file]
```

The *-i* argument inverts the color to set a dark theme at launch. It is also possible to invert colors during a presentation by pressing the *i* key.

## Slides
Although the *example* file is self-explanatory, here are a few notes on how to make slides:

* Each paragraph in a text file represents a single slide. The size of the text is automatically scaled to fill up the slide
* Every space and tab is literally rendered in a slide
* An image will always be on a single slide without any texts. An image slide is made by typing *@<image_file>* in a paragraph. Any text in the same paragraph will not be displayed in the presentation
* Unicode characters are literally displayed
* Comments can be set by beginning a line with a *#* character. These are not displayed in slides. The rest of the text in the same paragraph will be displayed on the slide
* The *\\* characters exits special characters so they are displayed literally
* An empty slide can be inserted by a single paragraph containing just *\\*

Images are displayed using *farbfeld*. Images with transparent backgrounds are supported.

# Key Bindings
I configured the key bindings that I like. They are all configured in the *config.def.h* file. Here is the full list and what they actually do:

| Key binding | Action |
| :--- | :--- |
| `Right Arrow / l / j / n / Return / Space / Left Mouse Click` | goes to next slide |
| `Left Arrow / h / k / p / Backspace / Middle Mouse Click` | goes to previous slide |
| `i` | inverts color |
| `r` | reloads presentation file (=refresh) |
| `Escape / q` | quits *sent* |

# Contact
You can always reach out to me:

* [Twitter](https://twitter.com/astsu777)
* [Email](mailto:gaetan@ictpourtous.com)
