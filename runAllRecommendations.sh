#!/bin/bash

#files=("ML-1M" "ML-10M" "ML-20M" "Amazon/VideoGames/v=5" "Amazon/VideoGames/v=10" "Amazon/Clothes/v=5" "Amazon/Clothes/v=10" "Yahoo/Movies" "ML-Latest/later2012")
files=("ML-1M")

touch log.txt
sudo chmod 777 log.txt
date "+%H:%M:%S   %d/%m/%y" > log.txt
echo "" >> log.txt

for f in "${files[@]}" 
do	

	echo "----------------------------------" >> log.txt
	echo "Dataset " $f >> log.txt
	echo "----------------------------------" >> log.txt

	echo "UserKNN" >> log.txt
	echo "UserKNN"
	item_recommendation --training-file=Datasets/ML-1M/trainSet.csv	 --test-file=Datasets/ML-1M/testSet.csv --recommender=UserKNN --prediction-file=Recommendations-Lists/rec_userKNN.txt --predict-items-number=100 2>> log.txt >> log.txt

	echo "" >> log.txt
	echo "----------------------------------------------------------------------------------" >> log.txt
	echo "" >> log.txt

	echo "ItemKNN" >> log.txt
	echo "ItemKNN"
	item_recommendation --training-file=Datasets/ML-1M/trainSet.csv	 --test-file=Datasets/ML-1M/testSet.csv --recommender=ItemKNN --prediction-file=Recommendations-Lists/rec_itemKNN.txt --predict-items-number=100 2>> log.txt >> log.txt

	echo "" >> log.txt
	echo "----------------------------------------------------------------------------------" >> log.txt
	echo "" >> log.txt

	echo "WRMF" >> log.txt
	echo "WRMF"
	item_recommendation --training-file=Datasets/ML-1M/trainSet.csv	 --test-file=Datasets/ML-1M/testSet.csv --recommender=WRMF --prediction-file=Recommendations-Lists/rec_WRMF.txt --predict-items-number=100 2>>log.txt >> log.txt

	echo "" >> log.txt
	echo "----------------------------------------------------------------------------------" >> log.txt
	echo "" >> log.txt

	echo "MostPopular" >> log.txt
	echo "MostPopular"
	item_recommendation --training-file=Datasets/ML-1M/trainSet.csv	 --test-file=Datasets/ML-1M/testSet.csv --recommender=MostPopular --prediction-file=Recommendations-Lists/rec_MostPopular.txt --predict-items-number=100 2>>log.txt >> log.txt


	echo "" >> log.txt
	echo "----------------------------------------------------------------------------------" >> log.txt
	echo "" >> log.txt

done

