// This is the main project file for VC++ application project 
// generated using an Application Wizard.


// Written by  Anoop Mayampurath 
// for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: anoop.mayampurath@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0


#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

#using <mscorlib.dll>
#using <system.dll>
#using <System.Xml.dll>

using namespace System;
using namespace System::Reflection ; 
using namespace System::IO ; 
using namespace System::Xml ; 
using namespace System::Runtime::InteropServices;
using namespace std;


int _tmain( int argc, char *argv[] )
{
	System::String *commandLine;
	
	int elapTicks;
    double elapMilli, elapSeconds, elapMinutes;
    clock_t Begin, End;             //initialize Begin and End for the timer

	void PrintUsage() ;
	std::string ManagedToSTL(System::String *managed);
	std::string BoolToString(bool value);

	System::IO::Path *ioPath ; 
	System::String *strAppFolder ; 
	System::String *strSVMParamFilePath ; 
	System::String *strDllFileAndPath ; 
	
	strAppFolder = ioPath->GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location) ; 
	strSVMParamFilePath = System::IO::Path::Combine(strAppFolder, "svm_params.xml") ; 

	if (argc == 1)
	{
		PrintUsage();		
		return 0;
	}

	//default options
	int IValue = 25; //ion count - resetting it to 25 
	int FValue = 1;
	int LValue = 1000000;
	int CValue = 0;
	double BValue = 200;	
	double TValue = 5000;

	System::String *stringIvalue ;
	System::String *stringFvalue ;
	System::String *stringLvalue ;
	System::String *stringBvalue ;
	System::String *stringTvalue ;
	System::String *stringCvalue ;
	System::String *stringFileName ; 	
	System::String *stringOutputFileFormat ;
	System::String *stringSpectraFormat;
	System::String *stringParamFile ; 

	Decon2LS::clsProcRunner *obj_proc_runner;
	Decon2LS::HornTransform::clsHornTransformParameters *obj_transform_parameters;
	Decon2LS::DTAGeneration::clsDTAGenerationParameters *obj_dta_generation_parameters;
	Decon2LS::Peaks::clsPeakProcessorParameters *obj_peak_parameters;
		
	obj_proc_runner = new Decon2LS::clsProcRunner();
	obj_transform_parameters = new Decon2LS::HornTransform::clsHornTransformParameters();
	obj_peak_parameters = new Decon2LS::Peaks::clsPeakProcessorParameters();
	obj_dta_generation_parameters = new Decon2LS::DTAGeneration::clsDTAGenerationParameters() ;
	


	bool error = false ; 
	obj_dta_generation_parameters->set_SVMParamFile(strSVMParamFilePath) ; 
	obj_dta_generation_parameters->set_CentroidMSn(false);

	Begin = clock() ;

	int argvIndex = 1;

	// First check for a parameter file defined using -P
	if (argc > 1)
	{
		for (argvIndex = 1 ; argvIndex < argc ; argvIndex++)
		{
			commandLine = argv[argvIndex] ; 			
			if (commandLine->StartsWith("-P") && !commandLine->ToLower()->StartsWith("-progress"))
			{
				stringParamFile = commandLine->Remove(0, 2) ; 

				cout<<"Reading Parameter File "<< ManagedToSTL(stringParamFile) <<std::endl ; 
				
				System::Xml::XmlTextReader *rdr =  new System::Xml::XmlTextReader(stringParamFile) ; 
				//Read each node in the tree.
				while (rdr->Read())
				{
					switch (rdr->NodeType)
					{
						case XmlNodeType::Element:							
							if (System::String::Compare(rdr->Name, S"PeakParameters") == 0 )
							{
								obj_peak_parameters->LoadV1PeakParameters(rdr) ; 
							}
							else if (System::String::Compare(rdr->Name, S"HornTransformParameters") == 0)
							{
								obj_transform_parameters->LoadV1HornTransformParameters(rdr) ;
							}							
							else if (System::String::Compare(rdr->Name, S"DTAGenerationParameters") == 0)
							{
								obj_dta_generation_parameters->LoadV1DTAGenerationParameters(rdr) ; 
							}
							break;
						default:
							break ; 
					}
				}

				if (rdr != 0)
					rdr->Close() ; 
			}
		}
	}

	bool filenameDefined = false;
	stringSpectraFormat = "ALL";

	if (argc > 0)
	{
		// Now read the remaining parameters		

		for (argvIndex = 1; argvIndex < argc; argvIndex++)
		{
			commandLine = argv[argvIndex];
			if (!error)
			{
				if (commandLine->ToLower()->StartsWith("-progress"))
				{
					obj_dta_generation_parameters->set_WriteProgressFile(true);
					continue;
				}

				if (commandLine->ToLower()->StartsWith("-centroid"))
				{
					// Warning: the masses reported by GetMassListFromScanNum when centroiding are not properly calibrated and thus could be off by 0.3 m/z or more
					//          For example, in scan 8101 of dataset RAW_Franc_Salm_IMAC_0h_R1A_18Jul13_Frodo_13-04-15, we see these values:
					//          Profile m/z         Centroid m/z	Delta_PPM
					//			112.051 			112.077			232
					//			652.3752			652.4645		137
					//			1032.56495			1032.6863		118
					//			1513.7252			1513.9168		127
					obj_dta_generation_parameters->set_CentroidMSn(true);
					continue;
				}
				
				if (!commandLine->StartsWith("-"))
				{
					// Treat the first non-switch parameter as the dataset to process
					if (!filenameDefined)
						obj_proc_runner->FileName = commandLine ;

					filenameDefined = true;
				}
				else if (commandLine->Length > 1)
				{
					switch(commandLine->get_Chars(1))
					{
						case 'I':	stringIvalue = commandLine->Remove(0, 2);
									IValue = System::Convert::ToInt32(stringIvalue, 10);
									obj_dta_generation_parameters->set_MinIonCount(IValue) ; 
									break;	
						case 'F':   stringFvalue = commandLine->Remove(0, 2);
									FValue = System::Convert::ToInt32(stringFvalue, 10);
									obj_dta_generation_parameters->set_MinScan(FValue) ; 
									break;
						case 'L':	stringLvalue = commandLine->Remove(0, 2);
									LValue = System::Convert::ToInt32(stringLvalue, 10);	
									obj_dta_generation_parameters->set_MaxScan(LValue) ; 
									break;
						case 'B':	stringBvalue = commandLine->Remove(0, 2);
									BValue = System::Convert::ToDouble(stringBvalue);
									obj_dta_generation_parameters->set_MinMass(BValue) ; 
									break;
						case 'T':	stringTvalue = commandLine->Remove(0, 2);
									TValue = System::Convert::ToDouble(stringTvalue);
									obj_dta_generation_parameters->set_MaxMass(TValue) ;
									break;				
						case 'C':	stringCvalue = commandLine->Remove(0, 2);
									CValue = System::Convert::ToInt16(stringCvalue);									
									obj_dta_generation_parameters->set_ConsiderChargeValue(CValue) ; 
									break;
						case 'S':	stringSpectraFormat = commandLine->Remove(0, 2);							
									if (System::String::Compare(stringSpectraFormat, "ETD") == 0){
										obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::ETD);
									}
									else if (System::String::Compare(stringSpectraFormat, "CID") == 0){
										obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::CID);
									}
									else if (System::String::Compare(stringSpectraFormat, "HCD") == 0){
										obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::HCD);
									}
									else {
										stringSpectraFormat="ALL";
										obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::ALL);
									}

						case 'X':	stringOutputFileFormat = commandLine->Remove(0, 2);							
									if (System::String::Compare(stringOutputFileFormat, "MGF") == 0)
										obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::MGF) ;														
									else if (System::String::Compare(stringOutputFileFormat, "LOG") == 0)
										obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::LOG) ;														
									else if (System::String::Compare(stringOutputFileFormat, "CDTA") == 0)
										obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::CDTA) ;														
									else if (System::String::Compare(stringOutputFileFormat, "MZXML") == 0)
										obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::MZXML) ;														
									else if (System::String::Compare(stringOutputFileFormat, "DTA") == 0)
										obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::DTA) ; 
									else
									{
										PrintUsage() ; 
										error = true ; 
									}
									break ; 
						case 'D':	System::String *outputFolderPath ;
									outputFolderPath = commandLine->Remove(0, 2) ;														
									obj_proc_runner->OutputPathForDTACreation = outputFolderPath ; 
									break;									
						case 'G':	// Used by Extract_msn; ignored by DeconMSn
									break ; 
						case 'M':	// Used by Extract_msn; ignored by DeconMSn
									break ; 							
						case 'P':	// Already handled above
									break ; 
						default :	PrintUsage();
									error = true ; 
					}  // Switch

				} // If starts with '-'

			}
			else
			{
				return 0 ; 
			}			
		}
	
	}

	if (!filenameDefined)
	{
		PrintUsage();
		return -1;
	}

	if (error) //Anoop 05/08 
	{
		return -1 ; 
	}

	string filenameToProcess = ManagedToSTL(obj_proc_runner->FileName);

	cout<<"Processing File " << filenameToProcess << std::endl << std::endl;

	// Display the settings

	cout << "Minimum Number of ions for valid MSn scan: " << obj_dta_generation_parameters->get_MinIonCount() << std::endl;

	cout << "Scan Start: " << obj_dta_generation_parameters->get_MinScan() << std::endl;
	cout << "Scan End: " << obj_dta_generation_parameters->get_MaxScan() << std::endl;

	cout << "m/z Start: " << obj_dta_generation_parameters->get_MinMass() << std::endl;
	cout << "m/z End: " << obj_dta_generation_parameters->get_MaxMass() << std::endl;

	if (obj_dta_generation_parameters->get_ConsiderChargeValue() > 0)
		cout << "-C enabled with " << obj_dta_generation_parameters->get_ConsiderChargeValue();

	cout << "Spectra to process: " << ManagedToSTL(stringSpectraFormat) << std::endl;

	stringOutputFileFormat = obj_dta_generation_parameters->get_OutputTypeName();
	cout << "Output format: " << ManagedToSTL(stringOutputFileFormat) << std::endl;

	cout << "Create progress file: " << BoolToString(obj_dta_generation_parameters->get_WriteProgressFile()) << std::endl;
	cout << "Centroid profile mode MSn spectra: " << BoolToString(obj_dta_generation_parameters->get_CentroidMSn()) << std::endl;
	cout << std::endl;

	obj_proc_runner->HornTransformParameters = obj_transform_parameters;
	obj_proc_runner->PeakProcessorParameters = obj_peak_parameters;
	obj_proc_runner->DTAGenerationParameters = obj_dta_generation_parameters ; 
	
	obj_proc_runner->CreateDTAFile() ; 

	//obj_dta_generation_parameters->__dtor() ; 
	//obj_peak_parameters->__dtor() ; 
	//obj_transform_parameters->__dtor() ; 
	//obj_proc_runner->__dtor() ; 

	End = clock() ; 

	elapTicks = End - Begin;					//the number of ticks from Begin to End
    elapMilli = (CLK_TCK * elapTicks)/1000;     //milliseconds from Begin to End
    elapSeconds = elapMilli/1000;				//seconds from Begin to End
    elapMinutes = elapSeconds/60;				//minutes from Begin to End


	cout<<"\nDone. Finished processing in " << elapSeconds << " seconds.\n";
	
	return 0;
}


std::string BoolToString(bool value)
{
	if (value)
		return "True";
	else
		return "False";
}

void PrintUsage()
{	
	cout<<endl<< "DeconMSn usage : DeconMSn [options] filename"<<endl<<endl;
	cout<<"[options] are" <<endl<<endl;
	cout<<"\t -Istring : string is the minimum Number of ions peaks for a scan to be considered [35]" << endl;
	cout<<"\t -Fstring : string is the first Scan to be considered [1]" << endl;
	cout<<"\t -Lstring : string is the last Scan to be considered [1000000]" << endl;
	cout<<"\t -Bstring : string is the minimum setting for Mass Range [200]" <<endl;
	cout<<"\t -Tstring : string is the maximum setting for Mass Range [5000]" <<endl;
	cout<<"\t -Cstring : string is the charge to be considered [NULL]" <<endl;
	cout<<"\t -Pstring : string is the parameter XML file name to be used for processing [default options are set]" <<endl; 
	cout<<"\t -Dstring : string is the output directory[default - set to same directory as input file]" <<endl;
	cout<<"\t -Centroid: Enables centroiding MSn data (when acquired as profile data); off by default" <<endl;
	cout<<"              since the m/z values reported by the centroiding algorithm are typically off by several hundred ppm"<<endl;
	cout<<"\t -Progress: Creates a _progress.txt file with a percent complete value every 25 scans"<<endl;
	cout<<"\t -Sstring : string is the type of spectra to process, options are"<<endl;
	cout<<"\t \t ALL : to process all spectra present in the raw file (default)"<<endl;
	cout<<"\t \t CID : to process only CID spectra present in the raw file"<<endl;
	cout<<"\t \t ETD : to process only ETD spectra present in the raw file"<<endl;
	cout<<"\t \t HCD : to process only HCD spectra present in the raw file"<<endl;
	cout<<"\t -Xstring : string is output file format, options are"<<endl;
	cout<<"\t \t DTA  : Creates .dta files along with a log file (_log.txt) and profile file (_profile.txt)"<<endl ; 
	cout<<"\t \t LOG  : Creates only the log file (_log.txt) and profile file (_profile.txt)"<<endl; 
	cout<<"\t \t MGF  : Creates a .mgf file along with the log file and profile file"<<endl; 
	cout<<"\t \t CDTA : Creates a concatenated dta file (_dta.txt), a log file, and a profile file [default option]"<<endl; 		
	cout<<"filename : input file [mzXML or RAW]"<<endl; 
	cout<<endl; 
	cout<<"Written by Anoop Mayampurath and Navdeep Jaitly for the Department of Energy"<<endl; 
	cout<<"Maintained by Matthew Monroe"<<endl; 
	cout<<"E-mail: matthew.monroe@pnnl.gov or samuel.payne@pnnl.gov"<<endl; 
	cout<<"Website: http://omics.pnl.gov or http://panomics.pnnl.gov"<<endl; 

}

//Converts a System::String to a std::string
//This code assumes that you have used the following namespace:
// using namespace System::Runtime::InteropServices;
std::string ManagedToSTL(System::String *managed) {
    //get a pointer to an array of ANSI chars
    char *chars = (char*) Marshal::StringToHGlobalAnsi(managed).ToPointer();

    //assign the array to an STL string
    std::string stl = chars;

    //free the memory used by the array
    //since the array is not managed, it will not be claimed by the garbage collector
    Marshal::FreeHGlobal(chars);

    return stl;
}