my $dta_file = "C:\\PNL\\LTE\\Proteomics\\DtaCreator\\validate\\dta_file_list.txt" ;
my $decon_file = "C:\\PNL\\LTE\\Proteomics\\DtaCreator\\validate\\decon_file_list.txt" ;
my $diff_file = "C:\\PNL\\LTE\\Proteomics\\DtaCreator\\validate\\charge_validate.txt" ;
my $out_file = "C:\\PNL\\LTE\\Proteomics\\DtaCreator\\validate\\analyze_list.txt" ;

open(DECONFILE, "<$decon_file") || die "Could not open output file\n";
open(DTAFILE, "<$dta_file") || die "Could not open output file\n";
open(DIFF_FILE, "<$diff_file") ||die "Could not open diff file \n" ;
open(OUT_FILE, ">$out_file") || die "Could not open out file \n" ; 

my %file_hash ;
while(<DIFF_FILE>)
{
	my $line = $_ ;
	chomp ($line) ;
	my $name = $line ;
	my $start_index =  length($name)-5;
	my $end_index = length($name)-4;	
	my $charge = substr($name, $start_index, $end_index-$start_index) ; 	
	if ($charge eq 1)
	{
		my $current_dta = substr($name, 0, $start_index-1) ; 	
		$file_hash{$current_dta} = 2;	 	
	}
#	if ($charge eq 3)
#	{
#		my $current_dta = substr($name, 0, $start_index-1) ; 	
#		$file_hash{$current_dta} = 3;	
#	}
}

my $count = 0;


while (<DTAFILE>)
{
	my $this_line = $_;
	chomp ($this_line) ;
	my $this_name = $this_line ;
	my $this_start_index =  length($this_name)-5;
	my $this_end_index = length($this_name)-4;
	my $this_charge = substr($this_name, $this_start_index, $this_end_index-$this_start_index) ;		
	
	if ($this_charge eq 3)
	{
		my $this_dta = substr($this_line, 0, $this_start_index-1)  ;		
		if (exists($file_hash{$this_dta}))
		{
			print "$this_dta \n" ; 
			print OUT_FILE "$this_dta \n" ;
			$count = $count +1 ; 
		}
	}
}

print "Found $count\n" ;



