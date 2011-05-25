#! usr/bin/perl -w

use strict;
use warnings;

my @sequence;


system "stty -cbreak < /dev/tty > /dev/tty 2>&1";
while ((my $key=getc))
{
    push(@sequence, $key);
    last if $key eq "q";

};
system "stty cbreak < /dev/tty > /dev/tty 2>&1";

pop(@sequence);




for (my $m = 0; $m <= $#sequence; $m++)
{
    my $n = 1;
    my $number = int(rand(($#sequence -$n)));
    my $a = $sequence[$number];
    my $b = $sequence[$#sequence -$m];

    splice(@sequence, $number, 1, $b);
    splice(@sequence, ($#sequence -$m), 1, $a);


    $n++;
};

print @sequence, "\n";
