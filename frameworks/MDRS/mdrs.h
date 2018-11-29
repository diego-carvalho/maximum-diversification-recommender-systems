#ifndef GETMETRICS_H
#define GETMETRICS_H

#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <unordered_map>
//#include <pthread.h>
//#include <getopt.h>

using namespace std;

// diversify
typedef std::unordered_map<int, float> Hash;		// INT: ID do item	  - FLOAT: valor do item
typedef std::unordered_map<int, Hash> HashOfHashes; // INT: ID do usuário - HASH: lista do usuário

//pso
typedef std::unordered_map<int, vector<int>> VectorOfUser; // INT: ID do usuário - Vector: lista com os id de itens

//typedef vector<int> Particle;   // Particula que contem: (First: ID do Item, Second: Valor)
struct Element{
	int id;
	int pos;

	Element(int id, int pos){
		this->id = id;
		this->pos = pos;
	}
};
struct Particle {
	vector<Element> element;
	vector<Element> pBest;
	float pBest_fo;
	float relBest;
	float divBest;
	Particle():pBest_fo(0), relBest(0), divBest(0){}
};
struct GBest {
	vector<Element> element;
	float fo;
	float rel;
	float div;
	GBest():fo(0), rel(0), div(0){}
};
typedef vector<Particle> Swarm; // Enxame de particulas
typedef std::unordered_map<int, GBest> GBestOfUser; // INT: ID do usuário - Vector: lista com os id de itens

/* estrutura que define os parametros para funcao da thread */
/*struct pthread_param {
	int threadId;
	int numThreads;
	int numPreds;
	HashOfHashes* itemRatings;
	HashOfHashes* hashPred;
	HashOfHashes* hashSimilarity;
	HashOfHashes* testData;
	HashOfHashes* trainData;
	char *outFile;
};*/

int main(int argc, char **argv);

GBest PSO_Discreet(int userId, VectorOfUser &userPred, VectorOfUser &hashFeature, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa, int iter_max, int swarmSize, int particleSize);

void calculate_fo(Particle& p, int userId, VectorOfUser &hashFeature, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa, int swarmSize);

int roulette(float w, float c1, float c2);

void shuffle(vector<int> &vet, int vetSize);

Swarm create_particles(vector<int> &vectorPred, int swarmSize, int particleSize, int numPreds);

bool findPosElement(int pos, vector<Element> elements);

bool findIdElement(int id, vector<Element> elements);

void loadPred(string predFile, HashOfHashes &hashPred, VectorOfUser &userPred, int numPreds);

void loadFeature(string featureFile, VectorOfUser &hashFeature);

void loadTrainData(string trainFile, HashOfHashes &itemRatings, HashOfHashes &trainData);

void loadTestData(string testFile, HashOfHashes &testData);

void string_tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters);

float getDiv(vector<Element> &element, VectorOfUser &featureFile);

float retrieveItemsSimilarity(int item1, int item2, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings);

void diversityILD(int user, HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double &ILD);

double getILD(HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int userId, int numPreds);

float calculatePearsonSimilarity(int firstItem, int secondItem, HashOfHashes &itemRatings);

/*

void noveltyDiscoveryEPC(int user, unsigned int numUsers, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &itemRatings, double C, double &EPC_r, double &EPC);

inline double conditionalRankDiscount(int rank1, int rank2);

double normalizedConstant(int listSize);

double conditionalNormalization(int selectedRank, int user, HashOfHashes &testData, HashOfHashes &hashPred, double C);

inline double probabilityOfRelevance(double rating);

void noveltyEPD(int user, HashOfHashes &trainData, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double C, double &EPD_r, double &EPD);

int getArgs(int argc, char **argv, char **baseFile, char **predFile, char **testFile, char **outFile, int *numThreads, int *numPreds);

void printUsage();*/

#endif
