% Compares the results of DeconMsn with Extract_msn
% Reads in the fht file and the concatenated file list generated from
% ConcatenateDtas.pl and compares the two based on charge and scan

clc
clear all;
X = [] ; 

fid_dtas = fopen('C:\data\Dta\validate_results\file_list.txt');
fid_out = fopen('C:\data\Dta\Test\combined_scan_charge_list.txt', 'wt') ; 

filename = fgets(fid_dtas);
while filename ~= -1    
    fileCh = strcat(filename) ;
    fspectra = fopen(fileCh);
    line = fgets(fspectra);
    value = str2num(line);
    mass = value(1);
    charge = value(2);  
    scan = GetScanFromFilename(filename);
    fprintf(fid_out, '%d\t', scan) ; 
    fprintf(fid_out, '%d\t',  charge) ; 
    fprintf(fid_out, '\n') ; 
    fclose(fspectra) ; 
    filename = fgets(fid_dtas) ;
end
fclose(fid_dtas) ; 
fclose(fid_out) ; 
    
 