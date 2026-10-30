#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int versionID;
    string text;
    string operation;

    Node *prev;
    Node *next;

    Node(int id, string t, string op)
    {
        versionID = id;
        text = t;
        operation = op;

        prev = nullptr;
        next = nullptr;
    }
};

class TextEditor
{
private:
    Node *head;
    Node *tail;
    Node *current;

    int nextVersionID;

    void saveVersion(string text, string operation)
    {
        if (current != nullptr)
        {
            Node *temp = current->next;

            while (temp != nullptr)
            {
                Node *nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }

            current->next = nullptr;
            tail = current;
        }

        Node *newNode = new Node(
            nextVersionID++,
            text,
            operation);

        if (head == nullptr)
        {
            head = tail = current = newNode;
        }
        else
        {
            newNode->prev = current;
            current->next = newNode;

            tail = newNode;
            current = newNode;
        }
    }

public:
    TextEditor()
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;

        nextVersionID = 1;
    }

    void insertText(string text)
    {
        string newText = "";

        if (current != nullptr)
            newText = current->text;

        newText += text;

        saveVersion(newText, "Insert");
    }

    void deleteText(int position, int count)
    {
        if (current == nullptr)
        {
            cout << "Document is empty.\n";
            return;
        }

        if (position < 0 || position >= current->text.length() || count <= 0)
        {
            cout << "Invalid position or count.\n";
            return;
        }

        string newText = current->text;

        newText.erase(position, count);

        saveVersion(newText, "Delete");
    }

    void replaceText(string oldText, string newText)
    {
        if (current == nullptr)
        {
            cout << "Document is empty.\n";
            return;
        }

        string text = current->text;

        size_t position = text.find(oldText);

        if (position == string::npos)
        {
            cout << "Text not found.\n";
            return;
        }

        text.replace(position, oldText.length(), newText);

        saveVersion(text, "Replace");
    }

    void undo()
    {
        if (current == nullptr || current->prev == nullptr)
        {
            cout << "Cannot undo.\n";
            return;
        }

        current = current->prev;

        showCurrentText();
    }

    void redo()
    {
        if (current == nullptr || current->next == nullptr)
        {
            cout << "Cannot redo.\n";
            return;
        }

        current = current->next;

        showCurrentText();
    }

    void showCurrentText()
    {
        if (current == nullptr)
        {
            cout << "Document is empty.\n";
            return;
        }

        cout << "Current Version: "
             << current->versionID << endl;

        cout << "Text: " << current->text << endl;
    }

    void displayVersions()
    {
        if (head == nullptr)
        {
            cout << "No saved versions.\n";
            return;
        }

        Node *temp = head;

        cout << "\nVersion History:\n";

        while (temp != nullptr)
        {
            cout << "Version ID: " << temp->versionID << endl;
            cout << "Operation: " << temp->operation << endl;
            cout << "Text: " << temp->text << endl;

            if (temp == current)
                cout << "<-- Current Version";

            cout << "\n\n";

            temp = temp->next;
        }
    }

    void clearHistory()
    {
        Node *temp = head;

        while (temp != nullptr)
        {
            Node *nextNode = temp->next;

            delete temp;

            temp = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        current = nullptr;

        cout << "History cleared.\n";
    }

    ~TextEditor()
    {
        Node *temp = head;

        while (temp != nullptr)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main()
{
    TextEditor editor;

    editor.insertText("Hello");
    editor.insertText(" World");
    editor.insertText("!");

    editor.undo();
    editor.undo();

    editor.redo();

    editor.insertText(" C++");

    editor.showCurrentText();

    editor.displayVersions();

    return 0;
}