#!/bin/bash

curl --output compiler.xz https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-a/10.2-2020.11/binrel/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf.tar.xz
tar -xvf compiler.xz
rm -r compiler.xz
export PATH=dep/compiler/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf/bin:$PATH