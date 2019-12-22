#include <iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;


vector<string> initReserved()
{
	vector<string> ReservedWords;
	ReservedWords.push_back("if");
	ReservedWords.push_back("then");
	ReservedWords.push_back("else");
	ReservedWords.push_back("end");
	ReservedWords.push_back("repeat");
	ReservedWords.push_back("until");
	ReservedWords.push_back("read");
	ReservedWords.push_back("write");
	return ReservedWords;

}
vector<string> initSymbols()
{
	string arr[] = { "+","-","*","/","=","<","(",")",";",":=",":"};
	vector <string> SpecialSymbolsVector(arr, arr + 11);
	for (int i = 0; i < SpecialSymbolsVector.size(); i++)
		cout << SpecialSymbolsVector[i] << endl;
	//cout << SpecialSymbolsVector[9];
	return SpecialSymbolsVector;
}

bool searchReserved(string word,vector<string> ReservedWords)
{
	for (int i = 0; i < ReservedWords.size(); i++)
		if (word == ReservedWords[i])
			return true;
	return false;
}
bool searchSymbols(string word, vector<string> SpecialSymbolsVector)
{
	cout << "hellow symbolss" << endl;
	for (int i = 0; i < SpecialSymbolsVector.size(); i++)
	{
		if (word == SpecialSymbolsVector[i])
		{
			cout << "da5el 3al return trueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
			return true; 
		}
			
		cout << "from inside the forloop" << endl;
	}
	cout << "da5el 3al return false" << endl;
		return false;
}

string removeComments(string s)
{
	
	int begin;
	int end;
	while (1)
	{
		begin = s.find("{");
		if (begin == -1)
			break;
		end = s.find("}");
		s.erase(begin, (end-begin)+1);
	}
	return s;
}
string removeSpacesTillNextChar(string sentence)
{
	string s;
	while (sentence.length() >= 0)
	{
		s = sentence.substr(0, 1);
		if (s == " ")
			sentence.erase(0, 1);
		else break;
	}
	return sentence;
}

void checkSentence(string sentence,vector<string> ReservedWords, vector<string> SpecialSymbolsVector)
{ 
	ofstream out;
	out.open("scanner_output.txt");
	//out <<"Came with sentence : " <<sentence << endl;
	while (sentence.length() > 0) {
		//delete all spaces found at the beginning of the sentence
		sentence = removeSpacesTillNextChar(sentence);
		//check if the first character is a letter , then it's a reserved word or an indentifier 
		int endid;
		string subsentence;
		//out <<"sentence is "<< sentence << "daruuuuuuuuuuuuuuuuuuuuuriii" << endl;
		
		//if "end" was found
		if (sentence.substr(0, 3) == "end")
		{
			out << "end" << " : " << "reserved word" << endl;
			break;
		}
		//check if the first character is a letter , then it's a reserved word or an indentifier 
		else if ((sentence.substr(0, 1) >= "A" && sentence.substr(0, 1) <= "Z")
			|| (sentence.substr(0, 1) >= "a" && sentence.substr(0, 1) <= "z"))
		{
			//take the word from the first character to the character before a space or a symbol
			endid = sentence.find_first_of(" +*/=<();:-");
			subsentence = sentence.substr(0, endid);
			if (searchReserved(subsentence, ReservedWords))
			{
				out << subsentence << " : " << "reserved" << endl;
				//cout<< subsentence << " : " << "reserved" << endl;
			}
			else {
				out << subsentence << " : " << "indentifier" << endl;

				//cout<<subsentence << " : " << "reserved" << endl;
			}
			sentence.erase(0, endid);
		}

		//if the first character is a symbol 
		else if (searchSymbols(sentence.substr(0, 1), SpecialSymbolsVector)) {
			//out << "searchsymbolssssssssssssssssssssssssssssssssssssssssssssssssssssssssss" << endl;
			if (sentence.substr(0, 2) == ":=") {
				out << sentence.substr(0, 2) << " : " << "Special Symbol" << endl;
				sentence.erase(0, 2);
			}
			else
			{
				out << sentence.substr(0, 1) << " : " << "Special Symbol" << endl;
				sentence.erase(0, 1);
			}

		}
	
		
	
	
		
		// if it is a number
		else if (sentence.substr(0, 1) >= "0"&&sentence.substr(0, 1) <= "9")
		{
			int endNum = sentence.find_first_not_of("0123456789");
			out << sentence.substr(0, endNum) << " : " << "number" << endl;
			sentence.erase(0, endNum);
		}

		

		/*else if (sentence.substr(0, 1) >= "0"&&sentence.substr(0, 1) <= "9")
			out << sentence << " : " << "number" << endl;*/
	}
	

}


int main()
{
	//initialize Reserved Words 
	vector<string> ReservedWords = initReserved();
	
	//init Symbols Vector
	vector <string> SpecialSymbolsVector= initSymbols();
	

	//open the file 
	ifstream in;
	in.open("C:\\Users\\Mina Rafla\\Documents\\Visual Studio 2017\\Projects\\LexicalAnalysisCompilersProject1\\LexicalAnalysisCompilersProject1\\tiny_sample_code.txt");
	
	//put the file content in a string "str"
	string s;
	string str;
	if (in.is_open())
	{
		while (in)
		{
			getline(in, s);
			str += s;
			str += " ";
		}
		//cout << str << endl;
	}
	else 
	{
		cout << "msh  tamaaaam" << endl;
	}

	//Remove Comments from the string str
	str = removeComments(str);
	cout << "After Comments removal str is " << endl << str << endl;

	checkSentence(str,ReservedWords,SpecialSymbolsVector);

	//int semiColon;
	//string substring;
	//while (str.length()>0)
	//{
	//	semiColon = str.find(";");
	//	if (semiColon == -1)
	//		semiColon = str.find(' ');
	//	
	//	if (semiColon == -1 && str.substr(0,3)=="end" )
	//	{
	//		break;
	//		//substring = str;
	//		//checkSentence(substring);
	//	}
	//	else {
	//		substring = str.substr(0, semiColon);
	//		str.erase(0, semiColon + 1);
	//	}
	//	cout << "SUB STRING ISSSS"<<substring << endl;
	//	checkSentence(substring,ReservedWords, SpecialSymbolsVector);
	//	cout <<"Str is "<< str << endl;
	//	
	//	
	//	//int x ;
	//		

		

	}

	
	






	 



	

