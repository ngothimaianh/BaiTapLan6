#include <iostream>
#include <string>
using namespace std;

struct File {
    string fileName;
    float size; 
    int time;   
};

struct Node {
    File info;
    Node* next;
};

struct List {
    Node* head;
};

void initList(List &l) {
    l.head = NULL;
}

// Ham chen theo thoi gian 
void insertByTime(List &l, File newFile) {
    Node* newNode = new Node;
    newNode->info = newFile;
    newNode->next = NULL;
    if (l.head == NULL || l.head->info.time > newFile.time) {
        newNode->next = l.head;
        l.head = newNode;
        return;
    }
    Node* p = l.head;
    while (p->next != NULL && p->next->info.time < newFile.time) {
        p = p->next;
    }
    newNode->next = p->next;
    p->next = newNode;
}


// Ham sap xep danh sach theo kich thuoc giam dan
void SapXepDanhSach(List &l) {
    for (Node* p = l.head; p != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (p->info.size < q->info.size) {
                // Hoan doi thong tin giua 2 node [cite: 10]
                File temp = p->info;
                p->info = q->info;
                q->info = temp;
            }
        }
    }
}

// Ham xoa node cuoi cung
void XoaNodeCuoi(List &l) {
    if (l.head == NULL) return;
    
    if (l.head->next == NULL) {
        delete l.head;
        l.head = NULL;
        return;
    }

    Node* p = l.head;
    Node* q = NULL;
    while (p->next != NULL) {
        q = p;
        p = p->next;
    }
    delete p;     
    q->next = NULL; 
}

float TongKichThuoc(List l) {
    float tong = 0;
    Node* p = l.head;
    while (p != NULL) {
        tong += p->info.size;
        p = p->next;
    }
    return tong;
}

// Ham giai phong USB: Sap xep truoc roi xoa duoi 
void GiaiPhongDungLuong(List &l) {
    // sap xep de file be nhat xuong cuoi
    SapXepDanhSach(l);
    
    float limit = 32.0;
    while (TongKichThuoc(l) > limit && l.head != NULL) {
        cout << "Dang xoa file be nhat o cuoi danh sach..." << endl;
        XoaNodeCuoi(l);
    }
}

void printList(List l) {
    Node* p = l.head;
    if (p == NULL) cout << "(Danh sach trong)" << endl;
    while (p != NULL) {
        cout << "- " << p->info.fileName << " (" << p->info.size << " GB)" << endl;
        p = p->next;
    }
}

int main() {
    List folder;
    initList(folder);

    // Gia su co cac file sau (Tong = 45.5 GB)
    insertByTime(folder, {"DanhSach.pptx", 25.0, 1});
    insertByTime(folder, {"Nhac.mp3", 15.0, 2});
    insertByTime(folder, {"TaiLieu.pdf", 0.5, 3});
    insertByTime(folder, {"Video.mp4", 5.0, 4});

    cout << "--- Danh sach ban dau (theo thoi gian) ---" << endl;
    printList(folder);
    cout << "Tong: " << TongKichThuoc(folder) << " GB" << endl;

    cout << "\n--- Tien hanh loc file cho USB 32GB ---" << endl;
    GiaiPhongDungLuong(folder);

    cout << "\n--- Ket qua sau khi xoa cac file be nhat ---" << endl;
    printList(folder);
    cout << "Tong hien tai: " << TongKichThuoc(folder) << " GB" << endl;

    return 0;
}