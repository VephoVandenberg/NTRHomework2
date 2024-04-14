#include <bitset>
#include <iostream>

#include "inverter.hpp"

void test();

int main(int argc, char** argv)
{
	test();

	return 0;
}

void printMem(uint8_t* start, const size_t nBytes)
{
	std::cout << "Dec: ";
	for (size_t iByte = 0; iByte < nBytes; iByte++)
	{
		std::cout << +start[iByte] << '.';
	}
	std::cout << '\n';

	std::cout << "Bin: ";
	for (size_t iByte = 0; iByte < nBytes; iByte++)
	{
		std::cout << std::bitset<8 * sizeof(uint8_t)>(start[iByte]) << '.';
	}
	std::cout << '\n' << '\n';
}

void test()
{
	// Generate memory
	uint8_t testMem1[3] = {255, 255, 255};
	const size_t memBytes1 = sizeof(testMem1) / sizeof(uint8_t);

	// Print generated memory
	std::cout << "<Generated Memory>" << '\n';
	printMem(testMem1, memBytes1);

	// So in this test we have 24 bits,
	// let's invert from 7th bit 5 bits
	std::cout << "<Memory with inverted bits>" << '\n';
	Inverter::invertBits(testMem1, memBytes1, 5, 5);
	printMem(testMem1, memBytes1);

	// Now let's test one more function,
	// if we want to invert singular bits,
	// then pass positions with vector,
	// and let's assume last position in vector is out of bounds
	std::cout << "<Memory with more inverted bits>" << '\n';
	Inverter::invertBits(testMem1, memBytes1, { 1, 5, 20, 23, 100 });
	printMem(testMem1, memBytes1);


	uint8_t testMem2[8];
	const size_t memBytes2 = sizeof(testMem2) / sizeof(uint8_t);
	Inverter::genRandomMem(testMem2, memBytes2);

	// Same kind of shinnanegans here just to be sure
	std::cout << "<Generated Memory>" << '\n';
	printMem(testMem2, memBytes2);

	std::cout << "<Memory with inverted bits>" << '\n';
	Inverter::invertBits(testMem1, memBytes1, 1, 22);
	printMem(testMem2, memBytes2);

	std::cout << "<Memory with more inverted bits>" << '\n';
	Inverter::invertBits(testMem2, memBytes2, {10000000, 1, 4, 18, 21, 23, 100 });
	printMem(testMem2, memBytes2);
}
