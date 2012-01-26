#use strict ; 
my $dta_folder = "C:\\data\\MassRefinement\\" ; 
my @files = <$dta_folder*.dta> ; 
my $num_files = @files ;
printf "Found $num_files files\n" ; 

my $combined_dta_file = "c:\\data\\sequest\\QC_06_01-b_26Jun06_Draco_05-08-07fst_dta\\QC_06_01-b_26Jun06_Draco_05-08-07fst_dta.txt" ; 
my %file_hash ; 

for (my $file_num = 0 ; $file_num < @files ; $file_num++)
{
	my $current_file = substr($files[$file_num], length($dta_folder), length($files[$file_num]) - length($dta_folder)-4) ; 
	my $current_file_without_charge = substr($files[$file_num], length($dta_folder), length($files[$file_num]) - length($dta_folder)-6) ; 
	$file_hash{$current_file} = 1 ; 
}

open (FILE, "<$combined_dta_file") || die "Could not open combined dta file: $combined_dta_file\n" ; 
while(<FILE>)
{
	my $line = $_ ; 
	chomp($line) ; 


	if (substr($line,0,1) eq "=")
	{
		my $start_index = index($line, "\"", 0) ;  
		my $end_index = index($line, "\"", $start_index+1) ; 
		my $dta_name = substr($line, $start_index+1 , $end_index-$start_index-5) ;
		my $dta_name_without_charge = substr($line, $start_index+1 , $end_index-$start_index-7) ;
		if (exists($file_hash{$dta_name_without_charge}))
		{
			$file_hash{$dta_name} = 0 ; 
		} 
		else
		{
			$file_hash{$dta_name} = 2 ; 
		}
	
	}
}
foreach my $file_name (keys %file_hash)
{
	if ($file_hash{$file_name} != 0)
	{
		printf "$file_name $file_hash{$file_name}\n" ; 
	}
}