#pragma once

#include <vector>
#include <random>
#include "PutStone.hpp"

using namespace std;

#define RATIO        2
#define MUTATION   100
#define T_SIZE       5

typedef vector<bool> Gene;
typedef pair<Gene, int> GeneP;
typedef vector<GeneP> Genes;

class GA {
private:
	const int block;
	
	const int gene;
	
	mt19937 mt;
	
	Genes genes;
	
	GeneP make(const int);
	
	Gene choice(const Genes&);
	
	Gene cross();
	
	int probRand();
	
	void point(Genes&);
	
	void sort(Genes&);

public:
	PutStone put;
	GA() : block(0), gene(0), put(PutStone()) {};

	GA(const int gene, const PutStone put);

	bool isEnd();

	void step();

	Gene getResult();

	int getMaxPoint();
};