
Debian
====================
This directory contains files used to package bambood/bamboo-qt
for Debian-based Linux systems. If you compile bambood/bamboo-qt yourself, there are some useful files here.

## bamboo: URI support ##


bamboo-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bamboo-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bambooqt binary to `/usr/bin`
and the `../../share/pixmaps/bamboo128.png` to `/usr/share/pixmaps`

bamboo-qt.protocol (KDE)

