FROM debian:stable

RUN apt-get update && apt-get install -y \
    build-essential \
    bison \
    flex \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo \
    xorriso \
    grub-pc-bin \
    mtools \
    wget

WORKDIR /opt

RUN wget https://flatassembler.net/fasm-1.73.32.tgz \
    && tar -xf fasm-1.73.32.tgz \
    && rm fasm-1.73.32.tgz \
    && chmod +x /opt/fasm/fasm \
    && ln -s /opt/fasm/fasm /usr/local/bin/fasm


WORKDIR /src

# Run by urself
# docker run --rm -v "$(pwd -W):/src" learn-os-dev sh -c "gcc nob.c -o nob && ./nob"
