#ifndef HSTEPS_
#define HSTEPS_
#include "../base/Simulation.cpp"
#include "../pso/TraditionalPso.cpp"
#include "../pso/StochasticPso.cpp"
#include "../function/Ra1b100.cpp"
#include "../base/Dat_File.cpp"

template <std::size_t N>
class Drawings2d : public Simulation<N>
{
	public:
		std::size_t stepQuantity; 
		bool terminateCondition()
		{
			return (stepQuantity++)==19;
		}
		void perform()
		{
			DatFile<N> df(Simulation<N>::name);
			df.createNextFile();
			df.currentFile<<*Simulation<N>::optimization;
			df.closeFile();

			while(!terminateCondition())
			{
				df.createNextFile();
				Simulation<N>::optimization->step(*Simulation<N>::tf);
				df.currentFile<<*Simulation<N>::optimization;
				df.closeFile();
			}

			std::cout<<"gb: "<<Simulation<N>::optimization->globalBestPosition<<std::endl;
		}

		Drawings2d(std::size_t pQ):stepQuantity(0)
		{
			Simulation<N>::name = "Drawings2d";
			Simulation<N>::tf = new Ra1b100<N>();
			Simulation<N>::particleQuantity = pQ;
			//Simulation<N>::optimization = new TraditionalPso<N>(Simulation<N>::particleQuantity);
			Simulation<N>::optimization = new StochasticPso<N>(Simulation<N>::particleQuantity,0.8,0.8);
			ParticleSetting<N> ps(Simulation<N>::particleQuantity,5.,*Simulation<N>::tf);
			Simulation<N>::optimization->setupSwarmSetting(ps);

		}
};



template <std::size_t N>
class StepQuantityDependency : public Simulation<N>
{
	public:
		std::size_t numberOfRepetitions = sqdParameters::performanceQuantity;
		std::size_t step = sqdParameters::step;
		std::size_t floor = sqdParameters::lowerBorder;
		std::size_t ceil = sqdParameters::upperBorder;
		std::size_t stepQuantity; 

		void execute(Pso<N> &pso,ParticleSetting<N> &pSetting)
		{

			AverageSolution<N> av;
			DatFile<N> df(Simulation<N>::name);
			df.createFile(pso.methodName,N,Simulation<N>::particleQuantity); 

			for(stepQuantity=floor;stepQuantity<=ceil;stepQuantity+=step)
			{
				for(std::size_t i=0;i<numberOfRepetitions;++i)
				{
	      				pso.setupSwarmSetting(pSetting);
					for(std::size_t k=0;k<stepQuantity;++k)
					{
					 pso.step(*Simulation<N>::tf);
					}

				av.append((pso.globalBestPosition - Simulation<N>::tf->expectedResult()).length());
				}
				df.currentFile<<stepQuantity<<"\t"<<av.get()<<std::endl;
				av.clear();
			}
			df.closeFile(); 
		}

		void perform()
		{ 
			ParticleSetting<N> ps(Simulation<N>::particleQuantity,3.,*Simulation<N>::tf);

			execute(* new TraditionalPso<N>(Simulation<N>::particleQuantity),ps);
			execute(* new StochasticPso<N>(Simulation<N>::particleQuantity),ps); 
		}

		StepQuantityDependency(std::size_t pQ):stepQuantity(0)
		{
			Simulation<N>::name = "StepQuantityDependency";
			Simulation<N>::particleQuantity = pQ;
			Simulation<N>::tf = new Ra1b100<N>();
		}
};

template <std::size_t N>
class TimeConsumption : public Simulation<N>
{
	public:
		std::size_t stepQuantity; 
		void perform()
		{

			ParticleSetting<N> ps(Simulation<N>::particleQuantity,5,*Simulation<N>::tf);
			for(std::size_t i=0;i<1000;++i)
			{
				Simulation<N>::optimization->setupSwarmSetting(ps);
				for(std::size_t k=0;k<20;++k)
				{
					Simulation<N>::optimization->step(*Simulation<N>::tf);
				}
			}

		}

		TimeConsumption(std::size_t pQ):stepQuantity(0)
		{
			Simulation<N>::name = "TimeConsumption";
			Simulation<N>::particleQuantity = pQ;
			Simulation<N>::tf = new Ra1b100<N>();
			//Simulation<N>::optimization = new TraditionalPso<N>(Simulation<N>::particleQuantity);
			Simulation<N>::optimization = new StochasticPso<N>(Simulation<N>::particleQuantity);
		}
};



#endif
