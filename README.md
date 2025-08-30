# Learn OS

This repository is storing the result of OS development stuff in 32 bit Protected Mode,
it might not efficient, atleast it work.

> [!WARNING]
> Don't Expect that this is good stuff, but it can become good reference point
> Although sometimes I didn't put resources.

## Feature / Roadmap

- [X] Serial Debugging
- [ ] PIT timer
- [ ] PS/2 Keyboard input
- [X] 320x200 linear 256-color mode
- [ ] VGA terminal
- [ ] Paging: allocating pages and mapping them to virtual addresses
- [ ] TTY
- [ ] Scheduler
- [ ] Read/write FAT-32 filesystem
- [ ] Basic UNIX-like syscall for userspace

## Dependency

- [FASM](https://flatassembler.net/)
- [GCC](https://gcc.gnu.org/)
- [QEMU](https://www.qemu.org/)

## Development

The development split into 2 platform: windows and linux, but first clone the repository

```sh
git clone https://github.com/UnknownRori/learn-os
cd learn-os

# Shallow clone the submodule
git submodule update --depth 1
```

### Linux

The build system is not using Makefile but rather by using tsoding [nob.h](https://github.com/tsoding/nob) and you need to bootstrap it by using gcc.

```sh
# Bootstrap the toolchain
gcc nob.c -o nob

# Run the build & Run the QEMU
./nob run
```

### Windows

Same as linux but since windows is not natively support I use docker to allow linux build environment and bootstraping the build system that I mentioned above.

```sh
docker build -t learn-os-dev

docker run --rm -v "$(pwd -W):/src" learn-os-dev sh -c "gcc nob.c -o nob && ./nob"

# Run the ISO image
qemu-system-i386 -cdrom ./build/rori_i386.iso -serial stdio --no-reboot
```

## License

License? What license? this silly OS has license? well I will think about it if this become full blown OS that I can use to write something or just do something productive
