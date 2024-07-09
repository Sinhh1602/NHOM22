#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct SV {
    string hoten;
    int msv;
    float diem;
};

struct Node {
    SV data;
    Node *next;
    Node *pre;
};

struct doubleList {
    Node *head;
    Node *tail;
};

void initialize(doubleList &list) {
    list.head = NULL;
    list.tail = NULL;
}

Node *createNode(SV d) {
    Node *pNode = new Node;
    pNode->data = d;
    pNode->next = NULL;
    pNode->pre = NULL;
    return pNode;
}

// 1. Nhap thong tin sinh vien
SV inputSV() {
    SV d;
    cout << "Nhap ma SV: ";
    cin >> d.msv;
    cout << "Nhap ten sinh vien: ";
    cin.ignore();
    getline(cin, d.hoten);
    cout << "Nhap diem cua sinh vien: ";
    cin >> d.diem;
    return d;
}

// 2. Them dau
void insertFirst(doubleList &list, SV d) {
    Node *pNode = createNode(d);
    if (list.head == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->next = list.head;
        list.head->pre = pNode;
        list.head = pNode;
    }
}

// 3. Them cuoi
void insertLast(doubleList &list, SV d) {
    Node *pNode = createNode(d);
    if (list.tail == NULL) {
        list.head = pNode;
        list.tail = pNode;
    } else {
        pNode->pre = list.tail;
        list.tail->next = pNode;
        list.tail = pNode;
    }
}

// 4. Chen giua
void insertMid(doubleList &list, SV d, int pos) {
    if (pos == 0 || list.head == NULL) {
        insertFirst(list, d);
    } else {
        Node *p = list.head;
        int currentPos = 0;
        while (p != NULL && currentPos < pos - 1) {
            p = p->next;
            currentPos++;
        }
        if (p != NULL && p->next != NULL) {
            Node *pNode = createNode(d);
            pNode->next = p->next;
            pNode->pre = p;
            p->next->pre = pNode;
            p->next = pNode;
        } else {
            insertLast(list, d);
        }
    }
}

// 5. Xoa sinh vien theo ma sinh vien
void deleteByMaSV(doubleList &list, int msv) {
    Node *p = list.head;
    while (p != NULL && p->data.msv != msv) {
        p = p->next;
    }

    if (p == NULL) return;

    if (p->pre != NULL) {
        p->pre->next = p->next;
    } else {
        list.head = p->next;
    }

    if (p->next != NULL) {
        p->next->pre = p->pre;
    } else {
        list.tail = p->pre;
    }

    delete p;
}

// 6. Xoa sinh vien theo ten sinh vien
void deleteByTenSV(doubleList &list, string tenSV) {
    Node *p = list.head;
    while (p != NULL && p->data.hoten != tenSV) {
        p = p->next;
    }

    if (p == NULL) return;

    if (p->pre != NULL) {
        p->pre->next = p->next;
    } else {
        list.head = p->next;
    }

    if (p->next != NULL) {
        p->next->pre = p->pre;
    } else {
        list.tail = p->pre;
    }

    delete p;
}

// 7. Xoa nhung sinh vien co diem thap hon 3
void deleteSVUnderMinDiem(doubleList &list, float minDiem) {
    Node *current = list.head;
    Node *temp;

    while (current != NULL) {
        if (current->data.diem < minDiem) {
            if (current == list.head) {
                list.head = current->next;
                if (list.head != NULL)
                    list.head->pre = NULL;
                delete current;
                current = list.head;
            } else if (current == list.tail) {
                list.tail = current->pre;
                list.tail->next = NULL;
                delete current;
                current = NULL;
            } else {
                temp = current;
                current->pre->next = current->next;
                current->next->pre = current->pre;
                current = current->next;
                delete temp;
            }
        } else {
            current = current->next;
        }
    }
}

// 8. Xoa toan bo sinh vien trong danh sach
void deleteAllSV(doubleList &list) {
    Node *current = list.head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    list.head = NULL;
    list.tail = NULL;
}

// 9. In danh sach sinh vien
void printList(const doubleList &list) {
    Node *p = list.head;
    cout << "|" << setw(10) << left << "Ma SV" << "|" << setw(20) << "Ten SV" << "|" << setw(10) << "Diem" << "|" << endl;
    while (p != NULL) {
        cout << "|" << setw(10) << left << p->data.msv << "|" << setw(20) << p->data.hoten << "|" << setw(10) << p->data.diem << "|" << endl;
        p = p->next;
    }
}

// 10. Tim sinh vien co diem lon hon 4
void searchSVAboveThreshold(doubleList list, float threshold) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.diem > threshold) {
            cout << "Ma SV: " << temp->data.msv << ", Ten SV: " << temp->data.hoten << ", Diem: " << temp->data.diem << endl;
        }
        temp = temp->next;
    }
}

// 11. Tim sinh vien co diem nho hon 4
void searchSVUnderThreshold(doubleList list, float threshold) {
    Node *temp = list.head;
    bool found = false;
    while (temp != NULL) {
        if (temp->data.diem < threshold) {
            cout << "Ma SV: " << temp->data.msv << ", Ten SV: " << temp->data.hoten << ", Diem: " << temp->data.diem << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "Khong co sinh vien nao co diem nho hon " << threshold << "." << endl;
    }
}


//12. tim du an trong khoang tu 3 den 5
void findProjectsInRange(doubleList list, float minDiem, float maxDiem) {
    Node *current = list.head;
    bool found = false;

    while (current != NULL) {
        if (current->data.diem >= minDiem && current->data.diem <= maxDiem) {
            found = true;
            cout << "Ma sinh vien: " << current->data.msv << endl;
            cout << "Ten sinh vien: " << current->data.hoten << endl;
            cout << "Diem: " << current->data.diem << endl << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Khong tim thay sinh vien nao trong khoang diem yeu cau." << endl;
    }
}

// 13. Tim sinh vien theo ma sinh vien
void searchProjectByID(doubleList list, int msv) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.msv == msv) {
            cout << "Tim thay: Ma Sinh Vien: " << temp->data.msv << ", Ten Sinh Vien: " << temp->data.hoten << ", Diem: " << temp->data.diem << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Sinh vien co Ma Sinh Vien " << msv << " khong ton tai." << endl;
}

// 14. Tim sinh vien theo ten sinh vien
void searchProjectByName(doubleList list, string hoten) {
    Node *temp = list.head;
    while (temp != NULL) {
        if (temp->data.hoten == hoten) {
            cout << "Tim thay: Ma Sinh Vien: " << temp->data.msv << ", Ten Sinh Vien: " << temp->data.hoten << ", Diem: " << temp->data.diem << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Sinh vien co ten " << hoten << " khong ton tai." << endl;
}

// 15. sap xep sinh vien theo diem tang dan 
void sortByDiemAscending(doubleList &list) {
    if (list.head == NULL || list.head->next == NULL) {
        return;
    }
    Node *current = list.head;
    Node *index = NULL;
    SV temp;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->data.diem > index->data.diem) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

// 16. sap xep sinh vien theo diem giam dan 
void sortByDiemDescending(doubleList &list) {
    if (list.head == NULL || list.head->next == NULL) {
        return;
    }

    Node *current = list.head;
    Node *index = NULL;
    SV temp;

    while (current != NULL) {
        index = current->next;

        while (index != NULL) {
            if (current->data.diem < index->data.diem) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

// 17. Dem so sinh vien trong danh sach
int countProjects(doubleList list) {
    Node *current = list.head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

// 18. Tinh diem trung binh diem cua tat ca cac sinh vien 
float calculateAverageDiem(const doubleList &list) {
    Node *current = list.head;
    float totalDiem = 0;
    int studentCount = 0;

    while (current != NULL) {
        totalDiem += current->data.diem;
        studentCount++;
        current = current->next;
    }

    if (studentCount == 0) {
        // Danh sách r?ng
        return 0;
    }

    // Tính trung bình diem
    return totalDiem / studentCount;
}

// 19 .Thay doi diem sinh vien theo ma xinh vien
void changeDiemByMSV(doubleList &list, int msv, float newDiem) {
    Node *current = list.head;

    while (current != NULL) {
        if (current->data.msv == msv) {
            current->data.diem = newDiem;
            return;
        }
        current = current->next;
    }

    cout << "Khong tim thay sinh vien co Ma Sinh Vien " << msv << "." << endl;
}

// 20.Tim sinh vien co diem cao nhat
void displayStudentWithHighestDiem(const doubleList &list) {
    if (list.head == NULL) {
        cout << "Danh sach sinh vien rong." << endl;
        return;
    }

    Node *current = list.head;
    SV maxDiemStudent = current->data;

    while (current != NULL) {
        if (current->data.diem > maxDiemStudent.diem) {
            maxDiemStudent = current->data;
        }
        current = current->next;
    }

    cout << "Sinh vien co diem cao nhat: " << endl;
    cout << "Ma Sinh Vien: " << maxDiemStudent.msv << endl;
    cout << "Ten Sinh Vien: " << maxDiemStudent.hoten << endl;
    cout << "Diem: " << maxDiemStudent.diem << endl;
}

// 21.Tim sinh vien co diem thap nhat
void displayStudentWithLowestDiem(const doubleList &list) {
    if (list.head == NULL) {
        cout << "Danh sach sinh vien rong." << endl;
        return;
    }

    Node *current = list.head;
    SV minDiemStudent = current->data;

    while (current != NULL) {
        if (current->data.diem < minDiemStudent.diem) {
            minDiemStudent = current->data;
        }
        current = current->next;
    }

    cout << "Sinh vien co diem thap nhat: " << endl;
    cout << "Ma Sinh Vien: " << minDiemStudent.msv << endl;
    cout << "Ten Sinh Vien: " << minDiemStudent.hoten << endl;
    cout << "Diem: " << minDiemStudent.diem << endl;
}

// 22. Them du lieu vao tep
void saveToFile(const doubleList &list, const string &filename) {
    ofstream outFile(filename.c_str());  
    if (!outFile) {
        cout << "Khong the mo tep de ghi du lieu.\n";
        return;
    }
    Node *p = list.head;
    while (p != NULL) {
        outFile << p->data.msv << "\n" << p->data.hoten << "\n" << p->data.diem << "\n";
        p = p->next;
    }
    outFile.close();
    cout << "Da luu du lieu vao tep " << filename << endl;
}

// 23. Nap du lieu tu tep
void loadFromFile(doubleList &list, const string &filename) {
    ifstream inFile(filename.c_str());  
    if (!inFile) {
        cout << "Khong the mo tep de doc du lieu.\n";
        return;
    }
    initialize(list);  
    SV d;
    while (inFile >> d.msv) {
        inFile.ignore(); // Clear newline character from input buffer
        getline(inFile, d.hoten);
        inFile >> d.diem;
        inFile.ignore(); // Clear newline character from input buffer
        insertLast(list, d);
    }
    inFile.close();
    cout << "Da nap du lieu tu tep " << filename << endl;
}


// Menu
void displayMenu() {
    cout << "==================== MENU ====================" << endl;
    cout << "1. Nhap thong tin sinh vien" << endl;
    cout << "2. Them sinh vien vao dau danh sach" << endl;
    cout << "3. Them sinh vien vao cuoi danh sach" << endl;
    cout << "4. Chen sinh vien vao vi tri bat ky trong danh sach" << endl;
    cout << "5. Xoa sinh vien theo ma sinh vien" << endl;
    cout << "6. Xoa sinh vien theo ten sinh vien" << endl;
    cout << "7. Xoa sinh vien co diem thap hon mot nguong" << endl;
    cout << "8. Xoa toan bo sinh vien trong danh sach" << endl;
    cout << "9. In danh sach sinh vien" << endl;
    cout << "10. Tim sinh vien co diem lon hon mot nguong" << endl;
    cout << "11. Tim sinh vien co diem nho hon mot nguong" << endl;
    cout << "12. Tim sinh vien co diem trong mot khoang" << endl;
    cout << "13. Tim sinh vien theo ma sinh vien" << endl;
    cout << "14. Tim sinh vien theo ten sinh vien" << endl;
    cout << "15. Sap xep sinh vien theo diem tang dan" << endl;
    cout << "16. Sap xep sinh vien theo diem giam dan" << endl;
    cout << "17. Dem so sinh vien trong danh sach" << endl;
    cout << "18. Tinh diem trung binh cua tat ca sinh vien" << endl;
    cout << "19. Thay doi diem cua sinh vien theo ma sinh vien" << endl;
    cout << "20. Hien thi sinh vien co diem cao nhat" << endl;
    cout << "21. Hien thi sinh vien co diem thap nhat" << endl;
    cout << "22. Luu du lieu vao tep" << endl;
    cout << "23. Nap du lieu tu tep" << endl;
    cout << "24. Thoat chuong trinh" << endl;
}

int getMenuChoice() {
    int choice;
    cout << "Nhap lua chon cua ban: ";
    cin >> choice;
    return choice;
}

void processMenuChoice(doubleList &list) {
    int choice;
    do {
        displayMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1: {
                SV student = inputSV();
                insertLast(list, student);
                break;
            }
            case 2: {
                SV student = inputSV();
                insertFirst(list, student);
                break;
            }
            case 3: {
                SV student = inputSV();
                insertLast(list, student);
                break;
            }
            case 4: {
                int pos;
                cout << "Nhap vi tri muon chen: ";
                cin >> pos;
                SV student = inputSV();
                insertMid(list, student, pos);
                break;
            }
            case 5: {
                int msv;
                cout << "Nhap ma sinh vien muon xoa: ";
                cin >> msv;
                deleteByMaSV(list, msv);
                break;
            }
            case 6: {
                string tenSV;
                cout << "Nhap ten sinh vien muon xoa: ";
                cin.ignore();
                getline(cin, tenSV);
                deleteByTenSV(list, tenSV);
                break;
            }
            case 7: {
                float minDiem;
                cout << "Nhap nguong diem: ";
                cin >> minDiem;
                deleteSVUnderMinDiem(list, minDiem);
                break;
            }
            case 8: {
                deleteAllSV(list);
                break;
            }
            case 9: {
                printList(list);
                break;
            }
            case 10: {
                float threshold;
                cout << "Nhap nguong diem: ";
                cin >> threshold;
                searchSVAboveThreshold(list, threshold);
                break;
            }
            case 11: {
                float threshold;
                cout << "Nhap nguong diem: ";
                cin >> threshold;
                searchSVUnderThreshold(list, threshold);
                break;
            }
            case 12: {
                float minDiem, maxDiem;
                cout << "Nhap nguong diem thap nhat: ";
                cin >> minDiem;
                cout << "Nhap nguong diem cao nhat: ";
                cin >> maxDiem;
                findProjectsInRange(list, minDiem, maxDiem);
                break;
            }
            case 13: {
                int msv;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> msv;
                searchProjectByID(list, msv);
                break;
            }
            case 14: {
                string hoten;
                cout << "Nhap ten sinh vien can tim: ";
                cin.ignore();
                getline(cin, hoten);
                searchProjectByName(list, hoten);
                break;
            }
            case 15: {
                sortByDiemAscending(list);
                break;
            }
            case 16: {
                sortByDiemDescending(list);
                break;
            }
            case 17: {
                cout << "So sinh vien trong danh sach: " << countProjects(list) << endl;
                break;
            }
            case 18: {
                cout << "Diem trung binh cua tat ca sinh vien: " << calculateAverageDiem(list) << endl;
                break;
            }
            case 19: {
                int msv;
                float newDiem;
                cout << "Nhap ma sinh vien can thay doi diem: ";
                cin >> msv;
                cout << "Nhap diem moi: ";
                cin >> newDiem;
                changeDiemByMSV(list, msv, newDiem);
                break;
            }
            case 20: {
                displayStudentWithHighestDiem(list);
                break;
            }
            case 21: {
                displayStudentWithLowestDiem(list);
                break;
            }
            case 22: {
                string filename;
                cout << "Nhap ten tep muon luu: ";
                cin >> filename;
                saveToFile(list, filename);
                break;
            }
            case 23: {
                string filename;
                cout << "Nhap ten tep muon nap: ";
                cin >> filename;
                loadFromFile(list, filename);
                break;
            }
            case 24: {
                cout << "Chuong trinh ket thuc. Hen gap lai!" << endl;
                break;
            }
            default:
                cout << "Lua chon khong hop le. Vui long chon lai";
        }
        cout << endl; // Thêm d?u cách tr?ng d? tránh hi?n th? menu l?p l?i ngay l?p t?c
    } while (choice != 24); // Thêm d?u cách tr?ng d? tránh hi?n th? menu l?p l?i ngay l?p t?c
}

int main() {
    doubleList list;
    initialize(list);
    processMenuChoice(list); // G?i hàm processMenuChoice thay vì displayMenu
    return 0;
}


