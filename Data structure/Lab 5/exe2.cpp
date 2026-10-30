#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

struct TrieNode
{
    TrieNode *children[26];
    bool isEndOfWord;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;

        isEndOfWord = false;
    }
};

class Trie
{
private:
    TrieNode *root;

    string normalize(string word)
    {
        string result = "";

        for (char ch : word)
        {
            if (!isalpha(static_cast<unsigned char>(ch)))
                return "";

            result += static_cast<char>(
                tolower(static_cast<unsigned char>(ch)));
        }

        return result;
    }

    void collectWords(TrieNode *node, string &currentWord,
                      vector<string> &suggestions, int limit)
    {
        if (node == nullptr || suggestions.size() >= limit)
            return;

        if (node->isEndOfWord)
            suggestions.push_back(currentWord);

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                currentWord += static_cast<char>('a' + i);

                collectWords(node->children[i], currentWord,
                             suggestions, limit);

                currentWord.pop_back();

                if (suggestions.size() >= limit)
                    return;
            }
        }
    }

    void deleteTrie(TrieNode *node)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < 26; i++)
            deleteTrie(node->children[i]);

        delete node;
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    Trie(const Trie &) = delete;
    Trie &operator=(const Trie &) = delete;

    bool insert(string word)
    {
        word = normalize(word);

        if (word.empty())
            return false;

        TrieNode *current = root;

        for (char ch : word)
        {
            int index = ch - 'a';

            if (current->children[index] == nullptr)
                current->children[index] = new TrieNode();

            current = current->children[index];
        }

        if (current->isEndOfWord)
            return false;

        current->isEndOfWord = true;
        return true;
    }

    bool search(string word)
    {
        word = normalize(word);

        if (word.empty())
            return false;

        TrieNode *current = root;

        for (char ch : word)
        {
            int index = ch - 'a';

            if (current->children[index] == nullptr)
                return false;

            current = current->children[index];
        }

        return current->isEndOfWord;
    }

    void autocomplete(string prefix, int limit = 10)
    {
        prefix = normalize(prefix);

        if (prefix.empty())
        {
            cout << "Invalid prefix.\n";
            return;
        }

        TrieNode *current = root;

        for (char ch : prefix)
        {
            int index = ch - 'a';

            if (current->children[index] == nullptr)
            {
                cout << "No suggestions found.\n";
                return;
            }

            current = current->children[index];
        }

        vector<string> suggestions;
        string currentWord = prefix;

        collectWords(current, currentWord, suggestions, limit);

        if (suggestions.empty())
        {
            cout << "No suggestions found.\n";
            return;
        }

        cout << "\nAutocomplete Suggestions:\n";

        for (int i = 0; i < suggestions.size(); i++)
            cout << i + 1 << ". " << suggestions[i] << endl;
    }

    int loadFromFile(string fileName)
    {
        ifstream file(fileName);

        if (!file.is_open())
        {
            cout << "Could not open the file.\n";
            return -1;
        }

        string word;
        int count = 0;

        while (file >> word)
        {
            if (insert(word))
                count++;
        }

        file.close();

        return count;
    }

    ~Trie()
    {
        deleteTrie(root);
    }
};

int main()
{
    Trie dictionary;

    int loadedWords = dictionary.loadFromFile("words.txt");

    if (loadedWords == -1)
        return 0;

    cout << loadedWords << " words loaded successfully.\n";

    int choice;
    string word;

    do
    {
        cout << "\n===== ENGLISH DICTIONARY =====\n";
        cout << "1. Search for a word\n";
        cout << "2. Autocomplete\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter word: ";
            cin >> word;

            if (dictionary.search(word))
                cout << "Word found in dictionary.\n";
            else
                cout << "Word not found.\n";

            break;

        case 2:
            cout << "Enter prefix: ";
            cin >> word;

            dictionary.autocomplete(word);
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
