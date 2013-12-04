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
	int gene_index = rand() % _genes.size();
	int drone_index = rand() % DataRepository::getInstance().getDronesCount();
	_genes[gene_index].setDrone(*DataRepository::getInstance().getDroneAtIndex(drone_index));
}

Gene* Chromosome::getGeneAtIndex(unsigned int index) {
	return &_genes[index];
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

