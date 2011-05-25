#! usr/bin/perl -w

######################################################################
# Code erstellt aus einer Sequenz eine radom-sequence mit gleicher 
# Nukleotid Verteilung
######################################################################


use strict;
use warnings;

my @sequence;

    my $A = 0;
    my $U = 0;
    my $C = 0;
    my $G = 0;

# Input Sequenz, jede Base wird als einzelne Position in den Array eingelesen
system "stty -cbreak < /dev/tty > /dev/tty 2>&1";
while ((my $key=getc))
{
    push(@sequence, $key);
    last if $key eq "q";

};
system "stty cbreak < /dev/tty > /dev/tty 2>&1";

pop(@sequence);
# Das q(uit) zum beenden wird aus dem array entfernt

# Dann werden die einzelnen Basen ihrer Art nach (C, T, A, U) gezählt

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

# Arrays werden erstellt mit Anzahl der Basen
my @Aarray = ('A') x $A;
my @Carray = ('C') x $C;
my @Garray = ('G') x $G;
my @Uarray = ('U') x $U;

my @random_array = @Aarray;

# Jetzt nehme ich meine Aarray (der mit genau so viel A's vollgepackt ist, wie in der 
# Sequenz vorhanden waren und füge an zufälligen Stellen meinen Carray (der genausoviel
# C's wie die ursprüngliche Sequenz hat) ein, das gleiche mache ich mit Guanin und Uracil-
# arrays

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

