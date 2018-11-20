#include "mdrs.h"


int main(int argc, char **argv) {
	//char *predFileName = "../../Recommendations-Lists/rec_itemKNN_conv.txt";
	string predFileName = "../../Recommendations-Lists/rec_itemKNN_conv.txt";
	int numPreds = 10;

	std::ifstream file;

	HashOfHashes hashPred;

	std::cout << "loading predictions...\n" << flush;
	loadPred(predFileName, hashPred, numPreds);

	for(map<int, Hash>::iterator i = hashPred.begin(); i != hashPred.end(); i++) {
		for(map<int, float>::iterator j = i.begin(); j != i.end(); j++) {
        	cout << j << "\n";
		}
    }
	

	return 0;
}


/****************************************************************************************
                             Load Functions
*****************************************************************************************/

void loadPred(string predFile, HashOfHashes &hashPred, int numPreds) {
	std::ifstream file;
	std::string line;
	std::string itemId;
	std::string rating;
	std::vector<std::string> vetor;
	int userId;
	int vectorSize;

	file.open(predFile);

	if(!file.is_open()) {
		std::cout << "\nError opening file!" << endl;
		std::cout << predFile << endl;
		std::exit(-1);
	}

	while(!file.eof()) {
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, " ");
		userId = atoi(vetor[0].c_str());
		vectorSize = (int) vetor.size();
		
		for(int i=1; i<vectorSize && i<=numPreds; i++){
			std::stringstream ssBuffer(vetor[i]);
			getline(ssBuffer, itemId, ':');
			getline(ssBuffer, rating, ':');
			
			hashPred[userId][atoi(itemId.c_str())] = atof(rating.c_str());
		}

	}
	
	file.close();
}


void string_tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters) {
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}
