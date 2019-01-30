#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <fstream>


class Twitter{
	int MAX; // maximum main hash table size
	string *words; // words in the file
	int *instance;// how many times have been repeated


	int StopMax;
	string *stopwords;


public:

	Twitter();//constructor

	void makeMainHashTable(string filename, string stopfile);
	void insert(int hashIndex, string insertdata);

	void StoppingHashTable(string filename);
	bool controlStop(int hash, string word);

	void findTop10();








};