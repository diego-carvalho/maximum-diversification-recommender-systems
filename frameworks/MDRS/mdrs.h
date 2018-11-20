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

typedef std::unordered_map<int, float> Hash;		// INT: ID do item	  - FLOAT: valor do item
typedef std::unordered_map<int, Hash> HashOfHashes; // INT: ID do usuário - HASH: lista do usuário

typedef vector<int> Particle;   // Particula que contem: (First: ID do Item, Second: Valor)
typedef vector<Particle> Swarm; // Enxame de particulas

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

int swarmSize = 10;
int particleSize = 10;

int main(int argc, char **argv);

void PSO_Discreet(int userId, Hash userPred);

Swarm create_particles(Hash userPred, int swarmSize, int particleSize);

void loadPred(string predFile, HashOfHashes &hashPred, int numPreds);

void string_tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters);

/*void *getMetrics(void *arg);

inline double probabilityOfRelevance(double rating);

double normalizedConstant(int listSize);

inline double conditionalRankDiscount(int rank1, int rank2);

double conditionalNormalization(int selectedRank, int user, HashOfHashes &testData, HashOfHashes &hashPred, double C);

float calculatePearsonSimilarity(int firstItem, int secondItem, HashOfHashes &itemRatings);

float retrieveItemsSimilarity(int item1, int item2, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings);

void diversityEILD(int user, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double C, double &EILD, double &ILD);

void noveltyDiscoveryEPC(int user, unsigned int numUsers, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &itemRatings, double C, double &EPC_r, double &EPC);

void noveltyEPD(int user, HashOfHashes &trainData, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double C, double &EPD_r, double &EPD);

void loadTrainData(char *trainFile, HashOfHashes &itemRatings, HashOfHashes &trainData);

void loadTestData(char *testFile, HashOfHashes &testData);

int getArgs(int argc, char **argv, char **baseFile, char **predFile, char **testFile, char **outFile, int *numThreads, int *numPreds);

void printUsage();*/

#endif
