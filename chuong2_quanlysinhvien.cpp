#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct SinhVien {
    string maSo;
    string hoTen;
    string lop;
    float diemTB;
};

struct Node {
    SinhVien data;
    Node* next;
};

Node* createNode(SinhVien sv) {
    Node* newNode = new Node();
    newNode->data = sv;
    newNode->next = nullptr;
    return newNode;
}

void themCuoi(Node*& head, SinhVien sv) {
    Node* newNode = createNode(sv);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

SinhVien nhapSinhVien() {
    SinhVien sv;
    cout << "Nhap ma so sinh vien: ";
    cin >> sv.maSo;
    cin.ignore(); // Xóa bộ nhớ đệm
    cout << "Nhap ho ten: ";
    getline(cin, sv.hoTen);
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cout << "Nhap diem trung binh: ";
    cin >> sv.diemTB;
    return sv;
}

void inSinhVien(SinhVien sv) {
    cout << left << setw(12) << sv.maSo 
         << setw(25) << sv.hoTen 
         << setw(10) << sv.lop 
         << setw(8) << fixed << setprecision(2) << sv.diemTB << endl;
}

void xuatDanhSach(Node* head) {
    if (head == nullptr) {
        cout << "=> Danh sach rong!\n";
        return;
    }
    cout << "\n---------------- DANH SACH SINH VIEN ----------------\n";
    cout << left << setw(12) << "Ma So" 
         << setw(25) << "Ho Ten" 
         << setw(10) << "Lop" 
         << setw(8) << "Diem TB" << endl;
    cout << string(55, '-') << endl;

    Node* temp = head;
    while (temp != nullptr) {
        inSinhVien(temp->data);
        temp = temp->next;
    }
}

Node* timTheoMa(Node* head, string maSo) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.maSo == maSo) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool xoaTheoMa(Node*& head, string maSo) {
    if (head == nullptr) return false;

    if (head->data.maSo == maSo) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->data.maSo != maSo) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
        return true;
    }

    return false;
}

bool capNhatDiemTB(Node* head, string maSo, float diemMoi) {
    Node* svNode = timTheoMa(head, maSo);
    if (svNode != nullptr) {
        svNode->data.diemTB = diemMoi;
        return true;
    }
    return false;
}

void sapXepDiemGiamDan(Node* head) {
    if (head == nullptr) return;

    for (Node* i = head; i != nullptr && i->next != nullptr; i = i->next) {
        Node* maxNode = i;
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (j->data.diemTB > maxNode->data.diemTB) {
                maxNode = j;
            }
        }
        if (maxNode != i) {
            SinhVien temp = i->data;
            i->data = maxNode->data;
            maxNode->data = temp;
        }
    }
}

Node* timDiemTBCaoNhat(Node* head) {
    if (head == nullptr) return nullptr;

    Node* maxNode = head;
    Node* temp = head->next;
    while (temp != nullptr) {
        if (temp->data.diemTB > maxNode->data.diemTB) {
            maxNode = temp;
        }
        temp = temp->next;
    }
    return maxNode;
}

void giaiPhong(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    int luaChon;

    do {
        cout << "\n================ MENU QUAN LY SINH VIEN ================\n";
        cout << "1. Them sinh vien vao cuoi danh sach\n";
        cout << "2. Tim sinh vien theo ma\n";
        cout << "3. Xoa sinh vien theo ma\n";
        cout << "4. Cap nhat diem trung binh\n";
        cout << "5. Sap xep danh sach theo diem TB giam dan\n";
        cout << "6. Tim sinh vien co diem TB cao nhat\n";
        cout << "7. Xuat toan bo danh sach\n";
        cout << "0. Thoat\n";
        cout << "--------------------------------------------------------\n";
        cout << "Nhap lua chon cua ban (0-7): ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                cout << "\n--- THEM SINH VIEN ---\n";
                SinhVien sv = nhapSinhVien();
                themCuoi(head, sv);
                cout << "=> Da them sinh vien thanh cong!\n";
                break;
            }
            case 2: {
                if (head == nullptr) {
                    cout << "=> Danh sach rong!\n";
                    break;
                }
                string maSo;
                cout << "Nhap ma sinh vien can tim: ";
                cin >> maSo;
                Node* result = timTheoMa(head, maSo);
                if (result != nullptr) {
                    cout << "\nThông tin sinh vien tim thay:\n";
                    inSinhVien(result->data);
                } else {
                    cout << "=> Khong tim thay sinh vien ma: " << maSo << endl;
                }
                break;
            }
            case 3: {
                if (head == nullptr) {
                    cout << "=> Danh sach rong!\n";
                    break;
                }
                string maSo;
                cout << "Nhap ma sinh vien can xoa: ";
                cin >> maSo;
                if (xoaTheoMa(head, maSo)) {
                    cout << "=> Da xoa sinh vien thanh cong!\n";
                } else {
                    cout << "=> Khong tim thay sinh vien de xoa!\n";
                }
                break;
            }
            case 4: {
                if (head == nullptr) {
                    cout << "=> Danh sach rong!\n";
                    break;
                }
                string maSo;
                float diemMoi;
                cout << "Nhap ma sinh vien can cap nhat: ";
                cin >> maSo;
                cout << "Nhap diem trung binh moi: ";
                cin >> diemMoi;
                if (capNhatDiemTB(head, maSo, diemMoi)) {
                    cout << "=> Cap nhat diem thanh cong!\n";
                } else {
                    cout << "=> Khong tim thay sinh vien!\n";
                }
                break;
            }
            case 5: {
                if (head == nullptr) {
                    cout << "=> Danh sach rong!\n";
                    break;
                }
                sapXepDiemGiamDan(head);
                cout << "=> Da sap xep danh sach giam dan theo diem TB!\n";
                xuatDanhSach(head);
                break;
            }
            case 6: {
                if (head == nullptr) {
                    cout << "=> Danh sach rong!\n";
                    break;
                }
                Node* maxSV = timDiemTBCaoNhat(head);
                cout << "\nSinh vien co diem TB cao nhat:\n";
                inSinhVien(maxSV->data);
                break;
            }
            case 7: {
                xuatDanhSach(head);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh...\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai!\n";
        }
    } while (luaChon != 0);

    giaiPhong(head);
    return 0;
}