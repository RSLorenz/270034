#!/usr/bin/perl -w
# -*-Perl-*-
# Last changed Time-stamp: <2008-05-28 14:35:23 xtof>
use strict;
use Data::Dumper;
use List::Util qw/max/;

my @EW     = (); # sights on east-west streets
my @NS     = (); # sights on north-south streets
my @sights = (); # sights[i][j] max number of sight until corner i,j

read_score_matrices();

my $width  = scalar(@{$EW[0]});
my $height = $#EW;

#print "$width, $height\n";

die "matrices have unequal size" 
  unless $height == @NS &&  $width ==  $#{$NS[0]};

fill_DP_array();

# print DP array
dump_LoL(\@sights);

# backtrack optimal path
my $path = backtrack();

# print result
print
    "\nRecommended path (@{[length $path]}):\nGo ", 
    "Go $path to see $sights[-1][-1] sights";
#    " to see ",
#    $sights[-1][-1],
#    " sights \n";

#---
sub fill_DP_array {
  $sights[0][0] = 0;

  # inizialize first row
  for my $j (1..$width) {
    $sights[0][$j] =  $sights[0][$j-1] + $EW[0][$j-1];
  }

  # inizialize first column
  for my $i (1..$height) {
    $sights[$i][0] =  $sights[$i-1][0] + $NS[$i-1][0];
  }

  # fill rest of matrix
  for my $i (1..$height) {
    for my $j (1..$width) {
      $sights[$i][$j] =  max($sights[$i][$j-1] + $EW[$i][$j-1],
			     $sights[$i-1][$j] + $NS[$i-1][$j]);
    }
  }
}

#---
sub backtrack {
  my ($i, $j) = ($height, $width);
  my $path;
  
  while ($i>0 || $j>0) {

    # came from north to i.j 
    if ($i>0 && $sights[$i][$j] == $sights[$i-1][$j] + $NS[$i-1][$j]) {
      $path .= 'S';
      $i--;
      next;
    }

    # came from west to i.j
    if ($j>0 && $sights[$i][$j] == $sights[$i][$j-1] + $EW[$i][$j-1]) {
      $path .= 'E';
      $j--;
      next;
    }
  }

  # backtracked path
  return scalar reverse $path;
}

#---
sub read_score_matrices {
  local $_;
  my $m = \@EW;
  while (<>) {
    next if /^\#/;
    $m = \@NS, next if /^\s*$/;
    push @$m, [split];
  }
}

#---
sub dump_LoL {print join(" ", map{sprintf "%3d", $_} @$_), "\n" for @{shift()}}
