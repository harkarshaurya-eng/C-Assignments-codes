#include <iostream>
#include <string>
using namespace std;

struct Data {
    string Line;
};

class Dnode {
public:
    Data data;
    Dnode* prev;
    Dnode* next;

    Dnode(string line) {
        data.Line = line;
        prev = nullptr;
        next = nullptr;
    }
};

class DLL {
private:
    Dnode* head;

public:
    DLL() {
        head = nullptr;
    }

    void Insert(string line, int pos) {
        Dnode* p = new Dnode(line);

        if (head == NULL) {
            head = p;
            return;
        }

        if (pos == 1) {
            head->prev = p;
            p->next = head;
            head = p;
            return;
        }

       Dnode* temp = head;
        int length = 1;
        while (temp->next) {
            temp = temp->next;
            length++;
        }

        if (pos > length + 1 || pos < 1) {
            cout << "Invalid Position" << endl;
            delete p;
            return;
        }

        
        temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        p->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = p;
        }
        temp->next = p;
        p->prev = temp;
    }

    void DeleteLine(int pos) {
        if (head == NULL) {
            cout << "Nothing to delete, document is empty." << endl;
            return;
        }

        Dnode* temp = head;
        int length = 1;
        while (temp->next) {
            temp = temp->next;
            length++;
        }

        if (pos < 1 || pos > length) {
            cout << "Invalid Position" << endl;
            return;
        }

        temp = head;
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Line " << pos << " deleted." << endl;
    }

    void DisplayScreen() {
        if (!head) {
            cout << "(document is empty)" << endl;
            return;
        }

        Dnode* temp = head;
        int lineNum = 1;
        while (temp) {
            cout << lineNum << ": " << temp->data.Line << endl;
            temp = temp->next;
            lineNum++;
        }
    }

    void SearchText(string keyword) {
        if (!head) {
            cout << "(document is empty)" << endl;
            return;
        }

        Dnode* temp = head;
        int lineNum = 1;
        bool found = false;
        while (temp) {
            if (temp->data.Line.find(keyword) != string::npos) {
                cout << "Found on line " << lineNum << ": " << temp->data.Line << endl;
                found = true;
            }
            temp = temp->next;
            lineNum++;
        }

        if (!found) {
            cout << "\"" << keyword << "\" not found." << endl;
        }
    }

    void printReverseLine() {
        if (!head) {
            cout << "(document is empty)" << endl;
            return;
        }

        Dnode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }

        int lineNum = 0;
        Dnode* counter = head;
        while (counter) {
            lineNum++;
            counter = counter->next;
        }

        while (temp) {
            cout << lineNum << ": " << temp->data.Line << endl;
            temp = temp->prev;
            lineNum--;
        }
    }

    void ClearAll() {
        Dnode* temp = head;
        while (temp) {
            Dnode* next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
    }
};

int main() {
    int choice;
    DLL L1;
    string lineText, keyword;
    int pos;

    L1.Insert("My name is shaurya", 1);

    do {
        cout << "\n---- Text Editor ----" << endl;
        cout << "[1] Insert line" << endl;
        cout << "[2] Delete line" << endl;
        cout << "[3] Display screen" << endl;
        cout << "[4] Search text" << endl;
        cout << "[5] Print lines in reverse" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "No more input" << endl;
            break;
        }
        cin.ignore(); 

        switch (choice) {
            case 1: {
                cout << "Enter line text: ";
                getline(cin, lineText);
                cout << "Enter line number to insert at:";
                cin >> pos;
                L1.Insert(lineText, pos);
                break;
            }
            case 2: {
                cout << "Enter line number to delete: ";
                cin >> pos;
                L1.DeleteLine(pos);
                break;
            }
            case 3:
                L1.DisplayScreen();
                break;
            case 4: {
                cout << "Enter text to search for:";
                getline(cin, keyword);
                L1.SearchText(keyword);
                break;
            }
            case 5:
                L1.printReverseLine();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    L1.ClearAll();
    return 0;
}
