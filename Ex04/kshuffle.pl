#!/usr/bin/perl -w
# -*-Perl-*-
# Last changed Time-stamp: <2010-04-14 15:52:59 xtof>

use Clone qw(clone);
use Data::Dumper;
use Getopt::Long;
use List::Util qw(shuffle);
use constant {ID =>0, POS =>1, NEIGHS => 2, SEEN=>3, NEXT => 4};
use warnings;
use strict;

my $k=2;
my $N=1; # number of shuffled sequences;
my $verbose = 0;

GetOptions("k=i" =>\$k, "n=i" => \$N, "v+" => \$verbose);

my $seq = <>;
chomp $seq;
$Data::Dumper::Indent = 0;

print kshuffle($seq), "\n" for (1..$N);


sub kshuffle {
    $seq  = shift;
   # build the multi-graph of (k-1)-lets. The Graph is stored in a hash
   # where keys are the (k-1)-lets, and values is a list containing the list
   # of neighbors (outgoing edges) plus some additional info
    my $nid=0;
    my $plet = "";
    my %vert = (); # hash encoding the Graph
    my @vert;      # array mapping fomr IDs to hash entries
    for my $i (0..length($seq)-$k+1) {
	my $id;
	my $clet = substr($seq,$i,$k-1);
	if (!exists($vert{$clet})) {
	    $vert[$nid] = $vert{$clet} = [$nid, $i, [], 0, undef];
	    $id = $nid++;
	} else {
	    $id = $vert{$clet}->[ID];
	}
	if ($i>0) {
	    push @{$vert{$plet}->[NEIGHS]}, $id;
	}
	$plet = $clet;
    }


    # Generate an arborescence via random walk that visits every vertex
    # The arborescence contains for each vertex the last outgoing edge
    # used along the random walk (stored in NEXT)
    my $nlets =  @vert;
    my $visited = 1;
    my $root = $vert{substr($seq, -($k-1))};
    $root->[SEEN]=1;

    for my $i (0..$nlets-1) {
	my $c = $i;
	while (!$vert[$c]->[SEEN]) {
	    my $neighs = $vert[$c]->[NEIGHS];
	    my $next = $neighs->[rand @$neighs];
	    $vert[$c]->[NEXT] = $next;
	    $c = $next;
	}
	$c = $i;
	while (!$vert[$c]->[SEEN]) {
	    $vert[$c]->[SEEN]++;
	    $c = $vert[$c]->[NEXT];
	}
    }

    # Generate Euler path from arborescence
    # For each vertex bring the list of neighbors into a random order, except
    # that the NEXT edge is the last one.

    $root->[NEXT] = $root;
    foreach my $v (@vert) {

      my $neighs = $v->[NEIGHS];
      my $nn = @$neighs;
      my $next = $v->[NEXT];

      foreach $_ (@{$neighs}) { # swap the NEXT element into last position
	($_, $neighs->[-1]) = ($neighs->[-1], $_) if $_ == $next;
      }
      # shufffle all except last element
      if ($v == $root) {
	@$neighs = shuffle @$neighs;
      } else {
	@$neighs[0..$nn-2] = shuffle @$neighs[0..$nn-2] if @$neighs>2;
      }
    }


    # Finally just walk the graph following the edges in order

    my $rseq = substr($seq, 0, $k-1); # Initialize the shuffled sequence

    my $current = 0; # start vertex has ID 0
    while (1) {
	$current = shift @{$vert[$current]->[NEIGHS]};
	last unless defined $current;
	$rseq .= substr($seq, $vert[$current]->[POS]+$k-2, 1);
    }

    return $rseq;
}

__END__
