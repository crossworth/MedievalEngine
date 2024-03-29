#!/usr/bin/perl -w

# Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer. 
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution. 
# 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission. 
#
# THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# "find-extra-includes" script for Web Kit Open Source Project

# From http://trac.webkit.org/browser/branches/old/safari-3-2-branch/WebKitTools/Scripts/find-extra-includes

use strict;
use File::Find;

find(\&wanted, @ARGV ? @ARGV : ".");

my %paths;
my %includes;

sub wanted
{
    my $file = $_;

    if ($file eq "icu") {
        $File::Find::prune = 1;
        return;
    }

    if ($file !~ /^\./ && $file =~ /\.(h|cpp|c|mm|m)$/) {
        $paths{$file} = $File::Find::name;
        open FILE, $file or die;
        while (<FILE>) {
            if (m-^\s*#\s*(include|import)\s+["<]((\S+/)*)(\S+)[">]-) {
                my $include = ($2 eq "sys/" ? $2 : "") . $4;
                $includes{$file}{$include}++;
            }
        }
        close FILE;
    }
}

my %totalIncludes;

sub fillOut
{
    my ($file) = @_;

    return if defined $totalIncludes{$file};

    for my $include (keys %{ $includes{$file} }) {
        $totalIncludes{$file}{$include} = 1;
        fillOut($include);
        for my $i (keys %{ $totalIncludes{$include} }) {
            $totalIncludes{$file}{$i} = 1;
        }
    }
}

sub check
{
    my ($file) = @_;

    for my $include (keys %{ $includes{$file} }) {
        fillOut($include);
    }
    for my $i1 (sort keys %{ $includes{$file} }) {
        for my $i2 (keys %{ $includes{$file} }) {
            next if $i1 eq $i2;
            if ($totalIncludes{$i2}{$i1}) {
                my $b1 = $i1;
                my $b2 = $file;
                $b1 =~ s/\..+$//;
                $b2 =~ s/\..+$//;
                print "$paths{$file} does not need to include $i1, because $i2 does\n" if $b1 ne $b2;
                last;
            }
        }
    }
}

for my $file (sort keys %includes) {
    check($file);
}
