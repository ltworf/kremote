kremote
=======

It provides a way to use remote controllers with KDE4's players Amarok and
Kaffine.

It has a modular architecture composed of several binaries specialized to
handle one kind of device and one binary to gather the data and relay the
commands to the players.

Usage
=====

```bash
$ kremote.py -D "command line to the device handler"
```

Device handlers
===============

- HTTP
This provides a web interface for a remote, intended to be used with a mobile
phone or similar device.

- Apple
![ScreenShot](https://raw.github.com/ltworf/kremote/master/doc/apple.jpg)

The file apple.h needs to be edited with the right constants because currently
it can work only with my remote

- Creative
![ScreenShot](https://raw.github.com/ltworf/kremote/master/doc/creative.jpg)
