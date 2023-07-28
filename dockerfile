FROM joshwyant/gcc-cross

RUN apt update && apt upgrade -y
RUN apt install cmake qemu-system xorriso git -y