#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node
{
    string word;
    Node *next;

    Node(string w)
    {
        word = w;
        next = nullptr;
    }
};

class Dictionary
{
private:
    Node *letters[26];

    string toLowerCase(string word)
    {
        for (int i = 0; i < word.length(); i++)
            word[i] = tolower((unsigned char)word[i]);

        return word;
    }

public:
    Dictionary()
    {
        for (int i = 0; i < 26; i++)
            letters[i] = nullptr;
    }

    void addWord(string word)
    {
        if (word.empty() || !isalpha((unsigned char)word[0]))
            return;

        int index = toupper((unsigned char)word[0]) - 'A';

        Node *newNode = new Node(word);

        if (letters[index] == nullptr)
        {
            letters[index] = newNode;
            return;
        }

        Node *current = letters[index];

        while (current->next != nullptr)
            current = current->next;

        current->next = newNode;
    }

    bool deleteWord(string word)
    {
        if (word.empty() || !isalpha((unsigned char)word[0]))
            return false;

        int index = toupper((unsigned char)word[0]) - 'A';

        Node *current = letters[index];
        Node *previous = nullptr;

        while (current != nullptr)
        {
            if (toLowerCase(current->word) == toLowerCase(word))
            {
                if (previous == nullptr)
                    letters[index] = current->next;
                else
                    previous->next = current->next;

                delete current;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    bool searchWord(string word)
    {
        if (word.empty() || !isalpha((unsigned char)word[0]))
            return false;

        int index = toupper((unsigned char)word[0]) - 'A';

        Node *current = letters[index];

        while (current != nullptr)
        {
            if (toLowerCase(current->word) == toLowerCase(word))
                return true;

            current = current->next;
        }

        return false;
    }

    void displayLetterWords(char letter)
    {
        if (!isalpha((unsigned char)letter))
            return;

        int index = toupper((unsigned char)letter) - 'A';

        Node *current = letters[index];

        cout << letter << ": ";

        if (current == nullptr)
        {
            cout << "No words found." << endl;
            return;
        }

        while (current != nullptr)
        {
            cout << current->word << " -> ";
            current = current->next;
        }

        cout << "null" << endl;
    }

    void displayAllWords()
    {
        for (int i = 0; i < 26; i++)
        {
            cout << char('A' + i) << ": ";

            Node *current = letters[i];

            while (current != nullptr)
            {
                cout << current->word << " -> ";
                current = current->next;
            }

            cout << "null" << endl;
        }
    }

    int countWordsByLetter(char letter)
    {
        if (!isalpha((unsigned char)letter))
            return 0;

        int index = toupper((unsigned char)letter) - 'A';
        int count = 0;

        Node *current = letters[index];

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        return count;
    }

    int countAllWords()
    {
        int total = 0;

        for (int i = 0; i < 26; i++)
        {
            Node *current = letters[i];

            while (current != nullptr)
            {
                total++;
                current = current->next;
            }
        }

        return total;
    }

    string findLongestWord()
    {
        string longest = "";

        for (int i = 0; i < 26; i++)
        {
            Node *current = letters[i];

            while (current != nullptr)
            {
                if (current->word.length() > longest.length())
                    longest = current->word;

                current = current->next;
            }
        }

        return longest;
    }

    ~Dictionary()
    {
        for (int i = 0; i < 26; i++)
        {
            Node *current = letters[i];

            while (current != nullptr)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

int main()
{
    Dictionary dict;

    dict.addWord("Apple");
    dict.addWord("Ant");
    dict.addWord("Air");
    dict.addWord("Book");
    dict.addWord("Ball");
    dict.addWord("Zebra");
    dict.addWord("High");

    cout << "All words:" << endl;
    dict.displayAllWords();

    cout << "\nWords starting with A:" << endl;
    dict.displayLetterWords('A');

    cout << "\nSearch Apple: "
         << boolalpha << dict.searchWord("Apple") << endl;

    cout << "Search Dog: "
         << dict.searchWord("Dog") << endl;

    cout << "\nWords starting with A: "
         << dict.countWordsByLetter('A') << endl;

    cout << "Total words: "
         << dict.countAllWords() << endl;

    cout << "Longest word: "
         << dict.findLongestWord() << endl;

    cout << "\nDeleting Apple: "
         << dict.deleteWord("Apple") << endl;

    cout << "Search Apple after deletion: "
         << dict.searchWord("Apple") << endl;

    cout << "Total words after deletion: "
         << dict.countAllWords() << endl;

    return 0;
}
