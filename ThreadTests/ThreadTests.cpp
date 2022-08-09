
#include "Examples.h"

#include "Examples2.h"
void Valid() { std::cout << "TEST!\n"; } //wow! you make this public if you declare it the Examples2 header (it can be called by other cpp modules)!!!!!



int main()
{
	//Examples::runThread1();
	//Examples::runThreadWithArgument();
    //Examples::runThreadWithClass();

    //Examples::runThreadClassWithArg();
	//Examples::runThreadClassWithRefArg();
	//Examples::runThreadClassWithPArg();

	//Examples::runThreadClassWithRefArgWithinClass();

	CallTest();
}
