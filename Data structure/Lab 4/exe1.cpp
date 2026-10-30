#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string url;
    string title;

    Node *prev;
    Node *next;

    Node(string u, string t)
    {
        url = u;
        title = t;
        prev = nullptr;
        next = nullptr;
    }
};

class Browser
{
private:
    Node *head;
    Node *tail;
    Node *current;

public:
    Browser()
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    void visitPage(string url, string title)
    {
        Node *newNode = new Node(url, title);

        if (head == nullptr)
        {
            head = tail = current = newNode;
            return;
        }

        Node *temp = current->next;

        while (temp != nullptr)
        {
            Node *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        current->next = nullptr;
        tail = current;

        newNode->prev = current;
        current->next = newNode;

        tail = newNode;
        current = newNode;
    }

    void goBack()
    {
        if (current == nullptr || current->prev == nullptr)
        {
            cout << "Cannot go back!\n";
            return;
        }

        current = current->prev;
        showCurrentPage();
    }

    void goForward()
    {
        if (current == nullptr || current->next == nullptr)
        {
            cout << "Cannot go forward!\n";
            return;
        }

        current = current->next;
        showCurrentPage();
    }

    void showCurrentPage()
    {
        if (current == nullptr)
        {
            cout << "No page visited yet.\n";
            return;
        }

        cout << "Current Page: " << current->title << endl;
        cout << "URL: " << current->url << endl;
    }

    void displayHistory()
    {
        if (head == nullptr)
        {
            cout << "History is empty.\n";
            return;
        }

        Node *temp = head;

        cout << "\nBrowser History:\n";

        while (temp != nullptr)
        {
            cout << temp->title;

            if (temp == current)
                cout << " <-- Current";

            if (temp->next != nullptr)
                cout << " <-> ";

            temp = temp->next;
        }

        cout << endl;
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

        cout << "History cleared successfully.\n";
    }

    ~Browser()
    {
        clearHistory();
    }
};

int main()
{
    Browser browser;

    browser.visitPage("google.com", "Google");
    browser.visitPage("youtube.com", "YouTube");
    browser.visitPage("facebook.com", "Facebook");

    browser.goBack();
    browser.goBack();

    browser.goForward();

    browser.visitPage("github.com", "GitHub");

    browser.displayHistory();

    return 0;
}
