#pragma once


#include <iostream>
#include <thread>
#include <chrono>
#include <future> //async
#include <vector>

using namespace std::chrono_literals;

namespace Examples
{
	bool continuePrinting = false;
	void printStuff()
	{
		while (!continuePrinting)
		{
			std::cout << "Working...\n";
			std::this_thread::sleep_for(500ms);
		}
	}

	void runThread1()
	{
		std::thread t(printStuff);

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		continuePrinting = true;
		t.join();
		std::cout << "Finished!\n";
	}


	void printStuff2(std::chrono::milliseconds interval)
	{
		while (!continuePrinting)
		{
			std::cout << "Working...\n";
			std::this_thread::sleep_for(interval);
		}
	}
	void runThreadWithArgument()
	{
		std::thread t(printStuff2, 100ms);

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		continuePrinting = true;
		t.join();
		std::cout << "Finished!\n";
	}
	//-----

	int longCalc1(int returnValue)
	{
		std::cout << "Func Thread ID: " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(3s);
		return returnValue;
	}

	void runAsync1()
	{
		std::cout << "Parent Thread ID: " << std::this_thread::get_id() << std::endl;

		//std::launch:deferred (same thread!) (so not in fact parallel..)
		//std::launch::async (other thread!) [this is true parallel!]

		std::vector<std::future<int>> results;
		for (size_t i = 0; i < 10; i++)
			results.push_back(std::async(std::launch::async, longCalc1, 10 * i));

		//waits and retrieved the result!
		for (size_t i = 0; i < 10; i++)
		{
			int r = results[i].get();
			std::cout << "Async result = " << r << std::endl;
		}
	}

	class SubItem
	{
	public:
		std::chrono::milliseconds _duration;
	};

	class Item
	{
	public:
		Item() {}
		Item(const Item& oldItem) {
			std::cout << "COPY IS CALLED!\n";
			continuePrinting = oldItem.continuePrinting;
		}

		bool continuePrinting = true;

		void printStuff()
		{
			while (this->continuePrinting)
			{
				std::cout << "Continue: " << continuePrinting << ". Working...\n";
				std::this_thread::sleep_for(500ms);
			}
		}

		void printStuffArg(std::chrono::milliseconds t)
		{
			while (this->continuePrinting)
			{
				std::cout << "Continue: " << continuePrinting << ". Working...\n";
				std::this_thread::sleep_for(t);
			}

		}

		void printStuffRefArg(SubItem& item)
		{
			while (this->continuePrinting)
			{
				std::cout << "Continue: " << continuePrinting << ". Working...\n";
				std::this_thread::sleep_for(item._duration);
			}

		}

		void printStuffPArg(SubItem* item)
		{
			while (this->continuePrinting)
			{
				std::cout << "Continue: " << continuePrinting << ". Working...\n";
				std::this_thread::sleep_for(item->_duration);
			}

		}

		void runThreadClassWithRefArg()
		{
			continuePrinting = true;
			SubItem subItem; subItem._duration = 5000s;
			//if we do NOT pass ref then it will copy the item!
			//the function address operator is MUST
			std::thread t(&Item::printStuffRefArg, std::ref(*this), std::ref(subItem)); //ref to subItem is needed or WILL NOT compile!
			subItem._duration = 1000ms; //change it in order to check if the correct subitem or a copy of it is passed!

			//wait for enter
			std::cin.get();
			//on enter inform the thread to quit!
			continuePrinting = false;

			t.join();
			std::cout << "Finished!\n";
		}
	};

	void runThreadWithClass()
	{
		Item item;
		//if we do NOT pass ref then it will copy the item!
		//the function address operator is MUST
		std::thread t(&Item::printStuff, std::ref(item));
		//std::thread t(&Item::printStuff, std::reference_wrapper(item)); //this is the same with std::ref
		//std::thread t(&Item::printStuff, item); //COPY IS CALLED HERE!

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		item.continuePrinting = false;

		t.join();
		std::cout << "Finished!\n";
	}

	void runThreadClassWithArg()
	{
		Item item;
		//if we do NOT pass ref then it will copy the item!
		//the function address operator is MUST
		std::thread t(&Item::printStuffArg, std::ref(item),500ms);

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		item.continuePrinting = false;

		t.join();
		std::cout << "Finished!\n";
	}

	void runThreadClassWithRefArg()
	{
		Item item;
		SubItem subItem; subItem._duration = 5000s;
		//if we do NOT pass ref then it will copy the item!
		//the function address operator is MUST
		std::thread t(&Item::printStuffRefArg, std::ref(item), std::ref(subItem)); //ref to subItem is needed or WILL NOT compile!
		subItem._duration = 1000ms; //change it in order to check if the correct subitem or a copy of it is passed!

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		item.continuePrinting = false;

		t.join();
		std::cout << "Finished!\n";
	}
	
	void runThreadClassWithPArg()
	{
		Item item;
		SubItem subItem; subItem._duration = 5000s;
		//if we do NOT pass ref then it will copy the item!
		//the function address operator is MUST
		std::thread t(&Item::printStuffPArg, std::ref(item), &subItem); //ref to subItem is needed or WILL NOT compile!
		subItem._duration = 1000ms; //change it in order to check if the correct subitem or a copy of it is passed!

		//wait for enter
		std::cin.get();
		//on enter inform the thread to quit!
		item.continuePrinting = false;

		t.join();
		std::cout << "Finished!\n";
	}

	void runThreadClassWithRefArgWithinClass()
	{
		Item item;

		item.runThreadClassWithRefArg();
	}
}