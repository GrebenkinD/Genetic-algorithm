#include "stdafx.h"
#include <iostream>
#include <algorithm>
//#include <iomanip>//setw(10)
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

class Individual{
public:
	Individual() : x(0.0), y(0.0), z(0.0), u(0.0), divider(1000) { srand((unsigned)time(NULL)); };
	Individual(double x, double y) : x(x), y(y), z(z), u(0.0), divider(1000) { srand((unsigned)time(NULL)); };

	static Individual Breeding(Individual first, Individual second);

	double getX() const { return x; }
	void setX(double val) { x = val; }
	double getY() const { return y; }
	void setY(double val) { y = val; }
	double getZ() const { return z; }
	void setZ(double val) { z = val; }
	double getU() const { return u; }
	void setU(double val) { u = val; }

	void setRandomValues();
	void mutate();

private:
	double x;
	double y;
	double z;
	double u;
	int divider;
};

void setQualityIndividuals(Individual *individuals, int individualsQuantity, double &Quality);
void SORT(Individual *individuals, size_t size);
void NewGeneration(Individual *individuals, size_t size, double Elite, double mutation);

int main(){
	setlocale(LC_ALL, "russian");

	int individualsQuantity = 200;
	int Generations = 15000;
	double Elite = 10.0;
	double mutation = 50.0;

	Individual *individuals = new Individual[individualsQuantity];

	for (int i = 0; i < individualsQuantity; i++){
		individuals[i].setRandomValues();
		individuals[i].setU(pow(individuals[i].getX(), 2.0) + pow(individuals[i].getY(), 2.0) + pow(individuals[i].getZ(), 2.0)
			/*-2*pow(individuals[i].getX(), 2.0)-pow(individuals[i].getY(), 2.0)+2*pow(individuals[i].getZ(), 2.0)-
			2*individuals[i].getX()*individuals[i].getY()+3*individuals[i].getX()*individuals[i].getZ()-
			2* individuals[i].getY()*individuals[i].getZ()-4*individuals[i].getX()+8*individuals[i].getY()+
			individuals[i].getZ()+4.0*/);
	}

	double Quality = 0.0;
	SORT(individuals, (unsigned int)individualsQuantity);
	setQualityIndividuals(individuals, individualsQuantity, Quality);

	for (int i = 0; i < Generations; i++){
		NewGeneration(individuals, (unsigned int)individualsQuantity, Elite, mutation);
		setQualityIndividuals(individuals, individualsQuantity, Quality);
		SORT(individuals, (unsigned int)individualsQuantity);

		cout << "Поколение: " << i + 1 << " Качество: " << Quality << "\n" << "Значение функции: " <<
			individuals[0].getU() << "\n" << "Лучшая особь: " << individuals[0].getX() << " " << 
			individuals[0].getY() << " " << individuals[0].getZ() << "\n\n";

		if (individuals[0].getU() == 0){
			break;
		}
	}
	system("pause");
	return 0;
}

void setQualityIndividuals(Individual * individuals, int individualsQuantity, double &Quality){
	Quality = 0.0;
	for (int i = 0; i < individualsQuantity; i++)
	{
		individuals[i].setU(pow(individuals[i].getX(), 2.0) + pow(individuals[i].getY(), 2.0) + pow(individuals[i].getZ(), 2.0)
			/*-2*pow(individuals[i].getX(), 2.0)-pow(individuals[i].getY(), 2.0)+2*pow(individuals[i].getZ(), 2.0)-
			2*individuals[i].getX()*individuals[i].getY()+3*individuals[i].getX()*individuals[i].getZ()-
			2* individuals[i].getY()*individuals[i].getZ()-4*individuals[i].getX()+8*individuals[i].getY()+
			individuals[i].getZ()+4*/);
		Quality += individuals[i].getU();
	}
	Quality /= individualsQuantity;
}

int compareIndividuals(const void *first, const void *second){
	double par1 = (*((Individual*)first)).getU();
	double par2 = (*((Individual*)second)).getU();

	if (par1 > par2){ return 1;}
	else if (par1 < par2){ return -1;}
	else{ return 0;}
}
void SORT(Individual *individuals, size_t size){
	qsort(individuals, size, sizeof(Individual), compareIndividuals);
}
void NewGeneration(Individual * individuals, size_t size, double Elite, double mutation){
	int eliteNumber = (int)(((double)size) * (Elite / 100.0));
	for (unsigned int i = eliteNumber + 1; i < size; i++){
		Individual firstParent = individuals[rand() % (size / 2)];
		Individual secondParent = individuals[rand() % (size / 2)];
		individuals[i] = Individual::Breeding(firstParent, secondParent);

		if ((rand() % 100) < mutation){
			individuals[i].mutate();
		}
	}
}
void Individual::setRandomValues(){
	x = (rand() % 17 - 8);
	y = (rand() % 17 - 8);
	z = (rand() % 17 - 8);
}
void Individual::mutate(){
	if (rand() % 10 > 4){
		x += x * (0.05 * (rand() % 8 + 1));
		y += y * (0.05 * (rand() % 8 + 1));
		z += z * (0.05 * (rand() % 8 + 1));
	}
	else{
		x -= x * (0.05 * (rand() % 8 + 1));
		y -= y * (0.05 * (rand() % 8 + 1));
		z -= z * (0.05 * (rand() % 8 + 1));
	}
}
Individual Individual::Breeding(const Individual first, const Individual second){
	Individual descendant;
	descendant.setX((first.getX() / 2.0) + (second.getX() / 2.0));
	descendant.setY((first.getY() / 2.0) + (second.getY() / 2.0));
	descendant.setZ((first.getZ() / 2.0) + (second.getZ() / 2.0));
	return descendant;
}