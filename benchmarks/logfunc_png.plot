set terminal png
set output "logfunc.png"

set xrange [0:2]
set yrange [0:]
set xtic ("" 0,"" 1,"" 2, "" 3)
set label 1 "without return" at 0.5, graph -0.03, 0 centre norotate
set label 2 "with return" at 1.5, graph -0.03, 0 centre norotate

set ylabel "time [s]"

set grid
set key left
set boxwidth 0.5
set style fill solid 1.0

plot	"logfunc.txt" using ($1+0.5):2 with boxes notitle
