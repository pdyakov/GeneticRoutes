/*
 * Chromosome.cpp
 *
 *  Created on: 20 Oct 2013
 *      Author: Pavel Dyakov
 */

#include "Chromosome.h"
#include <stdlib.h>
#include "../../DataAccess/DataRepository.h"

Chromosome::Chromosome() : _suitability(0) {

}

void Chromosome::AddGene(const Gene& gene) {
	_genes.push_back(gene);
}

void Chromosome::ChangeGeneAtIndex(unsigned int index, const Gene& gene) {
	if (index < _genes.size())
		_genes[index] = gene;
}

void Chromosome::MutateGene() {
	int geneIndex = rand() % _genes.size();
	std::vector<Drone> drones = DataRepository::getInstance().getDrones();
	int randomNumber = rand() % drones.size();
	Gene *gene = &(*(_genes.begin() + geneIndex));
	gene->setDrone(drones.at(randomNumber));
}

Gene Chromosome::getGeneAtIndex(const unsigned int index) const {
	return _genes.at(index);
}

unsigned int Chromosome::getSize() const {
	return _genes.size();
}

float Chromosome::getSuitability() const {
	return _suitability;
}

void Chromosome::setSuitability(float suitability) {
	_suitability = suitability;
}

