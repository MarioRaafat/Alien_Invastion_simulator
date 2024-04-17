#ifndef GENERATOR_H
#define GENERATOR_H

#include "containers/ArrayStack/ArrayStack.h"
#include "containers/LinkedQueue/LinkedQueue.h"
#include "containers/PriorityQueue/PriorityQueue.h"
#include "Units/AlienSoldier.h"
#include "Units/EarthSoldier.h"

class Generator {
	
	static int Ecount, Acount;  // earth and aliens units number
	int current_time;

	// from input file
	int min_Epower,
		max_Epower,
		min_Ehealth,
		max_Ehealth,
		min_Ecapacity,
		max_Ecapacity;

	int min_Apower,
		max_Apower,
		min_Ahealth,
		max_Ahealth,
		min_Acapacity,
		max_Acapacity;

public:
	// sorry 
	Generator(int min_Epw, int max_Epw,
		int	min_Ehl, int max_Ehl,
		int	min_Ecap, int max_Ecap, 
		int min_Apw, int	max_Apw,
		int	min_Ahl, int max_Ahl,
		int	min_Acap, int max_Acap);

	void Eunits_generator(int n, int es, int et, int eg, int prop);
	void Aunits_generator(int n, int as, int am, int ad, int prop);
	int random_range(int min, int max);
};


#endif // !GENERATOR_H