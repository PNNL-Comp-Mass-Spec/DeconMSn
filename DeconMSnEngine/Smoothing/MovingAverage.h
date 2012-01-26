#include "FilterSmoothing.h"

namespace Engine
{
	namespace Smoothing
	{

		class MovingAverage:public FilterSmoothing
		{

			public:
				MovingAverage(void);

				~MovingAverage(void);

				bool SmoothData();
		};
	}
}
