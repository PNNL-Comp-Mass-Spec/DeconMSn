#include "FilterSmoothing.h"

namespace Engine
{
	namespace Smoothing
	{

		class KernelSmoothing:public FilterSmoothing
		{

			public:
				KernelSmoothing(void);

				~KernelSmoothing(void);

				bool SmoothData(std::vector <double> *mzs, std::vector <double> *intensities, std::vector <double> *smooth);
		};
	}
}
