/*
 * Chromosome.h
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include <vector>
#include "Gene.h"

class Chromosome {
public:
	Chromosome();
	virtual ~Chromosome() { };

	Gene* getGeneAtIndex(unsigned int index);

	void AddGene(const Gene& gene);
	void ChangeGeneAtIndex(unsigned int index, const Gene& replacementGene);
	void MutateGene();
	unsigned int getSize() const;
	float getSuitability() const;

	void setSuitability(float suitability);

private:
	float _suitability;
	std::vector<Gene> _genes;
};


#endif /* CHROMOSOME_H_ */
