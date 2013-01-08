set term post enh
set output "auto.eps"
set grid
set xlabel "Semester"
set ylabel "% of autmatic choices"
plot 'auto.dat' using 1:2 title "Automatic choices by semester "with linespoints 
