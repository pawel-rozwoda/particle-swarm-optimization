#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_
#include <cmath>
#include <array>
#include <iostream>
#include <iomanip>
#include <vector>

/*
 *Represents cartesian point.
 */
template<std::size_t N>
class Cartesian{
	public:
		std::array<double,N> a;
		double & operator [](std::size_t position);
		Cartesian operator+(const Cartesian &c);
		Cartesian operator-(const Cartesian &c);
		void operator=(const Cartesian &other);
		bool operator==(const Cartesian &other);
		/*
		 * it returns euclidean distance from zero vector. For example, if position components are [1,1], length would equal sqrt(2).
		 */
		double length();
		/*
		 * this makes normalisation for euclidean point.
		 */
		void normalize();
		Cartesian<N>();
		Cartesian<N>(double *l);
		Cartesian(const Cartesian<N>& a)=default;
};


template <std::size_t N>	
std::ostream & operator<<(std::ostream& os, const Cartesian<N> & c)
		{  
			for(std::size_t i=0;i<N;++i)
			{
				if(i<N-1)
					os << c.a[i]<< std::setw(14);  
				else
					os << c.a[i];  
			}
			os<<std::endl;

			return os;  
		}  

template <std::size_t N>Cartesian<N> operator*(const Cartesian<N> &c, const double d);

template <std::size_t N>Cartesian<N> operator*(const double d, const Cartesian<N> &c);

template <std::size_t N> Cartesian<N>:: Cartesian()
{
	a = {};
}

template <std::size_t N> void Cartesian<N>::normalize()
{
	double aux = this->length();
	if(aux!=0)
	{
		for(std::size_t i=0;i<a.size();i++)
		{
			a[i]= a[i]*(1./aux);	
		}
	}

}

template <std::size_t N> double Cartesian<N>::length(){
	double aux=0;

	for(std::size_t i=0;i<a.size();i++)
	{
		aux+= a[i]*a[i];	
	}
	return sqrt(aux);
}


template <std::size_t N> double & Cartesian<N>::operator[](std::size_t position)
{
	return a[position];
}

template <std::size_t N> Cartesian<N>:: Cartesian(double l[N] )
{
	for(std::size_t i=0;i<a.size();i++)
	{
		a[i]=l[i];
	}
}
template <std::size_t N> Cartesian<N> Cartesian<N>::operator+(const Cartesian<N> &c)
{
	Cartesian ret;
	for(std::size_t i=0;i<a.size();i++){
		ret[i]=a[i]+c.a[i];	
	}
	return ret;
}

template <std::size_t N> bool Cartesian<N>::operator==(const Cartesian<N> &other)
{
	return a == other.a;
}

template <std::size_t N> Cartesian<N> Cartesian<N>::operator-(const Cartesian<N> &c)
{
	Cartesian ret;
	for(std::size_t i=0;i<a.size();i++)
	{
		ret[i]=a[i]-c.a[i];	
	}
	return ret;
}

template <std::size_t N> void Cartesian<N>::operator=(const Cartesian<N> & other)
{
	for(std::size_t i=0;i<a.size();i++)
	{
		a[i]=other.a[i];	
	}
}

template <std::size_t N>Cartesian<N> operator*(const Cartesian<N> &c, const double d)
{
	Cartesian<N> ret;
	for(std::size_t i=0;i<c.a.size();i++)
	{
		ret[i]=d*c.a[i];
	}
	return ret;
}

template <std::size_t N>Cartesian<N> operator*(const double d, const Cartesian<N> &c)
{
	Cartesian<N> ret;
	for(std::size_t i=0;i<c.a.size();i++)
	{
		ret[i]=d*c.a[i];
	}
	return ret;
}

/*
 * This auxiliary template class enables to calculate average solution for the set of values given with help of append function.
 * */
template <std::size_t N> 
class AverageSolution
{
	public:

	double sum;
	int count;

	AverageSolution<N>() 
	{
		clear();
	}

	/**
	 * This function returns average value from set given by append function.
	 */
	double get()
	{
		return sum/(double)count;
	}

	/**
	 * This function appends value to a sum. It also increases count. Finally one could calculate average solution.
	 */
	void append(double l)
	{
		sum+=l;
		++count;
	}

	/**
	 * This function resets sum and count variables to zero.
	 */
	void clear()
	{
		sum=0;
		count = 0;
	}

};
#endif
