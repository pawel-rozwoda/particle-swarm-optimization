#ifndef FTEST_
#define FTEST_

#include <limits.h>
#include "gtest/gtest.h"
#include "../src/base/Cartesian.cpp"
#include "../src/function/Ra1b100.cpp"


TEST(a1b1, one) {
	Ra1b100<2> tf;
		double l[2];
		l[0]=1;
		l[1]=1;
		Cartesian<2> c(l);
	
		EXPECT_EQ(0,tf.getValue(c)); }

TEST(gradient, one) {
	Ra1b100<2> tf;
		double l[2];
		l[0]=1;
		l[1]=1;
		Cartesian<2> c(l);
	
		EXPECT_EQ(0,tf.getGradient(c)[0]);
		EXPECT_EQ(0,tf.getGradient(c)[1]);

}

TEST(gradient, two) {
	Ra1b100<6> tf;
		double l[6];
		l[0]=1;
		l[1]=1;
		l[2]=1;
		l[3]=1;
		l[4]=1;
		l[5]=1;
		Cartesian<6> c(l);
		Cartesian<6> zero;
	
		ASSERT_TRUE(zero==tf.getGradient(c));
}







int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



#endif

