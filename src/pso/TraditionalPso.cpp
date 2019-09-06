#ifndef TRADITIONAL_
#define TRADITIONAL_
#include "../base/Pso.hpp"
template <std::size_t N>
class TraditionalPso:public Pso<N>
{
	public:
		void updateParticle(Particle<N> &p,TestFunction<N> &tf);

		double a,b,ksi,eta,omega;

		TraditionalPso(std::size_t pQ): Pso<N>(pQ)
	  {
			omega=0.8125;
			a=0.8125;
			b=0.8125;
			Pso<N>::methodName = "Traditional";

	  }
};


template <std::size_t N>
void TraditionalPso<N>::updateParticle(Particle<N> &p,TestFunction<N> &tf){


	ksi = randomFlat(0,1);
	eta = randomFlat(0,1);
	
	p.velocity = omega*p.velocity 

		+ a*ksi* ( p.bestPosition -  p.currentPosition)

		+ b*eta* ( Pso<N>::globalBestPosition -  p.currentPosition);


		p.currentPosition = p.currentPosition + p.velocity;


}
#endif
