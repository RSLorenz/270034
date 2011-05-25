#! usr/bin/perl -w

######################################################################
# Nimmt eine DNA Sequenz als Input und tauscht von hinten aus gehend
# jede einzelne Base mit einer zufälligen anderen Base aus der Sequenz
######################################################################


use strict;
use warnings;

my @sequence;

# Input Sequenz, jede Base wird als einzelne Position in den Array eingelesen
system "stty -cbreak < /dev/tty > /dev/tty 2>&1";
while ((my $key=getc))
{
    push(@sequence, $key);
    last if $key eq "q";

};
system "stty cbreak < /dev/tty > /dev/tty 2>&1";

# Das q(uit) zum beenden wird aus dem array entfernt

pop(@sequence);



# jetzt werden die Elemente vertauscht

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
