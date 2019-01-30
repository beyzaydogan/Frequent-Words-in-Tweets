#include <iostream>
#include "Twitter.h"
#include <fstream>
#include <string>
#include <ctime>
using namespace std;




int main()
{
	clock_t tstart = clock();
	Twitter data;

	data.makeMainHashTable("training.1600000.processed.noemoticon.csv", "stopwords.txt");

	data.findTop10();
	cout << "Time passed:" << (double)(clock() - tstart) / CLOCKS_PER_SEC
		<< "sec" << endl;
	system("pause");
	return 0;
}