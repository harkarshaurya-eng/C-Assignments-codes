#include <iostream>
#include <string>

using namespace std;

struct Data {
    string name;
    string singer;
    float duration;
};

class Dnode {
public:
    Data data;
    Dnode* prev;
    Dnode* next;

    Dnode(string name, string singer, float duration) {
        data.name = name;
        data.singer = singer;
        data.duration = duration;
        prev = NULL;
        next = NULL;
    }
};

class DLL {
private:
    Dnode* head;

public:
    DLL() { head = NULL; }




    /*
    Insert(value, pos)
    ├── 1. Is the list empty? -> head = newNode
    ├── 2. Is pos == 1?       -> Insert at Beginning
    ├── 3. Is the position valid?
    ├── 4. Traverse to (pos-1)th node
    ├── 5. Is temp->next == NULL? -> Insert at End : Insert in Middle
    */
    void Insert(string name, string singer, float duration, int pos) {
        Dnode* p = new Dnode(name, singer, duration);

        // empty list
        if (head == NULL) {
            head = p;
            return;
        }

        // insert at head
        if (pos == 1) {
            head->prev = p;
            p->next = head;
            head = p;
            return;
        }

        // find length
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

        // traverse to (pos-1)th node
        temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        // insert in middle / end
        p->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = p;
        }
        temp->next = p;
        p->prev = temp;
    }

    // Remove a song by name
    void Remove(string songName) {
        Dnode* temp = head;
        while (temp && temp->data.name != songName) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Song not found!!" << endl;
            return;
        }

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            // removing head
            head = temp->next;
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Song removed." << endl;
    }

    void searchSong(string SearchSong) {
        Dnode* temp = head;
        while (temp && temp->data.name != SearchSong) {
            temp = temp->next;
        }

        if (temp) {
            cout << "Playing: " << temp->data.name << endl;
        } else {
            cout << "Song not found!!" << endl;
        }
    }

    // Display all songs by a particular artist
    void DisplayByArtist(string artist) {
        Dnode* temp = head;
        bool found = false;
        cout << "Songs by " << artist << ":" << endl;
        while (temp) {
            if (temp->data.singer == artist) {
                cout << temp->data.name << "   " << temp->data.duration << " min" << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No songs found for this artist." << endl;
        }
    }

    // Find and display the longest song
    void FindLongestSong() {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }

        Dnode* temp = head;
        Dnode* longest = head;
        while (temp) {
            if (temp->data.duration > longest->data.duration) {
                longest = temp;
            }
            temp = temp->next;
        }

        cout << "Longest song: " << longest->data.name
             << " by " << longest->data.singer
             << " (" << longest->data.duration << " min)" << endl;
    }

    // Delete all songs of a particular artist
    void DeleteByArtist(string artist) {
        Dnode* temp = head;
        bool found = false;
        while (temp) {
            Dnode* next = temp->next; // save next before possible deletion
            if (temp->data.singer == artist) {
                if (temp->prev) {
                    temp->prev->next = temp->next;
                } else {
                    head = temp->next;
                }
                if (temp->next) {
                    temp->next->prev = temp->prev;
                }
                delete temp;
                found = true;
            }
            temp = next;
        }
        if (found)
            cout << "All songs by " << artist << " removed." << endl;
        else
            cout << "No songs found for this artist." << endl;
    }

    void Display() {
        if (!head) {
            cout << "Playlist is empty." << endl;
            return;
        }
        Dnode* temp = head;
        cout << "Name                 Singer               Duration" << endl;
        while (temp) {
            cout << temp->data.name << "   " << temp->data.singer
                 << "              " << temp->data.duration << endl;
            temp = temp->next;
        }
    }
};

int main() {
    int choice;
    DLL l1;
    string enterName, enterSinger;
    float enterDuration;
    int pos;

    // seed a couple of songs so the playlist isn't empty at start
    l1.Insert("Tum Hi Ho", "Arijit Singh", 3.25, 1);
    l1.Insert("Vande Mataram", "Tagore", 2.51, 1);

    do {
        cout << "\n[1] Add song" << endl;
        cout << "[2] Remove song" << endl;
        cout << "[3] Display Playlist" << endl;
        cout << "[4] Display songs of particular artist" << endl;
        cout << "[5] Find longest song" << endl;
        cout << "[6] Delete all the songs of an artist" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "No more input. Exiting..." << endl;
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Enter the song name: ";
                cin >> enterName;
                cout << "Enter the singer: ";
                cin >> enterSinger;
                cout << "Enter the duration (minutes): ";
                cin >> enterDuration;
                cout << "Enter position to insert at (1 = start): ";
                cin >> pos;
                l1.Insert(enterName, enterSinger, enterDuration, pos);
                break;
            }
            case 2: {
                cout << "Enter the song name to remove: ";
                cin >> enterName;
                l1.Remove(enterName);
                break;
            }
            case 3:
                l1.Display();
                break;
            case 4: {
                cout << "Enter artist name: ";
                cin >> enterSinger;
                l1.DisplayByArtist(enterSinger);
                break;
            }
            case 5:
                l1.FindLongestSong();
                break;
            case 6: {
                cout << "Enter artist name: ";
                cin >> enterSinger;
                l1.DeleteByArtist(enterSinger);
                break;
            }
            case 0:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
