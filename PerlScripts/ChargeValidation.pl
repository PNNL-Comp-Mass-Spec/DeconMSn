#use strict ; 
my $decon_folder = "C:\\data\\Dta\\DTA_High_res\\" ; 
my $dta_folder = "C:\\data\\Dta\\DTA_Low_Res\\" ;

my $dta_file = "C:\\development\\DeconMSn\\validate\\dta_file_list.txt" ;
my $decon_file = "C:\\development\\DeconMSn\\validate\\decon_file_list.txt" ;
my $out_file = "C:\\development\\DeconMSn\\validate\\charge_validate.txt" ;

my @decon_files = <$decon_folder*.dta> ; 
my @dta_files = <$dta_folder*.dta> ;
my $num_decon_files = @decon_files ;
my $num_dta_files = @dta_files; 

printf "Found $num_decon_files files from Decon\n" ; 
printf "Found $num_dta_files files from DTA\n" ; 

open(DECONFILE, ">$decon_file") || die "Could not open output file\n";
open(DTAFILE, ">$dta_file") || die "Could not open output file\n";
my $total_dta = 0;

for (my $file_num = 0 ; $file_num < @decon_files ; $file_num++)
{
	my $current_file = substr($decon_files[$file_num], length($decon_folder), length($decon_files[$file_num])) ; 
	print DECONFILE "$current_file\n" ;
}

for (my $file_num = 0 ; $file_num < @dta_files ; $file_num++)
{
	my $current_file = substr($dta_files[$file_num], length($dta_folder), length($dta_files[$file_num])) ; 
	print DTAFILE "$current_file\n" ;

}



my $found_dta = 0;
my $not_found_dta = 0;

close (DTAFILE) ;
close (DECONFILE) ;

open (DTA_FILE, "<$dta_file") || die "Could not open the concatenated file list from DTA\n" ;
open (DECON_FILE, "<$decon_file") || die "Could not open the concatenated file list from Decon \n" ;
open (OUT_FILE, ">$out_file") || die "Could not open out file\n" ;

my %file_hash ; 
while (<DTA_FILE>)
{
	my $line = $_ ;
	chomp ($line) ;
	my $current_dta = $line;
	$file_hash{$current_dta} = 1;
}



while (<DECON_FILE>)
{
	my $this_line = $_;
	chomp ($this_line) ;
	my $decon_name = $this_line ;
	$total_dta = $total_dta +1 ;

	if (exists($file_hash{$decon_name}))
	{
		$file_hash{$decon_name} = 0;
		$found_dta = $found_dta +1; 
	}
	else
	{
		$file_hash{$decon_name} = 2;
		my $current_file = substr($decon_name, 0, length($decon_name)) ;
		print OUT_FILE "$current_file\n" ;
		$not_found_dta = $not_found_dta + 1;
	}
}


print "Found $found_dta Common, $not_found_dta missing out of $total_dta total \n" ;

print "Done\n" ;
