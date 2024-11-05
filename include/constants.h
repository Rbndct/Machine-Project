#ifndef CONSTANTS_H
#define CONSTANTS_H

// Message Constants
#define OUT_OF_STOCK_MSG "Out of Stock"
#define INVALID_DENOM_MSG "Invalid denomination! Please try again."
#define SEPARATOR "--------------------------------------------------------------"

// Valid Denominations
static const float VALID_DENOMINATIONS[] = {20, 50, 100, 200, 500, 1, 5, 10, 0.25, 0.10, 0.05};
static const int NUM_VALID_DENOMINATIONS = 11;

#endif  // CONSTANTS_H
