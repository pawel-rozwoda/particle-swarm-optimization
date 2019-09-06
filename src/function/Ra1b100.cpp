#ifndef Ra1b100_CPP
#define Ra1b100_CPP
#include "../base/Pso.hpp"

template <std::size_t N>
class Ra1b100: public TestFunction<N>
{
	public:
		double R_B=100.;
		double R_A=1.;

		double getValue(Cartesian<N> &c)
		{
			double result = 0.0;
			for(std::size_t i = 0; i < N - 1; ++i)
			{
				result += R_B * pow(c[i+1] - pow(c[i],2.0), 2.0) + pow(R_A - c[i], 2.0);
			}
			return result;
		} 


		Cartesian<N> & getGradient(Cartesian<N> &c)
		{
			Cartesian<N> *ret = new Cartesian<N>();
			Cartesian<N> &ref = *ret;
			for(std::size_t i=0;i<N-1;++i)
			{
				ref[i] += 2.* (c[i] - R_A) + 4. * R_B *c[i]* (c[i]*c[i] -  c[i+1]);
				ref[i+1] += 2.* R_B*(c[i+1]-c[i]*c[i]);
			}
			return ref;
		}

		Cartesian<N> & expectedResult()
		{
			double l[N];
			for(std::size_t i=0;i<N;++i)
			{
				l[i] = 1.;
			}

			Cartesian<N> * c = new Cartesian<N>(l);
			return *c;
		}

		double expectedValue()
		{
			return 0.;
		}
};
#endif
