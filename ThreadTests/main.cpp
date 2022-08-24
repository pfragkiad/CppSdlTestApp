
#include "Examples.h"

#include "Examples2.h"
void Valid() { std::cout << "TEST!\n"; } //wow! you make this public if you declare it the Examples2 header (it can be called by other cpp modules)!!!!!

#include "Tzoker.h"


int main(int argc, char** argv)
{
	PredictTzoker(5);

	
	return 0;

	//Examples::runThread1();
	//Examples::runThreadWithArgument();
	//Examples::runThreadWithClass();

	//Examples::runThreadClassWithArg();
	//Examples::runThreadClassWithRefArg();
	//Examples::runThreadClassWithPArg();

	//Examples::runThreadClassWithRefArgWithinClass();

	//CallTest();
}
