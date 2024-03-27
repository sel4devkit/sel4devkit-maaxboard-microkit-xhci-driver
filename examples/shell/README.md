# Shell xHCI example

This example shows off all of the capabilities of the xHCI API by providing a shell interface to interact with. This shell can be interacted with using a keyboard connected to the board (only MaaXBoard supported currently). By using a USB hub, more devices can be connected. The full list of devices supported is the same as that of the driver.

## List of commands
Type `help` into the console to see this message.
- `disable`
    - toggle keyboard (can be reenabled with mouse scroll)
- `kbdtest`
    - Enter keyboard test mode
- `fatls`
    - list files at filepath
    - Usage: `fatls <filepath>`
- `fatread`
    - read file
    - Usage: `fatread <filepath>`
- `fatwrite`
    - write file
    - Usage: `fatwrite <filepath> <value>`
- `getdev`
    - print device information
    - Usage: `getdev <id>`
- `help`
    - Display this screen
- `history`
    - display list of commands
- `init`
    - display splash
- `lsdev`
    - List all devices connected to board
- `mousetest`
    - enter mouse test mode
- `read`
    - read x blocks from connected device starting from y
    - Usage: `read <x> <y>`
- `snake`
    - "Play snake"
- `write`
    - write `v` (size `x` blocks) to connected device starting from block `y`
    - Usage: `write <x> <y> <v>`