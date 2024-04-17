#ifndef EARTHUNIT_H
#define EARTHUNIT_H

#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "../../containers/ArrayStack/ArrayStack.h"
#include "../../containers/LinkedQueue/LinkedQueue.h"
#include "../../containers/PriorityQueue/PriorityQueue.h"

class EarthUnits {

	LinkedQueue<EarthSoldier> ES; // I know you will not like that "?????" so fuck you that its actually name in the document
	ArrayStack<EarthGunnery> ET;
	PriorityQueue<EarthGunnery> EG;

public:

};




#endif // !EARTHUNIT_H
