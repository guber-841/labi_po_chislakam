set terminal pngcairo size 1200, 900
set output "graphs/functions.png"

set title "типо апроксимация выражения"
set xlabel "x"
set ylabel "f(x)"
set grid

plot "database/func_values.dat" using 1:2 with lines title "y(x)", \
     "database/aprx_values.dat" using 1:2 with lines title "phi(x)"

unset output