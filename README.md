# Learn OS

This repository is storing the result of OS development stuff, it might not efficient, cool but atleast it work

> [!WARNING]
> Don't Expect that this is good stuff, but it can become good reference point
> Although sometimes I didn't put resources.

## Dependency

- [FASM](https://flatassembler.net/)
- [GCC](https://gcc.gnu.org/)
- [QEMU](https://www.qemu.org/)

## Development

The development split into 2 platform: windows and linux, but first clone the repository

```sh
git clone https://github.com/UnknownRori/learn-os
```

### Linux

The build system is not using Makefile but rather by using tsoding [nob.h](https://github.com/tsoding/nob) and you need to bootstrap it by using gcc.

```sh
# Bootstrap the toolchain
gcc nob.c -o nob

# Run the build
./nob
```

### Windows

Same as linux but since windows is not natively support I use docker to allow linux build environment and bootstraping the build system that I mentioned above.

```sh
docker build -t learn-os-dev

docker run --rm -v "$(pwd -W):/src" learn-os-dev sh -c "gcc nob.c -o nob && ./nob"
```

## License

License? What license? this silly OS has license? well I will think about it if this become full blown OS that I can use to write something or just do something productive
