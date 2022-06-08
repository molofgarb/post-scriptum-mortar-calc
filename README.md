# post-scriptum-mortar-tool
A calculator that performs Post Scriptum and Squad mortar calculations.

## Building File
1. Using provided binaries
    - Download the binary that corresponds to your operating system.
2. Building from source
    - Run makefile provided. Or, if you do not have make, run the commands in the makefile  with an appropriate compiler.

## Usage
1. Enter mortar coordinate in the format "A1-7-7" or "A1 7 7". Letters can be uppercase or lowercase.
2. Provide mortar type. The US, GER, and UK 3 inch mortars are "short" mortars, so an input of 0 should be provided. The UK 4 inch mortar is a "long" mortar, so an input of 1 should be provided.
3. Enter target coordinates in the same format as the mortar coordinate previously provided. Tthe target coordinate needs to be in range of the mortar for an accurate calculation to be provided. A maximum range table is provided at the start of the program.
4. Use calculated results to calibrate the mortar in game to hit the target coordinate.
5. To change the location of the mortar, type "new" when the target coordinate is requested.
6. To exit the program, type "exit" whenever any input is requested.
