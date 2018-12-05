reset 
# set term png 18	#formato da saida do grafico
set term postscript eps 35 enhanced color #formato da saida do grafico
set   autoscale                        # scale axes automatically
#set xtic auto                         # set xtics automatically - distancia dos label
#set ytic auto                           # set ytics automatically
set encoding utf8
#set xtics auto
#set ytics auto
# set yrange [0:60]
set key samplen .5 spacing .9 font ",35"

#set key left bottom
set key at graph 1, 0.8


set output "acc.eps"		#nome de saida
set ylabel "Acurácia" offset 1
set xlabel "Usuários (%)" 
plot "acc.txt" using ((column(0) / 500) * 100):2 title "MDRS a=0.5" with line lw 10 lc "#000000",\

#     "1-CDF-NORM.txt" using (($1 / 233096) * 100):5 title "Top 1 state" with linespoints lw 10 pt 70 ps 2 lc "#000000",\
#	 "3-CDF-NORM.txt" using (($1 / 75072) * 100):5 title "Top 3 state" with linespoints lw 10 pt 71 ps 2 lc "#000000",\
#	 #"average-CDF-NORM.txt" using (($1 / 837509) * 100):5 title "Average" with linespoints lw 10 pt 74 ps 2 lc "#000000"


set output "accRel.eps"		#nome de saida
set ylabel "Acurácia com Relevância" offset 1
set xlabel "Usuários (%)" 
plot "acc_Rel.txt" using ((column(0) / 500) * 100):3 title "MDRS a=0.5" with line lw 10 lc "#000000",\

set output "div.eps"		#nome de saida
set ylabel "Diversidade" offset 1
set xlabel "Usuários (%)" 
plot "div.txt" using ((column(0) / 500) * 100):4 title "MDRS a=0.5" with line lw 10 lc "#000000",\
