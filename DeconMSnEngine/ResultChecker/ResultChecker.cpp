#include "ResultChecker.h"

namespace Engine
{
	namespace ResultChecker
	{

		LCMSCheckResults::LCMSCheckResults()
		{
		}

		LCMSCheckResults::~LCMSCheckResults()
		{
		}

				
		void LCMSCheckResults::AddTransformsToCheck(std::vector<Engine::HornTransform::IsotopeFitRecord> &vect_isotope_record) 
		{
			/*Engine::HornTransform::IsotopeFitRecord isotope_rec ; 
			int num_records = vect_isotope_record.size() ;
			for (int rec_num = 0 ; rec_num < vect_isotope_record.size() ; rec_num++)
			{
				isotope_rec = vect_isotope_record[rec_num] ; 
				if(isotope_rec.mbln_flag_isotope_link == true)
					mvect_isotope_records.push_back(isotope_rec)  ; 
			}*/

		}

		void LCMSCheckResults::WriteOutTransformsToCheck(char *filename) 
		{
			/*Engine::HornTransform::IsotopeFitRecord record ; 
			filename = strcat(filename,"_linked_isos.csv") ; 
			std::ofstream fout(filename) ; 

			fout<<"scan_num"<<","<<"charge"<<","<<"abundance"<<","<<"mz";
			fout<<","<<"fit"<<","<<"average_mw"<<","<<"monoisotopic_mw"<<","<<"mostabundant_mw";
			fout<<","<<"fwhm"<<","<<"signal_noise"<<","<<"mono_abundance"<<","<<"mono_plus2_abundance";
			fout <<"\n" ;

			fout.precision(4) ; 
			fout.setf(std::ios::fixed, std::ios::floatfield);

					fout<<record.mint_scan_num<<","<<record.mshort_cs<<","<<record.mint_abundance<<","<<record.mdbl_mz ; 
					fout<<","<<record.mdbl_fit<<","<<record.mdbl_average_mw<<","<<record.mdbl_mono_mw<<","<<record.mdbl_most_intense_mw ; 
					fout<<","<<record.mdbl_fwhm<<"," ; 
					fout.precision(2) ; 
					fout<<record.mdbl_sn<<"," ; 
					fout.precision(4) ; 
					fout<<record.mint_mono_intensity<<"," ; 
					fout<<record.mint_iplus2_intensity<<"\n" ; */


			
		}

	}
}