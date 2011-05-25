#! usr/bin/perl -w

###########################################################################################
# Manhattan tourist problem or how a hedonist would travel
# Working start at: April 28, 2011 6:06:55 AM GMT+02:00
###########################################################################################
use warnings;
use strict;
use Getopt::Std;
use List::Util qw(max);
use Scalar::Util;
###########################################################################################

my @hmatrix;                                 # Vertikale Gewichtungsmatrix
my @vmatrix;                                 # Horizontale Gewichtungsmatrix
  
print 
"Eingabe der horizontalen Matrix (Trennen durch -Tab-, für jede neue Spalte eine neue Zeile): \n";

while (my $line = <>)                         # einlesen der horizontalen Gewichtungsmatrix
{                                             # eingabe erfolgt standardmäßig als 2x3 matrix
    my @row = split (/\s+/, $line);             
    push (@hmatrix, \@row);  
};

print "Eingabe der vertikalen Matrix: \n";

while (my $line = <>)                         # einlesen der vertikalen Gewichtungsmatrix
{                                             # eingabe erfolgt als 2x3 matrix, d.h. um 90°
    my @row = split (/\s+/, $line);           # im Uhrzeigersinn drehen
    push (@vmatrix, \@row);  
};

###########################################################################################
# Wiedergabe der Matrizen
###########################################################################################

my $how_big_is_my_matrix;

foreach my $ref_zeile (@hmatrix)              # nur zur Überprüfung, ob die Matrizen
{                                             # richtig aufgebaut werden - und zum zählen
    foreach my $spalte (@$ref_zeile)          # um was für eine Matrix es sich  handelt
    { 
       print "$spalte"   
    }
      print "\n";
    $how_big_is_my_matrix ++;
};


foreach my $ref_zeile (@vmatrix)              # nur zur Überprüfung, ob die Matrizen
{                                             # richtig aufgebaut werden - und zum zählen
    foreach my $spalte (@$ref_zeile)          # um was für eine Matrix es sich  handelt
    { 
       print "$spalte"   
    }
      print "\n";
};


###########################################################################################
###########################################################################################

print "\n $how_big_is_my_matrix  \n\n\n";

    
    my @tmp1 = ('0');                         # Aufbau der Manhattan Matrix
    my @tmp2 = ();
    my @tmp3 = ();
    my @tmp4 = ();
    my @tmp5 = ();
    my @tmp6 = ();
    my @tmp7 = ();
    my @tmp8 = ();
    my @tmp9 = ();
    my @tmp10 = ();

    my $ref_tmp1 = \@tmp1;
    my $ref_tmp2 = \@tmp2;
    my $ref_tmp3 = \@tmp3;
    my $ref_tmp4 = \@tmp4;
    my $ref_tmp5 = \@tmp5;
    my $ref_tmp6 = \@tmp6;
    my $ref_tmp7 = \@tmp7;
    my $ref_tmp8 = \@tmp8;
    my $ref_tmp9 = \@tmp9;
    my $ref_tmp10 = \@tmp10;
    my @manhattan_matrix = ($ref_tmp1, $ref_tmp2, $ref_tmp3, $ref_tmp4, $ref_tmp5, $ref_tmp6, 
    $ref_tmp7, $ref_tmp8, $ref_tmp9, $ref_tmp10);


for (my $m = 1; $m <= $how_big_is_my_matrix -1; $m++)
{
    $manhattan_matrix[$m][0] = $manhattan_matrix[$m -1][0] + $vmatrix[0][$m-1]
};

for (my $n = 1; $n <= $how_big_is_my_matrix -1; $n++)
{
    $manhattan_matrix[0][$n] = $manhattan_matrix[0][$n-1] + $hmatrix[0][$n-1]
};

for (my $m = 1; $m <= $how_big_is_my_matrix -1; $m++)
{
    for (my $n = 1; $n <= $how_big_is_my_matrix -1; $n++)
    {
        $manhattan_matrix[$m][$n] = max ($manhattan_matrix[$m-1][$n] + $vmatrix[$n][$m-1]
        , $manhattan_matrix[$m][$n-1] + $hmatrix[$m][$n-1]);
        
    };
};

foreach my $ref_zeile (@manhattan_matrix) 
{
    foreach my $spalte (@$ref_zeile) 
    { 
       print "$spalte \t" 
    }
    print "\n";
};

my @path;
my $new_position;

# print "$manhattan_matrix[$how_big_is_my_matrix -1][$how_big_is_my_matrix-2] - x-1/y-2 \n\n";
# print "$manhattan_matrix[$how_big_is_my_matrix -2][$how_big_is_my_matrix-1] - x-2/y- 1\n\n";
# print " $hmatrix[$how_big_is_my_matrix-1][$how_big_is_my_matrix-2] - horizontale matrix";
# print " $vmatrix[$how_big_is_my_matrix-1][$how_big_is_my_matrix-2] - horizontale matrix";

my $xcoord = $how_big_is_my_matrix;
my $ycoord = $how_big_is_my_matrix;
my $xvma = $how_big_is_my_matrix;
my $yvma = $how_big_is_my_matrix;
my $xhma = $how_big_is_my_matrix;
my $yhma = $how_big_is_my_matrix;

print "$manhattan_matrix[$how_big_is_my_matrix -1][$how_big_is_my_matrix-2] - x-1 + y-2 \n\n";
print "$manhattan_matrix[$how_big_is_my_matrix -2][$how_big_is_my_matrix-1] - x-2 + y- 1\n\n";
print " $vmatrix[$how_big_is_my_matrix-1][$how_big_is_my_matrix-2] \n";
print " $hmatrix[$how_big_is_my_matrix-1][$how_big_is_my_matrix-2] \n";


 
do {
    if (($manhattan_matrix[$xcoord - 1][$ycoord -2] + 
        $hmatrix[$xhma-1][$yhma-2]) >
        ($manhattan_matrix[$xcoord-2][$ycoord -1] + 
        $vmatrix[$xvma-1][$yhma-2]))
    {
            my $a = "osten";
            push(@path, $a);
            print " $manhattan_matrix[$xcoord - 1][$ycoord -2]\n";
            print " $hmatrix[$xhma-1][$yhma-2]\n";
            

            $xcoord =  $xcoord -1;
            $ycoord = $ycoord-2;
            $xvma = $xvma = $xvma -1;
            $yvma = $yvma = $yvma;
            $xhma = $xhma;
            $yhma = $yhma - 2;
    }
    else
    {
            my $a = "süden";
            push(@path, $a);
            print " $manhattan_matrix[$xcoord-2][$ycoord -1] \n";
            $xcoord =  $xcoord -2;
            $ycoord = $ycoord -1;
            $xvma = $xvma = $xvma;
            $yvma = $yvma = $yvma -1;
            $xhma = $xhma -2;
            $yhma = $yhma;

    }
} until($xcoord + $ycoord == 0) ;

print "Maximal erreichbare Anzahl an Sehenswürdigkeiten: "
.$manhattan_matrix[$how_big_is_my_matrix -1][$how_big_is_my_matrix -1] ."\n\n";

print "@path";