# LTCG Calculator

## Project Overview

The LTCG Calculator is a C++ program designed to calculate Long-Term Capital Gains (LTCG) tax based on different taxation schemes. The program allows users to input a year for selling a property and computes the estimated selling price and the tax amount based on the old and new LTCG tax schemes.

### Features

- Reads inflation data from a CSV file.
- Computes selling price based on inflation-adjusted growth.
- Calculates LTCG tax using both the old scheme (20% with inflation adjustment) and the new scheme (12.5% without inflation adjustment).
- Compares the taxes under both schemes and shows which leads to higher taxes.

## Building the Project

To build the project, a `Makefile` is provided to generate debug and optimized binaries.

### Prerequisites

- **g++** (GNU Compiler Collection) for compiling C++ code.

### Using the Makefile

1. **Default Target**: Run `make` to build both debug and optimized versions of the executable.

   ```sh
   make
   ```

2. **Debug Build**: Run `make debug` to build the debug version with debugging information.

   ```sh
   make debug
   ```

3. **Optimized Build**: Run `make optimized` to build the optimized version with compiler optimizations enabled.

   ```sh
   make optimized
   ```

4. **Clean Up**: Run `make clean` to remove the generated binaries and clean up build artifacts.

   ```sh
   make clean
   ```

## Running the Program

After building the project, you can run the executable binaries:

1. **Debug Version**:

   ```sh
   ./ltcg_debug
   ```

2. **Optimized Version**:

   ```sh
   ./ltcg_optimized
   ```

### How to Use the Program

1. **Input**: When prompted, enter the year of selling the property.
2. **Output**: The program will display:
   - The estimated selling price.
   - The LTCG tax to be paid under the old scheme (20% with inflation adjustment).
   - The LTCG tax to be paid under the new scheme (12.5% without inflation adjustment).
   - The difference in tax between the old and new schemes.

## Important Notes

- Ensure that the `price-inflation.csv` file containing inflation data is present in the same directory as the executable or provide the correct path to the file.
- The program assumes that the CSV file has the correct format with headers as described in the code.

## Troubleshooting

- **File Not Found Error**: Ensure the CSV file path is correct.
- **Compilation Errors**: Verify that you have `g++` installed and your environment is set up correctly for C++ development.

Feel free to contribute or open issues if you encounter any problems or have suggestions for improvements.
