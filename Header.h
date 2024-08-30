/////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                     //
//                      ==============> Dictionary <===============                                    //
//                                                                                                     //
//                          -->>> DSA Final Project <<<----                                            //
//                           Muhammad Bilal  (22F-3309)                                                //
//                           Tayyaba Imtiaz  (22F-3324)                                                //
//                           Ayesha Asad     (22F-3295)                                                //
//                                                                                                     //
//                                                                                                     //
////////////////////////////////////////// ///////////////////////////////////////////////////////////////


#pragma once
#include <iostream>
#include <string> 
#include <windows.h> 
#include <conio.h> 
#include <fstream> 
#include <vector>   //for temporary file storing
#include <algorithm> //for alphabetical order

#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27

#define MAIN_COLOUR 11
#define SECONDARY_COLOUR 224
#define COLOUR_WHITE 15
#define COLOUR_GREY 7
#define COLOUR_YELLOW 14

#define SCREEN_MAIN 0
#define SCREEN_SEARCH 1
#define SCREEN_BOOKMARKS 2
#define SCREEN_HISTORY 3
#define SCREEN_ADD 4
/*
176 Blue BG
160 Green BG
14 Yellow text
224 Yellow BG
*/


// ================================ >>>> Dictionary Hash Table Node <<<< ==================================
class DHT_Node {
public:
	string word;
	string def;
	DHT_Node* next;

	DHT_Node()
	{
		word = "";
		def = "";
		next = NULL;
	}
	DHT_Node(string w, string df)
	{
		word = w;
		def = df;
		next = NULL;
	}
	~DHT_Node() {}
};

// =================================== >>>> Dictionary Hash Table <<<<< =========================================
class DHT {

	int DICTIONARY_HASHTABLE_SIZE = 5021;
	DHT_Node** dictArray = new DHT_Node * [DICTIONARY_HASHTABLE_SIZE]; // Array of DHT node pointers
	unsigned int words_entered; // Number of words entered

public:

	DHT();
	DHT_Node* deepcopy(DHT_Node* root);
	void insert(string w, string df);			// Insert a word
	int hashFunction(string s);					// Hash function
	void getDefinition(string w);				// Returns the definition associated with a given word
	void removeWord(string w);					// Removes a word from the dictionary
	void addWord(); // Add new word in dictionary Hash Table
	void addWordToFile(const string& word);		//Add new word in file
	void update(const string& old);
	void updateWordInFile(const string& oldWord, const string& newWord, const string& newDefinition);
	bool searchInHashTable(string w);			//Search whether a word is in file/Hash Table or not
	void remove(const string& word);
	void deleteWordFromFile(const string& word); //Delete the specifc word from dictionary file
	void loadWordsFromFile(void);				// Load words from .txt file
	void display(void);							// DEBUG
};

// ======================================= >>>> Class TrieNode  <<< ===========================================
class TrieNode
{
public:
	friend class DHT;

	int value;
	TrieNode* children[26];                     //For All 26 alphabets
	TrieNode* pNext;
	char node_char;

	TrieNode()
	{
		value = 0;
		for (int i = 0; i < 26; i++)            //default constructor
		{
			children[i] = NULL;
		}
	}
	TrieNode(char Letter)                        //parametried constructor
		: node_char(Letter) {
		for (int i = 0; i < 26; i++)
		{
			children[i] = NULL;
		}
	}
	~TrieNode() {};
};

// ======================================= >>>> Class Trie <<< ===========================================
class Trie
{
	friend class TrieNode;              //made class node friend to access variables
private:
	TrieNode* root;
	int Counter;
public:
	friend class DHT;

	Trie()
	{
		root = new TrieNode();
		Counter = 0;
	}
	~Trie() {};


	// ===================== >>>>   function for imporitng dictionary file   <<<< =======================
	void import_txt()
	{
		int Counter = 0;
		string term;

		ifstream get_file("EnglishDictionary.txt");

		if (!get_file)
		{
			cout << "Couldn't open file" << endl;
			return;
		}

		int i = 0;

		while (!get_file.eof())
		{
			string word;
			getline(get_file, term);
			//cout << term << "\n";

			if (term != "") {
				string::iterator j;
				j = term.begin();

				while (j != term.end() && *j != ' ') {
					word.push_back(*j);
					++j;
				}

				++i;
			}

			insert(word);
			Counter++;


			if (Counter >= 28102)
			{
				break;
			}
		}

		//cout << "Inserted " << Counter << " words\n" << endl;
		get_file.close();
	}

	// =================== >>>>   For inserting data from text file into trie class   <<<< =====================
	void insert(string term)
	{
		TrieNode* p = root;
		long int len = term.size();
		for (int x = 0; x < len; x++)
		{
			int i = term[x] - 'a';
			//cout << i << endl;
			if (i < 0)
			{
				//	cout << "Term " << term << " cannot be inserted.  No numbers or symbols allowed!" << endl;
				return;
			}

			if (!p->children[i])
			{
				p->children[i] = new TrieNode(term[x]);
			}
			p = p->children[i];
		}
		Counter++;
		p->value = Counter;
	}

	// ============================= >>>>   function for searching a word   <<<< ============================
	bool search(string key)
	{
		TrieNode* p = root;
		long int len = key.size();
		for (int x = 0; x < len; x++)
		{
			int i = key[x] - 'a';
			if (p->children[i])                  //if words matched
			{
				p = p->children[i];
			}
			else
			{
				//	cout << "String not found!\n" << endl;            //if words didnt match
				return false;
			}
		}
		//cout << "String " << key << " successfully found\n" << endl;
		if (p->value != 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	// ============================= >>>>  For finding possible combinations  <<<< ============================
	bool get_prefix(string prefix)
	{
		TrieNode* p = root;
		long int len = prefix.size();
		for (int x = 0; x < len; x++)
		{
			int i = prefix[x] - 'a';
			if (p->children[i])
			{
				p = p->children[i];
			}

			else
			{
				string prefix1 = prefix.substr(0, prefix.length() - 1);
				//If entered wrong word then remove last alphabet 
				//and check again and repeat this until it finds a word.
				if (!prefix1.empty())
				{
					if (get_prefix(prefix1))
						return true;
				}
				else
				{
					//cout << "Prefix invalid!" << endl;
					return false;

				}
			}
		}
		bool y = true;
		for (int z = 0; z < 26; ++z)
			if (p->children[z] != NULL) y = false;

		if (!y) cout << " Do you mean..." << endl << endl;
		dfs(p, prefix);
		return true;
	}

	// =============================== >>>> traversing common path <<<< ================================
	void dfs(TrieNode* p, string prefix)
	{
		int y = 0;
		while (y < 26)
		{
			if (p->children[y] != NULL)
			{
				dfs2(p->children[y], prefix);
			}
			y++;
		}
		cout << endl;
	}

	// ================================ >>>> printing all combinations <<<< ===============================
	void dfs2(TrieNode* p, string prefix)
	{

		cout << " " << prefix;
		cout << p->node_char;

		while (p != NULL)
		{
			int y = 0;
			while (p->children[y] == NULL && y < 26)
			{
				y++;
			}
			p = p->children[y];

			if (p != NULL)
			{
				cout << p->node_char;
			}
		}
		cout << endl;
	}
};


// ========================================================================== //
// ======================= >>>>    USER INTERFACE  <<<< ===================== //
// ========================================================================== //


class UI {
	int selection;
	int max_selections;
	int key_input;
	string str_input;
	bool stop_taking_str_input;
	unsigned int screen = SCREEN_MAIN;
	HANDLE hConsole;
	bool loop = true;

	DHT dhtObj;
	Trie autoCompleteTrieObj;

public:
	friend class DHT;

	UI();
	void process(void);
	void setTextColour(int);
	void changeScreen(int);
	void showMenu(string* strArr);
	bool validEntry(void);
};

// -->> Bookmarks <<----- //

// Common node for both bookmark and history classes
struct BH_Node
{

	string data;
	BH_Node* link;
	//  Pointer of structure type to make another node
	//  for storing data and address of node
};

class BookmarkList
{
	BH_Node* headptr;                 // Head pointer for the first node
public:
	friend class DHT;

	BookmarkList()
	{
		headptr = 0;
	}

	void insert_word_at_last(string a);
	void Display();

};

// -------------------------- >>>> History Class  <<<<<-----------------------
class HistoryList
{
	BH_Node* headptr;                 // Head pointer for the first node
public:
	friend class DHT;
	HistoryList()
	{
		headptr = 0;
	}
	void insert_word_at_last(string a);
	bool search(string a);
	void Display();
};
