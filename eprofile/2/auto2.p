set term post enh
set output "auto2.eps"
set grid
set xlabel "Semester"
set ylabel "% of recommendations"
plot 'auto2.dat' using 1:2 title "Recommendations by semester "with linespoints 
