#!/bin/bash
set -e
echo -e "\x1b[32m
@2025 Project i4N
\x1b[0m"

cmake --build build/Debug --config Debug
echo -e "\x1b[32mBuild finished\x1b[0m"

ELF=$(find build/Debug -name "*.elf" | head -n 1)
if [ ! -f "$ELF" ]; then
    echo "Error: ELF file not found"
    exit 1
fi

echo -e "\x1b[32mFlashing ... \x1b[0m"
openocd -f openocd.cfg -c "program $ELF verify reset exit"
echo -e "\x1b[32mFlash finished\x1b[0m"