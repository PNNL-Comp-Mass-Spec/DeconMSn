#pragma once
#include "CalibratorImp.h"


namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorV :
			public CCalibratorImp
		{
		public:

			ApexCalibratorV(void);
			~ApexCalibratorV(void);

			CalibrationType GetCalibrationType() ;
			virtual double Mass2Freq(double mass);
			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual int GetRawPointsApplyFFT(float *data_ptr, std::vector <double> *mzs, std::vector<double> *intensities) ; 
			virtual int GetRawPointsApplyFFT(float *data_ptr, std::vector <double> *mzs, std::vector<double> *intensities, int num_pts_used) ; 
		};
	}
}