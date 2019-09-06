
#ifndef DAT_FILE_
#define DAT_FILE_

#include "headerLocation.hpp"
#include <fstream>
#include <sys/stat.h>
#include "Cartesian.cpp"
#include "Pso.hpp"
#include <string>
#include <sys/stat.h>

inline bool directoryExists (const std::string& name) {
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}



template <std::size_t N>
class DatFile
{
	public:

		int iteration;
		std::string currentDirectoryPath;
		std::ofstream currentFile; 

		/**
		 * Initially this function was useful to name files uniquely.
		 * It is not excluded from the class in scenario it could be useful someday
		 */
		std::string getCurrentDateString(); 
		/**
		 *
		 * this function is used mostly by Drawings2d class.
		 * \ it creates next file in the same directory.
		 */ 
		void createNextFile(const std::string &f_n=std::string(""));
		/**
		 * this function generates file for ParticleQuantityDependency class.
		 */
		void createFile(std::string methodName ,std::size_t dim,std::size_t pq=0); 
		/**
		 * it closes currentFile ofstream that belongs to Dat_File template class
		 */
		void closeFile(); 
		/**
		 * it creates directory that will be named by Simulation name.
		 */
		void createDirectory(const std::string & simulationName);

		DatFile(const std::string & simulationName): iteration(0)
		{
			createDirectory(simulationName);
		}; 
};


template <std::size_t N>
void	DatFile<N>:: createNextFile(const std::string &f_n)
{
	std::string file_name=std::string(f_n);
	std::string iteration_name;
	if(file_name.compare("")==0)

	{
		file_name = std::to_string(iteration);

		if(iteration<1000)
		{
			file_name.insert(0,1,'0');
		}
		if(iteration<100)
		{
			file_name.insert(0,1,'0');
		}
		if(iteration<10)
		{
			file_name.insert(0,1,'0');
		}
	}
	currentFile.open(currentDirectoryPath+"/"+file_name+".dat",std::ios::out);
	currentFile<<"#x\t#y\n";
	++iteration;
}


template <std::size_t N> 
void DatFile<N>::createFile(std::string methodName ,std::size_t dim,std::size_t pq)
{
	std::string fileName=std::string(methodName+std::to_string(dim)+"_"+std::to_string(pq)); 
	currentFile.open(currentDirectoryPath+"/"+fileName+".dat",std::ios::out);
	currentFile<<"#x\t#y\n";
	++iteration;
}


template <std::size_t N>
void DatFile<N>::closeFile(){
	currentFile.close();
}


template <std::size_t N> 
void DatFile<N>::createDirectory(const std::string & simulationName)
{
	currentDirectoryPath=std::string(PATHTOPNG + simulationName);

	if(!directoryExists(currentDirectoryPath))
	{ 
		if(mkdir(currentDirectoryPath.c_str(),0755)<0)
		{
			perror("error occured while creating directory");
		} 
	} 
}


template <std::size_t N>
std::string DatFile<N>::getCurrentDateString()
{
	return std::string(std::to_string(time(0)));
}

#endif
