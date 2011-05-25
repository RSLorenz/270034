#! usr/bin/perl -w

use strict;
use warnings;

my @sequence;

    my $A = 0;
    my $U = 0;
    my $C = 0;
    my $G = 0;


system "stty -cbreak < /dev/tty > /dev/tty 2>&1";
while ((my $key=getc))
{
    push(@sequence, $key);
    last if $key eq "q";

};
system "stty cbreak < /dev/tty > /dev/tty 2>&1";

pop(@sequence);


for (my $a = 0; $a < $#sequence; $a++)
{
   
    if ($sequence[$a] eq 'A')
    {
         $A++;
    }
    elsif ($sequence[$a] eq 'C')
    {
         $C++;
    }
     elsif ($sequence[$a] eq 'U')
    {
         $U++;
    }
       else 
    {
         $G++;
    };
};

print "C - $C , G - $G, A - $A, U - $U  \n";

my @Aarray = ('A') x $A;
my @Carray = ('C') x $C;
my @Garray = ('G') x $G;
my @Uarray = ('U') x $U;

my @random_array = @Aarray;

while ($#Carray >= 0)
{   
    splice(@random_array, int(rand(($#random_array))), 0, shift(@Carray));
};

while ($#Garray >= 0)
{
    splice(@random_array, int(rand(($#random_array))), 0, shift(@Garray));

};

while ($#Uarray >= 0)
{
    splice(@random_array, int(rand(($#random_array))), 0, shift(@Uarray));

};

print @random_array, "\n";

