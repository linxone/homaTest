This repo is a simple test based on HomaModule.

#### Requirements

HomaModule

#### Run it

1. Insert Homa kernel module

   * kernel version: 5.4.0-89-generic

   `git clone https://github.com/PlatformLab/HomaModule.git`

   `cd HomaModule`

   `make all`

   `sudo insmod homa.ko`

2. make this demo

   `gcc homa_api.c homa-receiver.c -o server`

   `gcc homa_api.c homa-sender.c -o client`

