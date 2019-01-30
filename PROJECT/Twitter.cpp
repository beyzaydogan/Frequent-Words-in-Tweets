#include "Twitter.h"


void Twitter::makeMainHashTable(string filename, string stopfile){

	fstream data(filename);
	string tweet = "";
	string new1;
	string new2;
	string new3;
	string new4;
	string new5;
	int hash = 0;
	int length = 0;
	int quotation = 0;
	int quotation1 = 0;
	StoppingHashTable(stopfile);//create stop hash table

	if (data.is_open()){

		while (data.good())
		{
			length = 0;
			getline(data, new1, ',');
			getline(data, new2, ',');
			getline(data, new3, ',');
			getline(data, new4, ',');
			getline(data, new5, ',');
			getline(data, tweet, '\n');

			string insertdata = "";  // insert word
			int i = 0;
			for (auto x : tweet){
				length++;

				if (data.eof()){
					break;
				}


				if ((x == ' ') || !(((int)x >= 65 && (int)x <= 90) || ((int)x >= 97 && (int)x <= 122) || ((int)x == 39)) || (quotation>0 && (int)x == 39) || quotation1 == 1){
					i = 0;
					if (insertdata != ""){
						if (!controlStop(hash%StopMax, insertdata)){
							insert(hash%MAX, insertdata);
						}
					}
					hash = 0;
					insertdata = "";
					quotation = 0;
					quotation1 = 0;
				}

				else{

					if (((int)x >= 65 && (int)x <= 90) || ((int)x >= 97 && (int)x <= 122) || ((int)x == 39)){
						if ((int)x == 39){
							if (insertdata == ""){
								continue;
							}
							else if (!(((int)tweet[length] >= 65 && (int)tweet[length] <= 90) || ((int)tweet[length] >= 97 && (int)tweet[length] <= 122))){
								quotation1 = 1;


							}
							else{
								if (quotation == 0){
									x = tolower(x);
									hash = abs(65599 * hash + (int)x);
									i++;
									insertdata = insertdata + x;

								}
								quotation++;

							}

						}
						else{
							x = tolower(x);
							hash = abs(65599 * hash + (int)x);
							i++;
							insertdata = insertdata + x;
						}
					}


				}

			}

			if (!controlStop(hash%StopMax, insertdata) && insertdata != ""){
				insert(hash%MAX, insertdata);
				insertdata = "";
				hash = 0;
				i = 0;
				quotation = 0;
				quotation1 = 0;
			}
		}

	}
}



bool Twitter::controlStop(int hash, string word){

	bool found = false;
	int index = 0;


	if (stopwords[hash] == word)
	{
		found = true;
	}

	return found;

}
Twitter::Twitter(){

	MAX = 2000000;
	StopMax = 2000000;

	words = new string[MAX];
	instance = new int[MAX];

	for (int i = 0; i < MAX; i++){
		instance[i] = 0;
	}

	stopwords = new string[StopMax];



}


void Twitter::insert(int hashIndex, string insertdata){
	int pcount = 1;

	while (instance[hashIndex] != 0 && words[hashIndex] != insertdata && pcount < MAX)
	{
		hashIndex = (hashIndex + 1) % MAX;
		pcount++;
	}

	if (instance[hashIndex] == 0)
	{
		words[hashIndex] = insertdata;
		instance[hashIndex] = 1;
	}
	else if (words[hashIndex] == insertdata){
		instance[hashIndex]++;

	}

}


void Twitter::findTop10(){

	for (int i = 0; i < 10; i++){
		int topIndex = 0;
		int topinstance = instance[0];

		for (int j = 0; j < MAX; j++){

			if (instance[j]>topinstance){
				topinstance = instance[j];

				topIndex = j;

			}
		}

		cout << i + 1 << ".WORD:  " << words[topIndex] << "-->" << topinstance << endl;

		instance[topIndex] = 0;

	}
}



void Twitter::StoppingHashTable(string filename){
	fstream data(filename);
	string word;
	int index = 0;
	if (data.is_open()){
		while (data >> word)
		{
			for (int j = 0; j < word.length(); j++){

				index = abs(65599 * index + (int)word[j]);
			}

			index = index%StopMax;



			stopwords[index] = word;
			index = 0;
		}

	}
}