#pragma once

#include <vector>

namespace Inverter
{
	void genRandomMem(uint8_t* start, const size_t nBytes);

	void invertBits(uint8_t* start, const size_t nBytes, const size_t startBit, const size_t nBitsToInv = 1);
	void invertBits(uint8_t* start, const size_t nBytes, const std::vector<size_t>& bitPositions);
}
