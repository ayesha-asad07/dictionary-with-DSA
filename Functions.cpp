
////////////////////////////////////////////////////////////////////////////////////////////////////////
// ================================================================================================== //
// ====================================== >>>>     SOURCE FILE  <<<< ================================ //
// ================================================================================================== //
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Header.h"

bool exit_program = false;
// ------->>>>      Bookmarks and history objects    <<<<------------------
BookmarkList b;
HistoryList h;

// -------------------------- >>>>    Main menu item array      <<<<<-----------------------
string itemArray_DictMain[]
{
	"Search for a word",
	"Bookmarks",
	"History",
	"Add Word",
	"Exit"
};

// -------- >>>> CLASS FUNCTIONS <<< ------
// -------- >>>> Dictionary class functions <<< ------

DHT::DHT()
{
	//dictArray = new DHT_Node *[DICTIONARY_HASHTABLE_SIZE];
	words_entered = 0;

	// Initialize dictionary array with empty DHT nodes

	DHT_Node* n = new DHT_Node;

	for (int i = 0; i < DICTIONARY_HASHTABLE_SIZE; ++i)
	{
		dictArray[i] = n;
		dictArray[i]->next = NULL;
	}
}

// This hash function adds up the unicode values of each letter of
// the provided key string. Each unicode value is also multiplied by
// the positional weight of the character in order to avoid duplicate
// hash values when two strings with the same characters are hashed

int DHT::hashFunction(string s) {
	int g = 2;
	int sum = 0;

	for (int i = 0; i < s.length(); ++i)
		sum += (int)s[i] * pow(g, i);

	return sum % DICTIONARY_HASHTABLE_SIZE;
}


// =================================== >>>> Insert function<<<< =================================
void DHT::insert(string w, string df)
{
	// Generate hash index
	int hash_index = hashFunction(w);

	DHT_Node* n = new DHT_Node(w, df);


	// If there's already a word at the hash index, traverse linked list of nodes
	if (dictArray[hash_index]->word != "")
	{
		DHT_Node* travNode = new DHT_Node;
		travNode = dictArray[hash_index];

		// Traverse linked list at hash index till the end
		while (travNode->next != NULL)
			travNode = travNode->next;

		travNode->next = n;
	}
	else dictArray[hash_index] = n;
	++words_entered;
}

// ========================== >>>> Add words on console function<<<< =================================
void DHT::addWord()
{
	string w, df;

	cout << "\n Enter word you want to insert: ";
	cin >> w;
	cout << " Enter defintion: ";
	cin >> df;
	string str = w + " " + df;

	if (searchInHashTable(w) == true)
		return;

	addWordToFile(str);
	cout << "filed" << endl;
	cout << "\n Word is inserted Successfully." << endl;
	cout << "\n TOTAL WORDS: " << words_entered << endl;


	DICTIONARY_HASHTABLE_SIZE++;

	int hash_index = hashFunction(w);

	DHT_Node* n = new DHT_Node(w, df);


	// If there's already a word at the hash index, traverse linked list of nodes
	if (dictArray[hash_index]->word != "") {
		DHT_Node* travNode = new DHT_Node;
		travNode = dictArray[hash_index];

		// Traverse linked list at hash index till the end
		while (travNode->next != NULL)
			travNode = travNode->next;
		travNode->next = n;
	}
	else dictArray[hash_index] = n;



}


// ========================== >>>> Add words in File function<<<< =================================

void DHT::addWordToFile(const string& word) {

	vector<string> words;

	// Read existing words from the file
	ifstream inputFile("EnglishDictionary.txt");

	if (inputFile.is_open()) {

		string line;

		while (getline(inputFile, line)) {

			words.push_back(line);
		}

		inputFile.close();
	}

	// Find the iterator where the word should be inserted to maintain alphabetical order
	auto iter = lower_bound(words.begin(), words.end(), word);

	// Insert the word at the correct position
	words.insert(iter, word);

	// Write the updated words back to the file
	ofstream outputFile("EnglishDictionary.txt");

	if (outputFile.is_open()) {

		for (const auto& w : words) {

			outputFile << w << '\n';

		}

		outputFile.close();

		cout << "Word '" << word << "' added to the file at the correct alphabetical position." << endl;
		words_entered++;
	}

	else
	{
		cerr << "Error opening file for writing." << endl;
	}
}


// ======================= >>>> funtion to deep copy user bst into a temp <<<< ======================
DHT_Node* DHT::deepcopy(DHT_Node* root)
{
	if (!root)
	{
		return NULL;
	}

	DHT_Node* newNode = new DHT_Node(root->word, root->def);
	newNode->next = deepcopy(root->next);
	return newNode;
}

// =================================== >>>> Search function (DEBUG) <<<< =================================
bool DHT::searchInHashTable(string w)
{
	for (int i = 0; i < DICTIONARY_HASHTABLE_SIZE; i++)
	{
		DHT_Node* travNode;

		travNode = deepcopy(dictArray[i]);

		while (travNode != NULL)
		{
			if (travNode->word == w)
			{
				cout << "\n Uh Oh! Cannot insert word. " << endl;
				cout << " This words is alredy existes in Dictionary. :)" << endl;
				return true;
			}
			travNode = travNode->next;
		}

	}
	return false;

}

// ================================ >>>> Display function (DEBUG) <<<< =================================
void DHT::display(void)
{
	for (int i = 0; i < DICTIONARY_HASHTABLE_SIZE; ++i)
	{
		DHT_Node* travNode = new DHT_Node;
		travNode = dictArray[i];

		do
		{
			cout << i << ": " << travNode->word;
			if (travNode->word != "") cout << " [" << travNode->def << "]";
			travNode = travNode->next;

			if (travNode != NULL) cout << " --> ";
		} while (travNode != NULL);

		cout << endl;
	}

	cout << "TOATL WORDS: " << words_entered << endl;
}

// ======================= >>>> Function to get word definition <<<< ======================
void DHT::getDefinition(string w)
{
	bool returned = false;
	int hash_index = hashFunction(w);
	string str;
	// If word is found at hash index...
	if (dictArray[hash_index]->word == w)
	{
		cout << "Definition: " << dictArray[hash_index]->def << endl << endl;
		returned = true;
	}
	else
	{ // If word is not found at hash index, traverse linked list
		DHT_Node* travNode = new DHT_Node;
		travNode = dictArray[hash_index];

		while (travNode->next != NULL)
		{
			travNode = travNode->next;
			if (travNode->word == w)
			{
				str = travNode->def;
				cout << "Definition: " << travNode->def << endl << endl;
				returned = true;
				break;
			}
		}
	}

	if (returned == false)
	{
		cout << "Uh Oh! Word doesn't exist :(";
		cout << "\n Do you want to add this word in Dictionary? (y/n)" << endl;
		char c = _getch();
		if (c == 'y') {
			addWord();
		}
	}
	if (returned == true) {
		update(w);
	}
}

// ============================= >>>> Function to remove word <<<< ============================
void DHT::removeWord(string w)
{
	string str = "";
	int hash_index = hashFunction(w);

	cout << "Searching for " << w << " ... " << endl;
	if (dictArray[hash_index]->word == w)
	{
		cout << "\n Word Found." << endl;
		str = dictArray[hash_index]->word + dictArray[hash_index]->def;
		// Lazy deletion
		dictArray[hash_index]->word = "";
		dictArray[hash_index]->def = "";
	}
	else
	{
		DHT_Node* travNode = new DHT_Node;
		travNode = deepcopy(dictArray[hash_index]);

		bool wordFound = false;

		do
		{
			if (travNode->word == w) {
				wordFound = true;
				str = travNode->word + travNode->def;
				cout << "\n Word Found." << endl;
				// Lazy deletion
				travNode->word = "";
				travNode->def = "";
				break;
			}
			travNode = travNode->next;
		} while (travNode != NULL);

		if (!wordFound) {
			cout << "\n Uh Oh! Cannot delete word.\n This word isn't available in the dictionary file." << endl;
			return;
		}
	}

	deleteWordFromFile(str);

	--words_entered;
	cout << "\n TOTAL WORDS: " << words_entered << endl;
}


void DHT::deleteWordFromFile(const string& word) {
	vector<string> words;

	// Read existing words from the file
	ifstream inputFile("EnglishDictionary.txt");

	if (inputFile.is_open()) {
		string line;

		while (getline(inputFile, line)) {
			// Check if the line is not the word to be deleted
			if (line != word) {
				words.push_back(line);
			}
		}

		inputFile.close();
	}
	else {
		cerr << "Error opening file for reading." << endl;
		return;
	}

	// Write the updated words back to the file
	ofstream outputFile("EnglishDictionary.txt");

	if (outputFile.is_open()) {
		for (const auto& w : words) {
			outputFile << w << '\n';
		}

		outputFile.close();

		cout << "Word '" << word << "' deleted from the file." << endl;
	}
	else {
		cerr << "Error opening file for writing." << endl;
	}
}

void DHT::update(const string& old) {

	char num;
	cout << "\n Do You want changings? " << endl;
	cout << " 1. Update this word \n 2. Delete this word \n 3. No" << endl;
	num = _getch();
	if (num == '1')
	{
		string word, def;
		cout << " Enter Updated Word: ";
		cin >> word;
		cout << "Enter Updated Definiton: ";
		cin >> def;
		updateWordInFile(old, word, def);
		cout << "\nDo you want to Delete it? (1/0)";
		num = _getch();
		if (num == 1)
			removeWord(old);
	}
	else if (num == '2')
		removeWord(old);

}

void DHT::updateWordInFile(const string& oldWord, const string& newWord, const string& newDefinition) {


	vector<string> words;

	// Read existing words from the file
	ifstream inputFile("EnglishDictionary.txt");

	if (inputFile.is_open()) {
		string line;

		while (getline(inputFile, line)) {
			// Check if the line contains the word to be updated

			if (line.find(oldWord) != string::npos) {
				// Replace oldWord with newWord and newDefinition
				line = newWord + " " + newDefinition;
			}

			words.push_back(line);
		}

		inputFile.close();
	}
	else {
		cerr << "Error opening file for reading." << endl;
		return;
	}

	// Write the updated words back to the file
	ofstream outputFile("EnglishDictionary.txt");

	if (outputFile.is_open()) {
		for (const auto& w : words) {
			outputFile << w << '\n';
		}

		outputFile.close();

		cout << "Word '" << oldWord << "' updated in the file." << endl;
	}
	else {
		cerr << "Error opening file for writing." << endl;
	}
}


// ============================= >>>> Load words and definitions from .txt file <<<< ============================
void DHT::loadWordsFromFile(void)
{
	ifstream textFile;
	// Open text file containing words and their definitions
	textFile.open("EnglishDictionary.txt");

	int i = 0;
	string line;

	// Read each line
	while (getline(textFile, line) && i < DICTIONARY_HASHTABLE_SIZE)
	{
		string word;
		string def;

		if (line != "")
		{
			string::iterator j;
			j = line.begin();

			// Extracts word
			while (j != line.end() && *j != ' ')
			{
				word.push_back(*j);
				++j;
			}

			// Extract definition
			while (j != line.end())
			{
				def.push_back(*j);
				++j;
			}

			// Insert word and definition into dictionary hash table
			this->insert(word, def);
			++i;
		}
	}

	// Close file
	textFile.close();
}

// ---- >>>> UI Class Functions <<< ------

// Default contructor
UI::UI(void) : selection(0), max_selections(sizeof(itemArray_DictMain) / sizeof(*itemArray_DictMain)), stop_taking_str_input(false) {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	dhtObj.loadWordsFromFile();
	autoCompleteTrieObj.import_txt();
}

// %%%%%%%%%%%%%% ==== >>> Change text colour << ===== %%%%%%%%%%%%%%
void UI::setTextColour(int c)
{
	SetConsoleTextAttribute(hConsole, c);
}

// ============================= >>>>  Display menu from string array<<<< ============================
void UI::showMenu(string* strArray)
{
	for (int i = 0; i < max_selections; ++i)
	{
		if (i == selection)
		{
			setTextColour(SECONDARY_COLOUR);
			cout << " -> " << strArray[i] << " " << endl;
		}
		else
		{
			setTextColour(COLOUR_WHITE);
			cout << "    " << strArray[i] << " " << endl;
		}
	}
}

// ============================= >>>>  // Process menus and UI elements <<< ============================
void UI::process(void)
{
	while (!exit_program)
	{
		switch (screen)
		{
		case SCREEN_MAIN:
			setTextColour(MAIN_COLOUR);
			cout << " --------------------------------------------------------" << endl;
			cout << " |          English Dictionary Implementation           |" << endl;
			cout << " --------------------------------------------------------" << endl << endl;

			showMenu(itemArray_DictMain);

			setTextColour(COLOUR_GREY);
			cout << endl << " Use UP and DOWN arrow keys to navigate." << endl;
			cout << " Press SPACE to select." << endl;

			// Controls input key commands

			switch (key_input = _getch()) {
			case KEY_UP:
				--selection;
				break;
			case KEY_DOWN:
				++selection;
				break;
			case KEY_SPACE:
				if (selection == 0) changeScreen(SCREEN_SEARCH);
				if (selection == 1) changeScreen(SCREEN_BOOKMARKS);
				if (selection == 2) changeScreen(SCREEN_HISTORY);
				if (selection == 3)changeScreen(SCREEN_ADD);
				if (selection == 4) exit_program = true;
				break;
			}

			// Controls selection counter

			if (selection > max_selections - 1)
				selection = 0;

			if (selection < 0)
				selection = max_selections - 1;

			break;

		case SCREEN_SEARCH:
			setTextColour(MAIN_COLOUR);
			cout << " --------------------------------------------------------" << endl;
			cout << " |          English Dictionary Implementation           |" << endl;
			cout << " --------------------------------------------------------" << endl << endl;

			setTextColour(COLOUR_GREY);
			cout << " Press SPACE to enter." << endl;
			cout << " Press ESC to go back." << endl << endl << endl;

			// Take string input

			setTextColour(COLOUR_YELLOW);
			cout << " Enter word to search: ";
			setTextColour(COLOUR_WHITE);
			cout << " ";
			cout << str_input;

			// Run autocomplete / autocorrect as long as string input is provided
			if (str_input != "") {
				cout << endl << endl;
				autoCompleteTrieObj.get_prefix(str_input);
			}

			//if (!stop_taking_str_input) key_input = _getch();

			// Take keyboard input
			if (!stop_taking_str_input)
			{
				key_input = _getch();

				if (key_input == KEY_SPACE)
					stop_taking_str_input = true;

				else if (str_input != "" && key_input == KEY_BACKSPACE)
					str_input.pop_back(); // Add character to string input

				else if (key_input != NULL && key_input != 13 && key_input != KEY_BACKSPACE && validEntry())
					str_input.push_back(key_input); // Remove character when BACKSPACE is pressed

				if (key_input == KEY_ESCAPE)
					changeScreen(SCREEN_MAIN);
			}

			// Once word is entered...
			if (stop_taking_str_input)
			{
				setTextColour(SECONDARY_COLOUR);
				cout << endl << endl << " " << str_input << " ";
				setTextColour(COLOUR_WHITE);

				// Get definition
				dhtObj.getDefinition(str_input);
				setTextColour(COLOUR_GREY);


				cout << endl << " Press SPACE to search again." << endl;
				cout << endl << " Press B to bookmark word." << endl;

				//dhtObj.update(str_input);
				h.insert_word_at_last(str_input); // Add searched word to history


				key_input = _getch();
				if (key_input == KEY_SPACE)
				{
					str_input = ""; // Reset string input
					stop_taking_str_input = false;
				}
				else if (key_input == KEY_ESCAPE) changeScreen(SCREEN_MAIN); // Go back to main menu
				else if (key_input == 66 || key_input == 98) b.insert_word_at_last(str_input); // Add to bookmarks
			}

			break;

		case SCREEN_BOOKMARKS:
			setTextColour(MAIN_COLOUR);
			cout << " --------------------------------------------------------" << endl;
			cout << " |          English Dictionary Implementation           |" << endl;
			cout << " --------------------------------------------------------" << endl << endl;

			setTextColour(SECONDARY_COLOUR);
			cout << " Bookmarks " << endl << endl;

			setTextColour(COLOUR_WHITE);

			// Show bookmarks
			b.Display();

			setTextColour(COLOUR_GREY);
			cout << endl << " Press ESC to go back." << endl;

			key_input = _getch();
			if (key_input == KEY_ESCAPE) changeScreen(SCREEN_MAIN);

			break;

		case SCREEN_HISTORY:
			setTextColour(MAIN_COLOUR);
			cout << " --------------------------------------------------------" << endl;
			cout << " |          English Dictionary Implementation           |" << endl;
			cout << " --------------------------------------------------------" << endl << endl;

			setTextColour(SECONDARY_COLOUR);
			cout << " History " << endl << endl;

			setTextColour(COLOUR_WHITE);

			// Show history
			h.Display();

			setTextColour(COLOUR_GREY);
			cout << endl << " Press ESC to go back." << endl;

			key_input = _getch();
			if (key_input == KEY_ESCAPE) changeScreen(SCREEN_MAIN);
			break;

		case SCREEN_ADD:

			setTextColour(MAIN_COLOUR);
			cout << " --------------------------------------------------------" << endl;
			cout << " |          English Dictionary Implementation           |" << endl;
			cout << " --------------------------------------------------------" << endl << endl;

			setTextColour(SECONDARY_COLOUR);
			cout << " Adding Word " << endl << endl;

			setTextColour(COLOUR_WHITE);
			//dhtObj.display();



			dhtObj.addWord();

			setTextColour(COLOUR_GREY);
			cout << endl << " Press ESC to go back." << endl;

			key_input = _getch();
			if (key_input == KEY_ESCAPE)
				changeScreen(SCREEN_MAIN);
			break;
		}

		Trie temp;
		temp.import_txt();
		autoCompleteTrieObj = temp;
		// Reset keyboard input and clear screen

		key_input = 0;
		system("cls");

	}

	system("cls");
	system("color 0A");
	cout << "\n\n\n\n\t\t\t\t-------------------------------------------------";
	cout << "\n\t\t\t\t|          Thanks for using Dictionary           |";
	cout << "\n\t\t\t\t-------------------------------------------------\n\n\n\n\n";
}

void UI::changeScreen(int id) {
	switch (id) {
	case SCREEN_MAIN:
		max_selections = sizeof(itemArray_DictMain) / sizeof(*itemArray_DictMain);
		selection = 0;
		screen = SCREEN_MAIN;
		break;

	case SCREEN_SEARCH:
	case SCREEN_BOOKMARKS:
	case SCREEN_HISTORY:
	case SCREEN_ADD:
		screen = id;
		break;
	}
}


// =================== >>>> Returns true when input is a-z, A-Z or BACKSPACE, SPACE or ESC<<< ================
bool UI::validEntry(void)
{
	if ((key_input >= 97 && key_input <= 122) || key_input == KEY_BACKSPACE || key_input == KEY_SPACE || key_input == KEY_ESCAPE) return true;
	else return false;
}


// =================== >>>> Bookmark and history class functions <<< ================
void BookmarkList::insert_word_at_last(string a)
{

	BH_Node* newNode, * last;
	newNode = new BH_Node;   // New node using Dynamic memory location
	newNode->data = a;
	newNode->link = NULL;
	last = headptr;
	if (!headptr)
		headptr = newNode;
	else
	{
		while (last->link)
		{
			last = last->link;
		}
		last->link = newNode;
	}

	ofstream i;
	i.open("Bookmark.txt", ios::app);
	if (i.fail())
	{
		cerr << "Error opening File" << endl;
	}
	i << a << endl;
	i.close();
}

// =================== >>>> ------  <<< ================
void BookmarkList::Display()
{
	BH_Node* temp = new BH_Node;
	temp = headptr;

	while (temp != NULL)
	{
		cout << " " << temp->data << endl;
		temp = temp->link;
	}
}


// =================== >>>> HistoryList Class Functions <<< ================
bool HistoryList::search(string a)
{

	struct BH_Node* current = headptr;  // Initialize current 
	while (current != NULL)
	{
		if (current->data == a)
			return true;
		current = current->link;
	}
	return false;
}


// =================== >>>> ------------  <<< ================
void HistoryList::insert_word_at_last(string a)
{
	if (h.search(a) == true)return;
	else
	{
		BH_Node* newNode, * last;
		newNode = new BH_Node;     // New node using Dynamic memory location
		newNode->data = a;
		newNode->link = NULL;
		last = headptr;
		BH_Node* temp = new BH_Node;
		temp = headptr;

		if (!headptr)
			headptr = newNode;
		else
		{
			while (last->link)
			{
				last = last->link;
			}
			last->link = newNode;
		}
		ofstream i;
		i.open("History.txt", ios::app);
		if (i.fail())
		{
			cerr << "Error opening File" << endl;
		}
		i << a << endl;
		i.close();
	}
}


// =================== >>>> ------------  <<< ================
void HistoryList::Display()
{
	BH_Node* temp = new BH_Node;
	temp = headptr;

	// Displays data stored in linked list
	while (temp != NULL)
	{

		cout << " " << temp->data << endl;
		temp = temp->link;
	}

}
