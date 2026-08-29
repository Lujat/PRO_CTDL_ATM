#include<iostream>
#include<fstream>
#include<string>
#include <cstdio>
#include<conio.h>
using namespace std;

struct TheTu{
    string ID;
    string pin;
};
struct TaiKhoan{
    string ID;
    string name;
    long long accBalance;
    string currency;
};
// DANG NHAP ADMIN 
bool dangnhapAdmin(){
    string user;
    string pin;

    cout << "************************" << endl;
    cout << "*    DANG NHAP ADMIN   *" << endl;
    cout << "************************" << endl;
    cout << "User: ";
    cin >> user;
    cout <<"Pin: ";
    char ch;
    while(true){
        ch =_getch();
        if(ch==13){
            break;
        }
        if(ch==8){
            if(!pin.empty()){
                pin.pop_back();
                cout <<"\b \b";
            }
        }
        else{
            pin += ch;
            cout <<"*";
        }
    }
    cout << endl;
    ifstream file("Admin.txt");
    if(!file){
        cout<< "ko mo duoc Admin.txt!" << endl;
        return false;
    }
    string userfile;
    string pinfile;
    while(file >> userfile >>pinfile){
        if(userfile == user && pinfile==pin){
            file.close();
            cout<<"Dang nhap thanh cong!";
            return true;
        }
    }
    file.close();
    cout << "sai User hoac pin!";
    return false;
}
void themtk(){
    string id;
    cin >> id;
    string defaultpin= "123456";
    ofstream fileTheTu("TheTu.txt", ios::app);
    cout << endl;
    fileTheTu <<  id << " " << defaultpin << endl;
    fileTheTu.close();
    
    //add file id tk vua them
    string tenFileTaiKhoan = id + ".txt";
    ofstream fileTaiKhoan(tenFileTaiKhoan);
    fileTaiKhoan << "ID: " << id << endl;
    fileTaiKhoan << "PIN: " << defaultpin << endl;
    
    //add file lichsuid tk vua them
    string tenfileLichSu = "LichSu" + id + ".txt" ;
    ofstream fileLichSu(tenfileLichSu);
    fileLichSu << "ID: " << id << endl;
    fileLichSu << "Lich su giao dich:" << endl;
}
void xoatk(){
    string id;
    cout << "nhap id tk can xoa";
    cin >> id;
    string tenfile = id + ".txt";
    //xoa file id
    if(remove(tenfile.c_str())==0){
        cout <<"Xoa file " << tenfile << endl;
    }
    else {
        cout << "khong tim thay file " << tenfile << endl;
    }
    //update thetu.txt = NewTheTu 
    ifstream oldfile("TheTu.txt");
    if(!oldfile){
        cout << "ko mo dc file TheTu.txt" <<endl;
        return;
    }
    ofstream newfile("NewTheTu.txt");
    string idfile;
    string pin;
    while(oldfile >> idfile >> pin){
        if(idfile != id){
            newfile << idfile << " "<< pin << endl;
        }
    }
    oldfile.close();
    newfile.close();
    //xoa file thetu va rename newTheTu
    remove("TheTu.txt");
    rename("NewTheTu.txt", "TheTu.txt");
    cout <<"da xoa va cap nhap thanh cong"<< endl;
}
void hienthiTheTu()
{
    string filename = "TheTu.txt";
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        cout<< line << endl;
    }
    file.close();
}
void menuAdmin(){
    int chose;
    do {
        cout << endl;
        cout << "*************MENU*************" << endl;
        cout << "1. Xem danh sach tai khoan" << endl;
        cout << "2. Them tai khoan" << endl;
        cout << "3. Xoa tai khoan" << endl;
        cout << "4. Mo khoa tai khoan" << endl;
        cout << "5. Thoat" << endl;
        cout << "******************************" << endl;
        cout << "Nhap lua chon: ";
        cin >> chose;


        switch (chose) {
            case 1:
                hienthiTheTu();
                break;
             case 2:
                themtk();
                break;
            case 3:
                xoatk();
                break;
            case 4:
                cout << "Chuc nang mo khoa tai khoan" << endl;
                break;
            case 5:
                cout << "Thoat!" << endl;
                break;

            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (chose != 5);
}    
int main(){
    //hienthiTheTu();
    //themtk();
    //xoatk();
    if (dangnhapAdmin()) {
        menuAdmin();
    }

    return 0;
    

}
