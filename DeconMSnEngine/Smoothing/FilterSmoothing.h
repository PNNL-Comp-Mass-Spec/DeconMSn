#pragma once
#include <vector>
#include <map> 

namespace Engine
{
	namespace Smoothing
	{
		class FilterSmoothing
		{
			public:
				FilterSmoothing ();
				~FilterSmoothing();

				virtual bool SmoothData(std::vector <double> *mzs, std::vector <double> *intensities, std::vector <double> *smooth) = 0;
		};
	}
}

	