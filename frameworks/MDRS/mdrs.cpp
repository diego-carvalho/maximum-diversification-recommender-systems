#include "mdrs.h"

using namespace std;

int main(int argc, char **argv)
{
	//char *predFileName = "../../Recommendations-Lists/rec_itemKNN_conv.txt";
	string predFileName = "../../Recommendations-Lists/rec_itemKNN_conv.txt";
	int numPreds = 100;


	std::ifstream file;

	Swarm swarm;

	HashOfHashes hashPred;

	std::cout << "loading predictions...\n"
			  << flush;
	loadPred(predFileName, hashPred, numPreds);

	// for(HashOfHashes::iterator i = hashPred.begin(); i != hashPred.end(); i++) {
	// 	for(Hash::iterator j = i->second.begin(); j != i->second.end(); j++) {
	//     	Swarm[]
	// 	}
	// }

	int userId = hashPred.begin()->first;
	Hash userPred = hashPred.begin()->second;
	cout << userId << '\n';
	for(hash h: userPred){
		for(int id: p){
			cout << id << ' ';
		}
		cout << "-------" << '\n';
	}
	PSO_Discreet(userId, userPred);

	// for(Hash::iterator itemId = userPred.begin(); itemId != userPred.end(); itemId++)
	// {
		// cout << itemId->first << " : " << itemId->second << "\n";
	// }
	


	return 0;
}

void PSO_Discreet(int userId, Hash userPred){
	Swarm swarm = create_particles(userPred, swarmSize, particleSize);

}

Swarm create_particles(Hash userPred, int swarmSize, int particleSize){
	Swarm s;
	int bestCand = round(0.4 * swarmSize);
	int randCand = swarmSize - bestCand; 
	
	// bestCand
	Hash::iterator iteratorPred = userPred.begin();
	for(int i = 0; i < bestCand; i++){
		Particle p;
		for(int j = 0; j < 10; j++){
			p.push_back(iteratorPred->first);
			iteratorPred++;
		}
		s.push_back(p);
	}

	for(Particle p: s){
		for(int id: p){
			cout << id << ' ';
		}
		cout << "-------" << '\n';
	}

	// int count = 0;
	// for(auto& p: userPred)
	// {
		// cout << p.first;
		// if(count > bestCand) break;
		// else count++;
	// }

	return s;	
}



/****************************************************************************************
                             Load Functions
*****************************************************************************************/

void loadPred(string predFile, HashOfHashes &hashPred, int numPreds)
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
