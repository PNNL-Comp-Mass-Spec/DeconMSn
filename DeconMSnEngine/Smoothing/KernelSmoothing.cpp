#include "KernelSmoothing.h"
#include <map> 
#include <iostream>
#include <float.h>
#include <fstream> 

namespace Engine
{
	namespace Smoothing
	{
		KernelSmoothing::KernelSmoothing(void){};

		KernelSmoothing::~KernelSmoothing(void){};


		bool KernelSmoothing::SmoothData(std::vector <double> *mzs, std::vector <double> *intensities, std::vector <double> *smooth)
		{
			bool debug = true;
			return debug;
		}
	}
}