
d="UserKNN"

cd $d

#for i in {1..10}
for i in `seq 1 10`;
do

	cd Teste$i

	sudo rm acc.txt
	sort -f -r -k2 eval.txt > acc.txt
	chmod 777 acc.txt
	sudo rm acc_Rel.txt
	sort -f -r -k3 eval.txt > acc_Rel.txt
	chmod 777 acc_Rel.txt
	sudo rm div.txt
	sort -f -r -k4 eval.txt > div.txt
	chmod 777 div.txt

	gnuplot plotEval.gp
	chmod 777 acc.eps
	chmod 777 accRel.eps
	chmod 777 div.eps

	cd ..
	echo "output: $i"

done
cd ..
