
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct PrintJob
{
    int jobID;
    string employeeName;
    string documentName;
    int numberOfPages;
    int submissionTime;
};

struct Node
{
    PrintJob data;
    Node *next;

    Node(PrintJob job)
    {
        data = job;
        next = nullptr;
    }
};

void displayJob(const PrintJob &job)
{
    cout << "Job ID: " << job.jobID << endl;
    cout << "Employee Name: " << job.employeeName << endl;
    cout << "Document Name: " << job.documentName << endl;
    cout << "Number of Pages: " << job.numberOfPages << endl;
    cout << "Submission Time: " << job.submissionTime << endl;
    cout << "------------------------" << endl;
}

class Queue
{
private:
    Node *front;
    Node *rear;
    int count;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~Queue()
    {
        PrintJob job;

        while (dequeue(job))
        {
        }
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    int getSize() const
    {
        return count;
    }

    void insertSorted(PrintJob job)
    {
        Node *newNode = new Node(job);

        if (isEmpty())
        {
            front = rear = newNode;
            count++;
            return;
        }

        if (job.numberOfPages < front->data.numberOfPages)
        {
            newNode->next = front;
            front = newNode;
            count++;
            return;
        }

        Node *current = front;

        while (current->next != nullptr &&
               current->next->data.numberOfPages <= job.numberOfPages)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        if (newNode->next == nullptr)
        {
            rear = newNode;
        }

        count++;
    }

    bool dequeue(PrintJob &job)
    {
        if (isEmpty())
        {
            return false;
        }

        Node *temp = front;
        job = temp->data;

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
        count--;

        return true;
    }

    bool processPrintJob()
    {
        PrintJob job;

        if (!dequeue(job))
        {
            cout << "No pending jobs." << endl;
            return false;
        }

        cout << "\nPrinting job..." << endl;
        displayJob(job);

        return true;
    }

    void displayPendingJobs() const
    {
        if (isEmpty())
        {
            cout << "No pending jobs." << endl;
            return;
        }

        Node *current = front;

        while (current != nullptr)
        {
            displayJob(current->data);
            current = current->next;
        }
    }

    bool cancelPrintJob(int jobID)
    {
        Node *current = front;
        Node *previous = nullptr;

        while (current != nullptr)
        {
            if (current->data.jobID == jobID)
            {
                if (previous == nullptr)
                {
                    front = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == rear)
                {
                    rear = previous;
                }

                delete current;
                count--;

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    int calculateTotalPages() const
    {
        int totalPages = 0;
        Node *current = front;

        while (current != nullptr)
        {
            totalPages += current->data.numberOfPages;
            current = current->next;
        }

        return totalPages;
    }
};

class FailedStack
{
private:
    Node *top;
    int count;

public:
    FailedStack()
    {
        top = nullptr;
        count = 0;
    }

    ~FailedStack()
    {
        PrintJob job;

        while (pop(job))
        {
        }
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    int getSize() const
    {
        return count;
    }

    void push(PrintJob job)
    {
        Node *newNode = new Node(job);

        newNode->next = top;
        top = newNode;

        count++;
    }

    bool pop(PrintJob &job)
    {
        if (isEmpty())
        {
            return false;
        }

        Node *temp = top;
        job = temp->data;

        top = top->next;

        delete temp;
        count--;

        return true;
    }

    void displayFailedJobs() const
    {
        if (isEmpty())
        {
            cout << "No failed jobs." << endl;
            return;
        }

        Node *current = top;

        while (current != nullptr)
        {
            displayJob(current->data);
            current = current->next;
        }
    }
};

class PrinterSystem
{
private:
    Queue printQueue;
    FailedStack failedStack;
    int nextJobID;
    int completedJobs;

public:
    PrinterSystem()
    {
        nextJobID = 1;
        completedJobs = 0;
    }

    void submitPrintJob()
    {
        PrintJob job;

        job.jobID = nextJobID++;

        cout << "Enter employee name: ";
        getline(cin >> ws, job.employeeName);

        cout << "Enter document name: ";
        getline(cin, job.documentName);

        cout << "Enter number of pages: ";
        cin >> job.numberOfPages;

        while (job.numberOfPages <= 0)
        {
            cout << "Pages must be greater than zero: ";
            cin >> job.numberOfPages;
        }

        cout << "Enter submission time: ";
        cin >> job.submissionTime;

        printQueue.insertSorted(job);

        cout << "Job submitted successfully. Job ID: "
             << job.jobID << endl;
    }

    void processPrintJob()
    {
        if (printQueue.processPrintJob())
        {
            completedJobs++;
            cout << "Job completed successfully." << endl;
        }
    }

    void displayPendingJobs() const
    {
        cout << "\n--- Pending Jobs (SJF Order) ---\n";
        printQueue.displayPendingJobs();
    }

    void cancelPrintJob()
    {
        int jobID;

        cout << "Enter Job ID to cancel: ";
        cin >> jobID;

        if (printQueue.cancelPrintJob(jobID))
        {
            cout << "Job cancelled successfully." << endl;
        }
        else
        {
            cout << "Job not found in pending queue." << endl;
        }
    }

    void simulatePrinterFailure()
    {
        PrintJob job;

        if (!printQueue.dequeue(job))
        {
            cout << "No pending job to fail." << endl;
            return;
        }

        failedStack.push(job);

        cout << "Printer failure simulated." << endl;
        cout << "Job moved to failed stack:\n";
        displayJob(job);
    }

    void retryFailedJob()
    {
        PrintJob job;

        if (!failedStack.pop(job))
        {
            cout << "No failed jobs to retry." << endl;
            return;
        }

        printQueue.insertSorted(job);

        cout << "Job returned to the priority queue." << endl;
        cout << "Job ID: " << job.jobID << endl;
    }

    void displayFailedJobs() const
    {
        cout << "\n--- Failed Jobs (Most Recent First) ---\n";
        failedStack.displayFailedJobs();
    }

    void displayStatistics() const
    {
        cout << "\n========== STATISTICS ==========\n";
        cout << "Completed jobs: " << completedJobs << endl;
        cout << "Failed jobs awaiting retry: "
             << failedStack.getSize() << endl;
        cout << "Pending jobs: " << printQueue.getSize() << endl;
        cout << "Pages waiting to be printed: "
             << printQueue.calculateTotalPages() << endl;
        cout << "================================\n";
    }

    void run()
    {
        int choice;

        do
        {
            cout << "\n========== PRINTER MANAGEMENT ==========\n";
            cout << "1. Submit Print Job\n";
            cout << "2. Process Print Job\n";
            cout << "3. Pending Jobs\n";
            cout << "4. Cancel Job\n";
            cout << "5. Simulate Failure\n";
            cout << "6. Retry Failed Job\n";
            cout << "7. Failed Jobs\n";
            cout << "8. Statistics\n";
            cout << "9. Exit\n";
            cout << "Choose an option: ";

            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number from 1 to 9.\n";
                continue;
            }

            switch (choice)
            {
            case 1:
                submitPrintJob();
                break;

            case 2:
                processPrintJob();
                break;

            case 3:
                displayPendingJobs();
                break;

            case 4:
                cancelPrintJob();
                break;

            case 5:
                simulatePrinterFailure();
                break;

            case 6:
                retryFailedJob();
                break;

            case 7:
                displayFailedJobs();
                break;

            case 8:
                displayStatistics();
                break;

            case 9:
                cout << "Exiting Printer Management System.\n";
                break;

            default:
                cout << "Invalid choice. Please select 1 to 9.\n";
            }

        } while (choice != 9);
    }
};

int main()
{
    PrinterSystem printer;
    printer.run();

    return 0;
}
