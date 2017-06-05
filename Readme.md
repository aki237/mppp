# mppp
the portable mp3 player

## Compiling

What you need :
 
 - GNU Compiler Collection - gcc (`g++`)
 - autotools - make, coreutils, etc.,
 - python
 - `ninja` build system

+ Clone the source

```sh
$ git clone https://github.com/aki237/mppp
```

+ Download and build the dependancies using the included python script (`build`).

```sh
$ ./build deps
Fetching alsa-lib.tar.gz
Fetching mpg123.tar.bz2
Fetching portaudio.tar.gz
Building alsa-lib
Building mpg123
Building portaudio
$ ls lib/
total 14M
-rw-r--r-- 1 you you  11M Jun  5 05:45 libasound.a
-rw-r--r-- 1 you you 1.8M Jun  5 05:45 libmpg123.a
-rw-r--r-- 1 you you 1.1M Jun  5 05:45 libportaudio.a
```

+ Build the source :

```sh
# Either ninja
$ ninja -j 8 # number of jobs
# or
$ ./build mppp
```

You'll have a `mppp` binary in the root directory.
All the dependancies are basic stuff like :
```sh
$ ldd ./mppp
	linux-vdso.so.1 (0x00007fff8cf85000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f1bf3f1a000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f1bf3d16000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f1bf398e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f1bf3685000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f1bf346e000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f1bf30a6000)
	/lib64/ld-linux-x86-64.so.2 (0x0000561ee88f5000)
```
