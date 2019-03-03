#!/usr/bin/awk -f
# This file takes a 41 field version of the NYC Open Data Tree Census cvs
# and "zeros out" the feilds not required for testing a CSCI 335 project
# this is my first .awk file, so it likely is not pretty to someone familure
# with the awk program -- my apologies. 
# Author: Josiah Nosek
# Date: 3/1/2019
#
# function to clear fields of non-essential values
function zero_col(col,      i) {
    for(i=col; i<=NF; i++) {
        if(i==4 || i==7 || i==8 || i==10 || i==25 || i==26 || i==30 
           || i==38 || i==39)
            $i=$i;
        else
            $i="";
    }
}

BEGIN {
    FS=",";
    OFS=",";
}
{
    zero_col(2);
    # removes non-five digit zip codes
    if(length($7)!=5)
        next;
    # uses the longitude value to determine if the zero_col() function
    # created bad feilds due to embedded commas, and removes them.
    if($39!~"-7")
        next;
}

1
