#include "GA.hpp"
#include "../../procon26_modio.hpp"
#include <algorithm>

/*
置く　　 : true
置かない : false
*/

GA::GA(const int _gene, const PutStone _put) : mt(mt19937(random_device()())), block(_put.problem->num), gene(_gene), put(_put) {
	genes.clear();
	for (int i = 0; i < gene; i++) {
		if (!i) {
			genes.push_back(GeneP(Gene(block, true), 0));
			continue;
		}
		genes.push_back(make(block));
	}
	point(genes);
	sort(genes);
}

GeneP GA::make(const int block) {
	Gene g;
	for (int i = 0; i < block; i++) {
		g.push_back(mt() % RATIO);
	}
	return GeneP(g, 0);
}

Gene GA::choice(const Genes& genes) {
	pair<int, int> p(0, 0);
	for (int i = 0; i < T_SIZE; i++) {
		int r = mt() % gene;
		if (genes[r].second > p.second) {
			p.first  = r;
			p.second = genes[r].second;
		}
	}
	return (mt() % MUTATION) ? genes[p.first].first : make(block).first;
}

Gene GA::cross() {
	Gene a = choice(genes), b, res;
	int type = probRand();
	switch (type){
	case 0: //二点交叉
	{
		b = choice(genes);
		int size = mt() % block + 1;
		int abegin = (size != block) ? mt() % (block - size) : 0;
		int bbegin = (size != block) ? mt() % (block - size) : 0;
		for (int i = 0; i < size; i++) {
			swap(a[abegin + i], b[bbegin + i]);
		}
		res = (mt() % 2) ? a : b;
	}
		break;
	case 1: //OR交叉
		b = choice(genes);
		for (int i = 0; i < block; i++) {
			res.push_back(a[i] | b[i]);
		}
		break;
	case 2: //AND交叉
		b = choice(genes);
		for (int i = 0; i < block; i++) {
			res.push_back(a[i] & b[i]);
		}
		break;
	case 3: //NOT交叉
		for (int i = 0; i < block; i++) {
			res.push_back(!a[i]);
		}
		break;
	case 4: //逆転交叉
		for (int i = block - 1; i >= 0; i--) {
			res.push_back(a[i]);
		}
	}
	return res;
}

int GA::probRand() {
	static const int source[] = { 5, 3, 3, 2, 1 };
	static const vector<int> seeds(begin(source), end(source));
	int max = 0;
	for (int i = 0; i < seeds.size(); i++) {
		max += seeds[i];
	}
	int rtn = mt() % max;
	for (int i = 0; i < seeds.size(); i++) {
		if (rtn < seeds[i]) return i;
	}
	return 0;
}

void GA::point(Genes& genes) {
	static bool once = true;
	for (int i = 0; i < gene; i++) {
		genes[i].second = put.putStone(&genes[i].first);
		if (once && !i) {
			bool flag = true;
			for (int j = 0; j < block; j++) {
				if (!genes[0].first[j]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				genes[0].second = BOARD_SIZE * BOARD_SIZE;
				return;
			}
			once = false;
		}

	}
}

void GA::sort(Genes& genes) {
	partial_sort(genes.begin(), genes.begin() + 1,
		genes.end(), [](const GeneP& a, const GeneP& b)->bool {
		return a.second > b.second;
	});
}

bool GA::isEnd() {
	GeneP* g = &genes[0];
	if (g->second == (BOARD_SIZE * BOARD_SIZE)) return true;
	return false;
}

void GA::step() {
	if (isEnd()) return;
	Genes next;
	next.push_back(genes[0]);
	for (int i = 1; i < gene; i++) {
		next.push_back(GeneP(cross(), 0));
	}
	point(next);
	sort(next);
	genes = next;
	next.clear();
}

Gene GA::getResult() {
	return genes[0].first;
}

int GA::getMaxPoint() {
	return genes[0].second;
}