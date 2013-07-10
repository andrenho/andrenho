set term post enh
set output "auto.eps"
set grid
set xlabel "Semester"
set ylabel "% of recommendations"
plot 'auto.dat' using 1:2 title "Recommendations by semester "with linespoints 
