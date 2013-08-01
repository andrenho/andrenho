set term post enh
set output "temp.eps"
set grid
set xlabel "Semester"
set ylabel "% of recommendations"
set key outside box
plot \
  'temp.dat' using 1:2 title "30% similarity" with linespoints,\
  'temp.dat' using 1:3 title "40% similarity" with linespoints,\
  'temp.dat' using 1:4 title "50% similarity" with linespoints,\
  'temp.dat' using 1:5 title "60% similarity" with linespoints,\
  'temp.dat' using 1:6 title "70% similarity" with linespoints,\
