set term post enh
set output "auto2.eps"
set grid
set xlabel "Semester"
set ylabel "% of autmatic choices"
plot 'auto2.dat' using 1:2 title "Automatic choices by semester "with linespoints 
