#ifndef STOCHASTIC_
#define STOCHASTIC_
#include "../base/Pso.hpp"
#include <iomanip>

/*
 *
 * Implementation of proposed PSO method
 */
template <std::size_t N>
class StochasticPso:public Pso<N>
{
	public:
		void updateParticle(Particle<N> &p,TestFunction<N> &tf);

		double tStep;
		double gamma;
		double a,b,ksi,eta;

		StochasticPso(std::size_t pQ,double paramA=stochasticParameters::aValue,double paramB=stochasticParameters::bValue): Pso<N>(pQ)
		{

			tStep = stochasticParameters::timeStep;
			gamma = stochasticParameters::gamma;
			a = paramA; 
			b = paramB;

			//Pso<N>::methodName = "Stochastic" + std::to_string(tStep) + "_";
			Pso<N>::methodName = "Stochastic" ;

			if(stochasticParameters::versatileOutput)
			{
				std::cout<<"a "<<a<<std::endl;
				std::cout<<"b "<<b<<std::endl;
				std::cout<<"tStep "<<tStep<<std::endl;
				std::cout<<"gamma "<<gamma<<std::endl;
			}
		}
};




template <std::size_t N>
void StochasticPso<N>::updateParticle(Particle<N> &p,TestFunction<N> &tf)
{ 
 ksi = randomNormal(0.5,1.);
 eta = randomNormal(0.5,1.); 


	p.velocity = 	p.velocity * (1.- gamma*tStep) 

		-tStep * tf.getGradient(p.currentPosition)

		+ sqrt(tStep) * ( a * ksi * (p.bestPosition - p.currentPosition)

				+ b * eta * (Pso<N>::globalBestPosition - p.currentPosition));  


	p.currentPosition = p.currentPosition + p.velocity;


	if(stochasticParameters::versatileOutput) 
	{
		std::cout
		<<std::setw(12)		<<(1.-gamma*tStep)* p.velocity.length()<<"\t"
		<<std::setw(12)		<<(-tStep * tf.getGradient(p.currentPosition)).length()<<"\t"
		<<std::setw(12)		<< (sqrt(tStep) * ( a * ksi * (p.bestPosition - p.currentPosition) 
					+ b * eta * (Pso<N>::globalBestPosition - p.currentPosition))).length()<<std::endl;  
	} 
}

#endif

