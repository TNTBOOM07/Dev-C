#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct SinhVien {
    string mssv;
    string hoTen;
};

struct Queue {
    SinhVien data[MAX];
    int front;
    int rear;
};

void Init(Queue &q) {
    q.front = 0;
    q.rear = -1;
}

bool IsEmpty(const Queue &q) {
    return q.front > q.rear;
}

bool IsFull(const Queue &q) {
    return q.rear == MAX - 1;
}

bool Enqueue(Queue &q, SinhVien sv) {
    if (IsFull(q)) {
        cout << "[!] Hang doi da day, khong the them SV: " << sv.hoTen << endl;
        return false;
    }
    q.rear++;
    q.data[q.rear] = sv;
    cout << "[+] Da them vao hang doi: " << sv.mssv << " - " << sv.hoTen << endl;
    return true;
}

bool Dequeue(Queue &q, SinhVien &sv) {
    if (IsEmpty(q)) {
        cout << "[!] Hang doi rong, khong co sinh vien de phuc vu!\n";
        return false;
    }
    sv = q.data[q.front];
    q.front++;
    cout << "[-] Da phuc vu xong ho so cho SV: " << sv.mssv << " - " << sv.hoTen << endl;
    return true;
}

bool Front(const Queue &q, SinhVien &sv) {
    if (IsEmpty(q)) return false;
    sv = q.data[q.front];
    return true;
}

void Display(const Queue &q) {
    if (IsEmpty(q)) {
        cout << "\n---> Hang doi dang RONG <--- \n";
        return;
    }
    cout << "\n================ BAN DANG CHO XU LY ================\n";
    int stt = 1;
    for (int i = q.front; i <= q.rear; ++i) {
        cout << stt++ << ". MSSV: " << q.data[i].mssv << " | Ho ten: " << q.data[i].hoTen << endl;
    }
    cout << "====================================================\n\n";
}

int main() {
    Queue q;
    Init(q);

    Enqueue(q, {"SV01", "Nguyen Van A"});
    Enqueue(q, {"SV02", "Tran Thi B"});
    Enqueue(q, {"SV03", "Le Van C"});
    
    Display(q);

    SinhVien headSV;
    if (Front(q, headSV)) {
        cout << ">> Sinh vien dang cho o dau hang: " << headSV.mssv << " - " << headSV.hoTen << endl << endl;
    }

    SinhVien servedSV;
    Dequeue(q, servedSV);
    
    Display(q);

    return 0;
}