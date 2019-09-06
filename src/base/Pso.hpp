#ifndef PSO_HPP_
#define PSO_HPP_
#include "Cartesian.cpp"
#include "TestFunction.hpp"
#include "parameters.hpp"
#include <vector>
#include <random>
#include <iomanip>


double randomFlat(double left,double right); 
/*
 * random
 *
 * */
double randomNormal(double mi,double sigmaSquared);


/*
 * this class template represents one particle of the swarm
 *
 */
template <std::size_t N>
struct Particle
{
	Cartesian<N> currentPosition;
	Cartesian<N> bestPosition;
	Cartesian<N> velocity;
};

/*
 * Instances of this class stores particle setting that can be reused.
 * It enables to initialize different optimization methods's swarm in same position
 */
template <std::size_t N>
class ParticleSetting
{
	public:
		TestFunction<N> * tf;
		Cartesian <N> auxGlobalBestPosition;

		std::vector<Particle<N> > v;
		ParticleSetting<N>(std::size_t pq, double radius,TestFunction<N> &tf)
		{
			for(std::size_t i=0;i<pq;++i)
			{
				Particle<N> p;
				for(std::size_t k=0;k<N;++k)
				{
					p.currentPosition[k]=randomFlat(-1.,1.);
					p.velocity[k]=randomFlat(-1.,1.);
				}

				p.currentPosition.normalize();
				p.velocity.normalize();
				p.currentPosition = p.currentPosition * radius;
				p.currentPosition = p.currentPosition + tf.expectedResult();
				p.bestPosition = p.currentPosition;

				v.push_back(p);
			}
			auxGlobalBestPosition = v.at(0).currentPosition;

			for(std::size_t i=0;i<v.size();++i)
			{
				Particle<N> p = v.at(i);
				if(tf.getValue(p.currentPosition) < tf.getValue(auxGlobalBestPosition))
				{
					auxGlobalBestPosition = p.currentPosition;
				}
			}
		}
};



template <std::size_t N>
class Pso
{
	public:

		Cartesian<N> globalBestPosition;
		std::string methodName; 
		/**
		 * this updates all of particles in swarm, accordingly to function shape
		 * */
		void step(TestFunction<N> &tf);
		/**
		 *this function set ups swarm
		 */
		 
		void setupSwarmSetting(const ParticleSetting<N> &ps); 
		std::vector<Particle<N> > particles;
		explicit Pso()=default;
		explicit Pso(std::size_t pQ);

	private:
		/**
		 * this is auxiliary function checks wether actual position of particular particle is better than personalBest
		 * and update this value
		 */
		void compareWithGlobalBest(Particle<N> &p,TestFunction<N> &tf);
		/**
		 * this auxliary function updates one particle
		 * */
		virtual void updateParticle(Particle<N> &p, TestFunction<N> &tf) = 0;


};

template <std::size_t N>
std::ostream & operator<<(std::ostream& os, const Pso<N> & pso)
{  
	for(std::size_t i=0;i<pso.particles.size();++i)
	{
		os<< pso.particles.at(i).currentPosition;
	}
	return os;  
}  

template <std::size_t N>
void Pso<N>::step(TestFunction<N> &tf){

	for(std::size_t i=0;i<Pso<N>::particles.size();i++){
		Particle<N> &p = Pso<N>::particles.at(i);
		updateParticle(p,tf);
		Pso<N>::compareWithGlobalBest(p,tf);
	}
}


template <std::size_t N>
Pso<N>::Pso(std::size_t pQ)
{
	for(std::size_t i=0;i<pQ;++i)
	{
		Particle<N> p;
		particles.push_back(p);
	}
}

template <std::size_t N>
void Pso<N>::compareWithGlobalBest(Particle<N> &p,TestFunction<N> &tf)
{
	double aux = tf.getValue(p.currentPosition);

	if(aux < tf.getValue(p.bestPosition))
	{
		p.bestPosition = p.currentPosition;

		if(aux < tf.getValue(globalBestPosition))
		{
			globalBestPosition = p.currentPosition;
		}
	}
}

template <std::size_t N>
void Pso<N>::setupSwarmSetting(const ParticleSetting<N> &ps)
{

	particles.clear();

	for(std::size_t i = 0 ; i<ps.v.size();++i)
	{
		Particle<N> p( ps.v.at(i) );
		particles.push_back(p);
	}
	globalBestPosition = ps.auxGlobalBestPosition;
}

double randomFlat(double left,double right)
{
	double aux;
	if(right>=left){
		std::random_device r;
		std::default_random_engine e1(r());

		std::uniform_real_distribution<double> uniform_dist(left, right);
		aux = uniform_dist(e1);
		return aux;
	}
	else std::cerr<<"wrong random range";
	return -1;
}

double randomNormal(double mi,double sigmaSquared)

{
	std::random_device r;
	std::default_random_engine e1(r());
	std::normal_distribution<double> d(mi,sigmaSquared);
	return d(e1);
}

#endif
