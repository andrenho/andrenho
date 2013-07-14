set term post enh
set output "temp.eps"
set grid
set xlabel "Semester"
set ylabel "% of recommendations"
plot 'temp.dat' using 1:2 title "Recommendations by semester " with linespoints,\
 'temp.dat' using 1:3 title "Test" with linespoints 
