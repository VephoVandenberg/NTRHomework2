#include <iostream>
#include <random>

#include "inverter.hpp"

constexpr size_t g_bitsInByte = 8;
constexpr size_t g_seed = 777;

inline void invertBit(uint8_t* start, const size_t iBit)
{
	start[iBit / g_bitsInByte] ^= (0x80 >> (iBit % g_bitsInByte));
}

void Inverter::invertBits(uint8_t* start, const size_t nBytes,
	const size_t startBit, const size_t nBitsToInv)
{
	const size_t nBits = nBytes * g_bitsInByte;

	if (startBit > nBits)
	{
		std::cout
			<< "ERROR::Invalid start position of invertion! Valid range 0 : " << nBits << '\n';
		return;
	}

	for (size_t iBit = startBit; iBit < startBit + nBitsToInv && iBit < nBits; iBit++)
	{
		invertBit(start, iBit);
	}
}

void Inverter::invertBits(uint8_t* start, const size_t nBytes, 
	const std::vector<size_t>& bitPositions)
{
	const size_t nBits = nBytes * g_bitsInByte;

	for (const auto pos : bitPositions)
	{
		if (pos > nBits)
		{ 
			std::cout << "ERROR::Invalid start position" << pos << "! Valid range 0 : " << nBits << '\n';
			continue;
		}
		invertBit(start, pos);
	}
}

void Inverter::genRandomMem(uint8_t* start, const size_t nBytes)
{
	std::mt19937 engine;
	engine.seed(g_seed);
	std::uniform_int_distribution<size_t> distribuition(1, 255);
	for (size_t iByte = 0; iByte < nBytes; iByte++)
	{
		start[iByte] = distribuition(engine);
	}
}
