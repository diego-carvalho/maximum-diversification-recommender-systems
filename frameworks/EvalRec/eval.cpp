#include "eval.h"

using namespace std;

int MAX_RATING;

int main(int argc, char **argv)
{
	//string predFileName = "../../Recommendations-Lists/rec_itemKNN_5_conv.txt";
	//string predFileName = "../../Recommendations-Lists/rec_userKNN_5_conv.txt";
	//string predFileName = "../../Recommendations-Lists/rec_MostPopular_5_conv.txt";
	string predFileName = "../../Recommendations-Lists/rec_WRMF_5_conv.txt";
	string trainFileName = "../../Datasets/ML-1M/ratings_train.txt";
	string testFileName = "../../Datasets/ML-1M/ratings_test.txt";
	string featureFileName = "../../Datasets/ML-1M/featuresItems.txt";
	int numPreds = 5;

	std::ifstream file;
	srand(time(NULL));

	HashOfHashes trainData;
	HashOfHashes testData;
	HashOfHashes itemRatings;
	HashOfHashes hashSimilarity;
	HashOfHashes hashPred;
	VectorOfUser userPred;
	VectorOfUser hashFeature;
	GBestOfUser gbestUser;

	

	std::cout << "loading predictions...\n"
			  << flush;
	loadPred(predFileName, hashPred, userPred, numPreds);

	std::cout << "loading test data...\n"
			  << flush;
	loadTestData(testFileName, testData);

	std::cout << "loading training data...\n"
			  << flush;
	loadTrainData(trainFileName, itemRatings, trainData);

	std::cout << "loading feature data...\n"
			  << flush;
	loadFeature(featureFileName, hashFeature);

	vector<PrintData> vecPrint;

	for (int userId = 1; userId <= 500; userId++){

		Particle p;
		//get pred itens
		for(int i: userPred[userId]){
			Element e(i, 0);
			p.element.emplace_back(e);
		}

		// double diversify = 0;
		float diversify = 0;
		// diversify = getILD(testData, p.element, hashSimilarity, itemRatings, userId, numPreds);
		diversify = getDiv(p.element, hashFeature);

		PrintData printData = findAccuracy(userId, trainData, testData, userPred[userId], diversify);
		vecPrint.push_back(printData);

	}

	//writeToFile(vecPrint, "../../Evaluations/Standard/ItemKNN/eval.txt");
	//writeToFile(vecPrint, "../../Evaluations/Standard/UserKNN/eval.txt");
	//writeToFile(vecPrint, "../../Evaluations/Standard/MostPopular/eval.txt");
	writeToFile(vecPrint, "../../Evaluations/Standard/WRMF/eval.txt");

	return 0;
}

PrintData findAccuracy(int userId, HashOfHashes &trainData, HashOfHashes &testData, vector<int> &vectorPred, float diversify)
{
	float userMean = 0;
	float acc = 0;
	float accRel = 0;

	Hash testUser = testData[userId];
	Hash trainUser = trainData[userId];

	// Média é no treino
	for (auto &&i : trainUser)
		userMean += i.second;

	userMean /= trainUser.size();
	//cout << "Média: " << userMean << "\n";

	// Acurácia é no teste
	for (auto &&i : vectorPred)
	{
		Hash::iterator it = testUser.find(i);
		// Caso diferente, user tem o item em sua lista
		if (it != testUser.end())
		{
			++acc;
			// Nota do usuário pro item é maior que a média
			if (it->second >= userMean)
				++accRel;
		}
	}

	acc /= vectorPred.size();
	accRel /= vectorPred.size();

	return PrintData(userId, acc, accRel, diversify);
}

void writeToFile(vector<PrintData>& vecPrint, string filePath)
{
	ofstream myFile(filePath);
	if (myFile.is_open())
	{
		for (auto &&i : vecPrint)
		{
			myFile << i.userID << "\t" << i.acc << "\t" << i.accRel << "\t" << i.div << "\n";
		}
		myFile.close();
	}
}

void writeToFile(HashOfHashes& hashPred, GBestOfUser& allGBests, string filePath)
{
	ofstream myFile(filePath);
	if (myFile.is_open())
	{
		for (auto&& user : hashPred)
		{
			myFile << user.first << "\t";
			for(auto&& element : allGBests[user.first].element)
			{
				myFile << element.id << ":" << element.pos << "\t";
			}
			myFile << "\n";
		}
		myFile.close();
	}
}

/****************************************************************************************
                             Diversify Functions
*****************************************************************************************/

float getDiv(vector<Element> &element, VectorOfUser &hashFeature)
{
	vector<int> featureFinal = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (Element e : element)
	{
		vector<int> featureCurrent = hashFeature[e.id];
		for (unsigned int i = 0; i < featureCurrent.size(); i++)
		{
			if ((featureFinal[i] + featureCurrent[i]) >= 1)
			{
				featureFinal[i] = 1;
			}
			else
			{
				featureFinal[i] = 0;
			}
		}
	}

	int sum = 0;
	for (unsigned int i = 0; i < featureFinal.size(); i++)
	{
		sum += featureFinal[i];
	}
	return (float)sum / featureFinal.size();
}

double getILD(HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int userId, int numPreds)
{

	double ILD;

	diversityILD(userId, testData, particle, hashSimilarity, itemRatings, ILD);

	return ILD;
}

void diversityILD(int user, HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double &ILD)
{
	int l;
	int itemL;
	int itemK;
	double distance_lk;
	double pearson;
	double sum = 0.0;
	int numRecommendations;

	numRecommendations = (int)particle.size();

	int k = 1;
	for (unsigned int i = 0; i < particle.size(); i++)
	{
		itemK = particle[i].id;
		l = 1;

		for (unsigned int j = 0; j != i; j++)
		{
			if (k != l)
			{
				itemL = particle[j].id;
			}

			if (l < k)
			{
				pearson = (retrieveItemsSimilarity(itemL, itemK, hashSimilarity, itemRatings) + 1) / 2;
				distance_lk = 1 - pearson;
				sum += distance_lk;
			}
			l++;
		}
		k++;
	}

	ILD = 2.0 / ((double)(numRecommendations * (numRecommendations - 1))) * sum;
}

float retrieveItemsSimilarity(int item1, int item2, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings)
{
	int firstItem = item1;
	int secondItem = item2;
	float similarity;

	HashOfHashes::iterator itr1;
	Hash::iterator itr2;

	if (item1 > item2)
	{
		firstItem = item2;
		secondItem = item1;
	}

	itr1 = hashSimilarity.find(firstItem);
	if (itr1 != hashSimilarity.end())
	{

		itr2 = hashSimilarity[firstItem].find(secondItem);
		if (itr2 != hashSimilarity[firstItem].end())
			return hashSimilarity[firstItem][secondItem];
	}

	//calcula nova similaridade
	similarity = calculatePearsonSimilarity(firstItem, secondItem, itemRatings);

	//atualiza similaridade
	hashSimilarity[firstItem][secondItem] = similarity;

	return similarity;
}

float calculatePearsonSimilarity(int firstItem, int secondItem, HashOfHashes &itemRatings)
{
	float meanX;
	float meanY;
	float pearson = 0.0;
	float squaredDifferencesX;
	float squaredDifferencesY;
	float sumOfProduct = 0.0;

	HashOfHashes::iterator itr1;
	HashOfHashes::iterator itr2;

	Hash::iterator itr3;
	Hash::iterator itr4;

	//verify whether both item exist in the training set
	itr1 = itemRatings.find(firstItem);
	itr2 = itemRatings.find(secondItem);

	if (itr1 == itemRatings.end() || itr2 == itemRatings.end())
		return pearson;

	meanX = 0.0;
	for (itr3 = itemRatings[firstItem].begin(); itr3 != itemRatings[firstItem].end(); itr3++)
		meanX += itr3->second;

	meanY = 0.0;
	for (itr4 = itemRatings[secondItem].begin(); itr4 != itemRatings[secondItem].end(); itr4++)
		meanY += itr4->second;

	sumOfProduct = 0.0;
	squaredDifferencesX = 0.0;
	for (itr3 = itemRatings[firstItem].begin(); itr3 != itemRatings[firstItem].end(); itr3++)
	{
		squaredDifferencesX += (itr3->second - meanX) * (itr3->second - meanX);

		itr4 = itemRatings[secondItem].find(itr3->first);
		if (itr4 != itemRatings[secondItem].end())
		{
			sumOfProduct += (itr3->second - meanX) * (itr4->second - meanY);
		}
	}

	squaredDifferencesY = 0.0;
	for (itr4 = itemRatings[secondItem].begin(); itr4 != itemRatings[secondItem].end(); itr4++)
	{
		squaredDifferencesY += (itr4->second - meanY) * (itr4->second - meanY);
	}

	if ((squaredDifferencesX > 0.0) && (squaredDifferencesY > 0))
	{
		pearson = sumOfProduct / (sqrt(squaredDifferencesX) * sqrt(squaredDifferencesY));
	}

	return pearson;
}

/****************************************************************************************
                             Load Functions
*****************************************************************************************/

void loadPred(string predFile, HashOfHashes &hashPred, VectorOfUser &userPred, int numPreds)
{
	std::ifstream file;
	std::string line;
	std::string itemId;
	std::string rating;
	std::vector<std::string> vetor;
	int userId;
	int vectorSize;

	file.open(predFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << predFile << endl;
		std::exit(-1);
	}

	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, " ");
		userId = atoi(vetor[0].c_str());
		vectorSize = (int)vetor.size();

		for (int i = 1; i < vectorSize && i <= numPreds; i++)
		{
			std::stringstream ssBuffer(vetor[i]);
			getline(ssBuffer, itemId, ':');
			getline(ssBuffer, rating, ':');

			hashPred[userId][atoi(itemId.c_str())] = atof(rating.c_str());
			userPred[userId].push_back(atoi(itemId.c_str()));
		}
	}

	file.close();
}

void loadFeature(string featureFile, VectorOfUser &hashFeature)
{
	std::ifstream file;
	std::string line;
	std::vector<std::string> vetor;
	int userId;
	vector<int> features;
	int vectorSize;

	file.open(featureFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << featureFile << endl;
		std::exit(-1);
	}

	getline(file, line);
	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		features.clear();
		string_tokenize(line, vetor, " ");
		userId = atoi(vetor[0].c_str());
		vectorSize = (int)vetor.size();

		for (int i = 1; i < vectorSize; i++)
		{
			features.push_back(atoi(vetor[i].c_str()));
		}

		if (!features.empty())
			hashFeature[userId] = features;
	}

	file.close();
}

void loadTrainData(string trainFile, HashOfHashes &itemRatings, HashOfHashes &trainData)
{
	std::ifstream file;
	std::string line;
	int itemId;
	float rating;
	std::vector<std::string> vetor;
	int userId;

	file.open(trainFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << trainFile << endl;
		std::exit(-1);
	}

	MAX_RATING = -1;
	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, "::");
		userId = atoi(vetor[0].c_str());
		itemId = atoi(vetor[1].c_str());
		rating = atof(vetor[2].c_str());

		if (rating > MAX_RATING)
			MAX_RATING = rating;

		itemRatings[itemId][userId] = rating;
		trainData[userId][itemId] = rating;
	}

	file.close();
}

void loadTestData(string testFile, HashOfHashes &testData)
{
	std::ifstream file;
	std::string line;
	int itemId;
	float rating;
	std::vector<std::string> vetor;
	int userId;

	file.open(testFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << testFile << endl;
		std::exit(-1);
	}

	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, "::");
		if (((int)vetor.size()) > 2)
		{
			userId = atoi(vetor[0].c_str());
			itemId = atoi(vetor[1].c_str());
			rating = atof(vetor[2].c_str());

			testData[userId][itemId] = rating;
		}
	}

	file.close();
}

void string_tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters)
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}
