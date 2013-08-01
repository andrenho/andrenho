set termoption dash
set term post enh
set output "temp2.eps"
set grid
set xlabel "Semester"
set ylabel "% of recommendations"
set key off
set style line 1 lt 1 lc rgb "black" lw 3
set style line 2 lt 2 lc rgb "black" lw 2
plot \
  'temp2.dat' using 1:2 ls 1 title "With rule change" with linespoints,\
  'temp2.dat' using 1:3 ls 2 title "Without rule change" with linespoints,\
  'temp2.dat' using 1:4 ls 2 title "Without rule change" with linespoints
