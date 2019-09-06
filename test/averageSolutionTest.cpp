#ifndef AVTEST_
#define AVTEST_
#include <limits.h>
#include "gtest/gtest.h"
#include "../src/base/Cartesian.cpp"

TEST(average, one) 
{
	double l[]={3.,4.};
	Cartesian<2> one(l);
	AverageSolution<2> av;

	for(std::size_t i=0;i<5;++i)
		av.append(one.length());

	EXPECT_EQ(5.,av.get()); 
}

TEST(average, two) 
{
	double l[]={0.,1.};
	Cartesian<2> one(l);
	AverageSolution<2> av;

	for(std::size_t i=1;i<10;++i)
	{
		av.append(one.length());
		one[1]+=1;
	}

	std::cout<<av.get()<<std::endl; 
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
