DeconMSn 
--------------------
DeconMSn creates spectrum files for tandem mass spectrometry data. DeconMSn
can read in Finnigan .RAW files, if the needed DLLS are installed on the 
computer. Alternatively, the input data can also be of mzXML format.  With
high resolution data, for each MSn scan, the parent monoisotopic mass is 
accurately calculated from the parent isotopic distribution using a modified 
THRASH approach.  For low-resolution data, DeconMSn uses a support-vector
machine based charge-detection algorithm to determine parent mass. Results are 
acquired both as .dta files or .MGF files, which can be then used for peptide 
identifications using search engines such as SEQUEST, X!Tandem or MASCOT.  

Double click the DeconMSnInstaller.msi file to install. The .exe gets installed in 
C:\Program Files\DeconMSn, unless otherwise specified during installation.  
Type DeconMSn.exe at the command line in the installer directory to see the 
basic method of usage of the program shown below.  If the program won't run, see
below for some comments on file msvcp71.dll.

> DeconMSn.exe

	DeconMSn usage : DeconMSn [options] filename

	[options] are
	
	         -Istring : string is the minimum Number of ions peaks for a 
			    scan to be considered [35]
	         -Fstring : string is the first Scan to be considered [1]
	         -Lstring : string is the last Scan to be considered [1000000]
	         -Bstring : string is the minimum setting for Mass Range [200]
	         -Tstring : string is the maximum setting for Mass Range [5000]
	         -Cstring : string is the charge to be considered [NULL]
	         -Pstring : string is the parameter XML file name to be used for 
	            processing [default options are set if not present in the parameter file]
	         -Dstring : string is the output directory [default - set to 
	            same directory as input file]
	         -Xstring : string is output file format, options are
	                 DTA  : Creates .dta files along with a log file 
	                   (_log.txt)[default option]
	                 LOG  : Creates only log file (_log.txt)
	                 MGF  : Creates .mgf file along with log file(_log.txt)
	                 CDTA : Creates .dta files, log file(_log.txt), and a 
	                    composite dta file (_dta.txt)
	filename : input file [mzXML or RAW]

Note that the switch parameters are case-sensitive (for example you must use -P an not -p)

Some examples

Process sample.RAW, create .dta files
> DeconMSn.exe C:\data\sample.RAW 

Process sample.RAW with scan range of 1000-1200 and mass range of 200-1000, create .dta files
> DeconMSn.exe -F1000 -L1200 -B200 -T1000 C:\data\sample.RAW 

Process sample.RAW using default options; create .MGF as result file
> DeconMSn.exe -XMGF C:\data\sample.RAW 

Process sample.RAW, use processing options specified by parameter file LTQ_FT_Normal.xml
> DeconMSn.exe -PLTQ_FT_Normal.xml C:\data\sample.RAW 


Dependencies
-----------------
- DeconMSN assumes that the user has vendor specific libraries installed on the machine to run 
ThermoFinnigan data.  Alternatively, if the user converts
the raw data into the .mzXML format, then DeconMSn can process the data without vendor specific libraries
- When compiling the source code, the user must first install Xerces 
(http://xerces.apache.org/xerces-c/) and then modify the paths for header and library
in the solution to indicate any change in the Xerces installation folder (the default 
installation path given in DeconMSN is C:\xerces\)
-Current version of this program is built with xerces 2.8.
-This program requires msvcp71.dll, which is often already on your computer.  However
the installer should put a copy of msvcp71.dll in the c:\program files\DeconMSn\  You
may need to register this DLL by going to the command prompt and typing:
	cd "\Program Files (x86)\DeconMSn"
	regsvr32 msvcp71.dll

-------------------------------------------------------------------------------
Written by Anoop Mayampurath and Navdeep Jaitly for the Department of Energy 
(PNNL, Richland, WA) in 2006-2007.
Copyright 2007, Battelle Memorial Institute.  All Rights Reserved.

E-mail: anoop.mayampurath@pnl.gov or proteomics@pnl.gov
Website: http://ncrr.pnl.gov/ 
-------------------------------------------------------------------------------

Licensed under the Apache License, Version 2.0; you may not use this file 
except in compliance with the License.  You may obtain a copy of the License 
at http://www.apache.org/licenses/LICENSE-2.0
All publications that result from the use of this software should include the 
following acknowledgment statement:
 Portions of this research were supported by the NIH National Centre for 
 Research Resources and the National Institute of Allergy and Infectious 
 Diseases  (NIH/DHHS through interagency agreement Y1-AI-4894-01).  
 Experimental portions of this research were performed at the Environmental 
 and Molecular Sciences Laboratory (EMSL), a U. S. Department of Energy (DOE) 
 national scientific user facility located at Pacific Northwest National 
 Laboratory in Richland, Washington, USA.  PNNL is operated by Battelle 
 Memorial Institute for the U.S. Department of Energy under contract 
 DE-AC05-76RL0 1830.
 

Notice: This computer software was prepared by Battelle Memorial Institute, 
hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830 with the 
Department of Energy (DOE).  All rights in the computer software are reserved 
by DOE on behalf of the United States Government and the Contractor as provided
in the Contract.  NEITHER THE GOVERNMENT NOR THE CONTRACTOR MAKES ANY WARRANTY,
EXPRESS OR IMPLIED, OR ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  
This notice including this sentence must appear on any copies of this computer 
software.
