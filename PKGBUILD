# Maintainer: iyamnabeen 
# gmail:  <iym.nabeen@gmail.com>
# github: <github.com/iyamnabeen>

pkgname=ewm
pkgver=1
pkgrel=0
pkgdesc="Less bloated dwm "
url="https://github.com/iyamnabeen/ewm"
arch=('any')
license=('GPL3')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 
)
conflicts=('ewm')
provides=("${pkgname}")
options=(!strip !emptydirs)
install="${pkgname}.install"

prepare() {
	cp -af ../ewm/. ${srcdir}
}

build() {
  cd "$srcdir"
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd "$srcdir"
  make PREFIX=/usr DESTDIR="$pkgdir" install


}
