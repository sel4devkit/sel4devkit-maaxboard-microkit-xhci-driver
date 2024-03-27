# Async FatFs example
This example is adapted from [this LionsOS FatFs example](https://github.com/au-ts/LionsOS/tree/FatFs/examples), and depends on resources used by it. The resources will be pulled by git submodule. 

## Changes made
The example in the LionsOS directory is intended for use using the VMM. In contrast, this example demonstrates usage using our seL4 xHCI driver and API to communicate with a USB mass storage device on a block level, running bare on microkit rather than using the VMMs capabilities.

The xHCI API uses the design paradigms outlined in the sDDF, and therefore fits with little modification into this async FatFs example. No modifications need to be made to the underlying driver, and very slight changes have been made to accommodate the lack of VMM support in the FatFs library. The system file has been modified to remove the VMM protection domain, and contains the template xHCI API user system file (found in empty-client).
