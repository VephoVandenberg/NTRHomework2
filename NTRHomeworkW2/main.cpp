#include "homework3/LinkedList.hpp"
#include "homework3/homework3.hpp"

int main(int argc, char** argv)
{
	homework3::testHomework3();

	List<int> l1;

	
	l1.add(1);
	l1.add(2);
	
	List<int> l2;
	l2.add(-1);
	l2.add(-2);
	l2.add(-3);
	l2.addFront(-11);
	l2.addFront(-22);
	l2.popFront();
	l2.popFront();

	l2 = l1;

	List<int> l3;
	l3 = std::move(l2);

	l1.clear();
	
	return 0;
}