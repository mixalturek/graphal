set terminal png
set output "log.png"

set xrange [0:3]
set xtic ("" 0,"" 1,"" 2, "" 3)
set label 1 "variables" at 0.5, graph -0.03, 0 centre norotate
set label 2 "arrays" at 1.5, graph -0.03, 0 centre norotate
set label 3 "functions" at 2.5, graph -0.03, 0 centre norotate

set ylabel "time [s]"

set grid
set key left
set boxwidth 0.15
set style fill solid 1.0

plot	"cpp.dat" using ($1+0.25):2 title "c++" with boxes,\
	"perl.dat" using ($1+0.45):2 title "perl" with boxes,\
	"bbd.dat" using ($1+0.65):2 title "bbd" with boxes
