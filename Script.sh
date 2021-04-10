#! /usr/bin/gnuplot -persist "filename" "filename1" "filename2", "filename3", "filename4" "filename5" "filename6" "filename7" "filename8"

set boxwidth 0.5
set style fill solid

set terminal wxt 0
set term png
set output "Images/0.png"
plot filename  using 1:2 lc "#000080" with boxes title filename,  \
     filename1 using 1:2 lc "#9400d3" with boxes title filename1, \
     filename2 using 1:2 lc "#00eeee" with boxes title filename2, \
     filename3 using 1:2 lc "#a08020" with boxes title filename3, \
     filename4 using 1:2 lc "#ff1493" with boxes title filename4, \
     filename5 using 1:2 lc "#0080ff" with boxes title filename5, \
     filename6 using 1:2 lc "#ffa500" with boxes title filename6, \
     filename7 using 1:2 lc "#00c000" with boxes title filename7, \
     filename8 using 1:2 lc "#ff0000" with boxes title filename8
unset output
set terminal wxt
replot 

set terminal wxt 1
set term png
set output "Images/1.png"
plot filename1 using 1:2 lc "#9400d3" with boxes title filename1,  \
     filename2 using 1:2 lc "#00eeee" with boxes title filename2,  \
     filename3 using 1:2 lc "#a08020" with boxes title filename3,  \
     filename4 using 1:2 lc "#ff1493" with boxes title filename4,  \
     filename5 using 1:2 lc "#0080ff" with boxes title filename5,  \
     filename6 using 1:2 lc "#ffa500" with boxes title filename6,  \
     filename7 using 1:2 lc "#00c000" with boxes title filename7,  \
     filename8 using 1:2 lc "#ff0000" with boxes title filename8   

set terminal wxt 2
set term png
set output "Images/2.png"
plot filename2 using 1:2 lc "#00eeee" with boxes title filename2, \
     filename4 using 1:2 lc "#ff1493" with boxes title filename4, \
     filename5 using 1:2 lc "#0080ff" with boxes title filename5, \
     filename6 using 1:2 lc "#ffa500" with boxes title filename6, \
     filename7 using 1:2 lc "#00c000" with boxes title filename7, \
     filename8 using 1:2 lc "#ff0000" with boxes title filename8
unset output
set terminal wxt
replot

set terminal wxt 3
set term png
set output "Images/3.png"
plot filename4 using 1:2 lc "#ff1493" with boxes title filename4, \
     filename5 using 1:2 lc "#0080ff" with boxes title filename5, \
     filename6 using 1:2 lc "#ffa500" with boxes title filename6, \
     filename7 using 1:2 lc "#00c000" with boxes title filename7, \
     filename8 using 1:2 lc "#ff0000" with boxes title filename8
unset output
set terminal wxt
replot

set terminal wxt 4
set term png
set output "Images/4.png"
plot filename4 using 1:2 lc "#ff1493" with boxes title filename4
unset output
set terminal wxt
replot

set terminal wxt 5
set term png
set output "Images/5.png"
plot filename5 using 1:2 lc "#0080ff" with boxes title filename5
unset output
set terminal wxt
replot

set terminal wxt 6
set term png
set output "Images/6.png"
plot filename6 using 1:2 lc "#ffa500" with boxes title filename6
unset output
set terminal wxt
replot

set terminal wxt 7
set term png
set output "Images/7.png"
plot filename7 using 1:2 lc "#00c000" with boxes title filename7
unset output
set terminal wxt
replot

set terminal wxt 8
set term png
set output "Images/8.png"
plot filename8 using 1:2 lc "#ff0000" with boxes title filename8
unset output
set terminal wxt
replot


set terminal wxt 9
set term png
set output "Images/9.png"
plot filename4 using 1:2 lc "#ff1493" with boxes title filename4, \
     filename5 using 1:2 lc "#a00080ff" with boxes title filename5
unset output
set terminal wxt
replot