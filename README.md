# dictionary-with-DSA
Created an English dictionary using the Data Structures and Algorithms with optimzed search by trie-trees.

## Prerequiste: - 
  -	Search
  -	Show suggestions
  -	Update Word
  - Delete Word
  -	Add Word
  - Use of an optimize Data Structure in terms of time and space complexity.
## Data Structure: -
- Attains **time and space complexity**
- Best working and efficiency using **Trie Trees and Chaining** of data in our Dictionary Implementation.
## Storage efficiency:
 - As dictionary is storage of a large number of words in alphabetical order so chaining is the best approach to store words for each alphabet. As, we make an array of 26 letters and then chain the words of each corresponding letter by attaching a linked list to each word index.
## Searching approach:
 - Using a trie tree for searching purpose is one of best way of structuring letters. When we are typing our letters to search, tire tree keeps connecting nodes of letter and in this way it can create suggestions according to currently entered letters.
This functionality cannot be get by any other data structure.
## DHT_Node:
The word refers as Dictionary Hash Table Node. 
This class actually creates a pointer node which hold a word, its definition and address of next node.
It has default and parametrized constructor for initialization of node.
DHT:
DHT stands for Dictionary Hash Table.
This class creates a Hash Table of in which words and their definition containing nodes are inserted using d specific hash function. Also it modifies table like it adds word, delete or update word and many more regarding Hash Table.
It stores all nodes in an array of double pointer of specified size.

    DHT_Node** dictArray = new DHT_Node * [DICTIONARY_HASHTABLE_SIZE];
And it uses following hash function to set index for each node:
    
      int DHT::hashFunction(string s) {
	    int g = 2;
	    int sum = 0;

     	for (int i = 0; i < s.length(); ++i)
		      sum += (int)s[i] * pow(g, i);

	     return sum % DICTIONARY_HASHTABLE_SIZE;
    }

This hash function adds up the unicode values of each letter of the provided key string. Each unicode value is also multiplied by the positional weight of the character in order to avoid duplicate hash values when two strings with the same characters are hashed.

## Trie Node:
- This word refers as Trie Tree Node. 
This class actually creates a pointer node which hold a word, its definition and address of next node.
It has default and parametrized constructor for initialization of node.

					
## Trie:
- This class creates a “Trie Tree” using trie node. It also adds meny functionalties. 
Insertion:
First of all , it imports all words form file into trie tree using the same functionality as used in load function of DHT.
The insert function inserts the string in trie tree , by traversing through each character of given string and creates new node coreesponding to each letter and updates counter also.

      void import_txt()
	    void insert(string term)

## Seacrh:
- It searches the respective string simply traversing through nodes of trie tree. By checking each node of tree comparing with string.
# Suggestions:
- It takes the each letter that is input by user, check it a as current string, 
- Finds out the length of that entered prefix and traverse upto that length in trie tree
- Then go to **Depth First Search (DFS) ** for checking each possible word that can be formed form the current prefix and
- Display all the children or words that are in trie tree related to that entered string.
 
      bool get_prefix(string prefix)
      void dfs(TrieNode* p, string prefix)
      void dfs2(TrieNode* p, string prefix)
## UI:
- The UI class represents a simple user interface in a C++ program. It manages user inputs, displays menus, and interacts with two specific objects:
 dhtObj of the DHT class and autoCompleteTrieObj of the Trie class. 
- The class handles various aspects such as screen navigation, text color settings, and user inputs for both numbers and strings. It includes methods to process user actions, change screens, display menus, and ensure the validity of user entries.
	   
      void process(void);
	    void setTextColour(int);
	    void changeScreen(int);
	    void showMenu(string* strArr);
	    bool validEntry(void);
## History:
- Use **Linked List** to keeps the record of history of all searched words.
