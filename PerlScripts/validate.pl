#use strict ; 
my $dta_folder = "C:\\data\\Dta\\Test\\LowRes\\" ; 
my @files = <$dta_folder*.dta> ; 
my $num_files = @files ;
printf "Found $num_files dta files\n" ; 
my $out_file_name = "C:\\development\\DeconMSn\\validate\\test_out.txt";

my $combined_dta_file = "C:\\data\\Dta\\Test\\LowRes\\QC_04_1_LTQ_28Oct04_Doc_1004-3_4-20_dta.txt" ; 
my %file_hash ; 

for (my $file_num = 0 ; $file_num < @files ; $file_num++)
{
	my $current_file = substr($files[$file_num], length($dta_folder), length($files[$file_num]) - length($dta_folder)-4) ; 
	my $current_file_without_charge = substr($files[$file_num], length($dta_folder), length($files[$file_num]) - length($dta_folder)-6) ; 
	$file_hash{$current_file}= 1 ; 
}

open (FILE, "<$combined_dta_file") || die "Could not open combined dta file: $combined_dta_file\n" ; 
my $combined_dta_count = 0 ;
my $zero_count = 0;
my $two_count = 0;
my $one_count = $file_num;

while(<FILE>)
{
	my $line = $_ ; 
	chomp($line) ; 

	if (substr($line,0,1) eq "=")
	{
		$combined_dta_count = $combined_dta_count + 1;
		my $start_index = index($line, "\"", 0) ;  
		my $end_index = index($line, "\"", $start_index+1) ; 
		my $dta_name = substr($line, $start_index+1 , $end_index-$start_index-5) ;
		my $dta_name_without_charge = substr($line, $start_index+1 , $end_index-$start_index-7) ;
		if (exists($file_hash{$dta_name}))
		{
			$file_hash{$dta_name} = 0 ; 			
			$zero_count = $zero_count +1 ;			
		} 
		else
		{
			$file_hash{$dta_name} = 2 ; 
			$two_count = $two_count +1;
		}
	
	}
}

printf "Found $combined_dta_count combined DTA files\n" ; 
print "Found $zero_count common DTAs\n" ;
print "Found $two_count DTAs in Extract_MSN\n" ;


open(OUTFILE, ">$out_file_name") || die "Could not open output file\n";
foreach my $file_name (keys %file_hash)
{
	if ($file_hash{$file_name} == 2 )
	{
		print OUTFILE "$file_name \n" ; 
	}
	
}
