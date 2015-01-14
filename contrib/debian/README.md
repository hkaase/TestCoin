
Debian
====================
This directory contains files used to package Testcoind/Testcoin-qt
for Debian-based Linux systems. If you compile Testcoind/Testcoin-qt yourself, there are some useful files here.

## Testcoin: URI support ##


Testcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Testcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Testcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/Testcoin128.png` to `/usr/share/pixmaps`

Testcoin-qt.protocol (KDE)

