#! /usr/bin/gnuplot -persist "filename" "filename1"

set boxwidth 0.5
set style fill solid

set terminal wxt 0
set term png
set output "Optimization/hash.png"
plot filename using 1:2 lc "#00c000" with boxes title filename, \
     filename1 using 1:2 lc "#ff0000" with boxes title filename1
unset output
set terminal wxt
replot 