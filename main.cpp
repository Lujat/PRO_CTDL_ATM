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
    bool bikhoa;
    int solansai;
};
//Capnhap file LockAccount(luu so lan dag nhap sai)
void capNhapLockAccount(string idcansua , int solansaimoi , int bikhoamoi){
    ifstream file("LockAccount.txt");
    ofstream temp("LockAccount_temp.txt");
    string id;
    int solansai;
    int bikhoa;
    while(file >> id >> solansai >> bikhoa){
        if(id == idcansua){
            temp << id<<" "<<solansaimoi<<" "<<bikhoamoi<< endl;
        }
        else {
            temp << id <<" "<<solansai<<" "<<bikhoa<<endl;
        }
    }
    file.close();
    temp.close();
    remove("LockAccount.txt");
    rename("LockAccount_temp.txt","LockAccount.txt");
}
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
    //kiem tra nhap sai mk
    ifstream file("Admin.txt");
    if(!file){
        cout<< "ko mo duoc Admin.txt!" << endl;
        return false;
    }
    string userfile;
    string pinfile;
    while(file >> userfile >>pinfile){
        if(userfile == user && pinfile == pin){
            cout <<"Dang nhap thanh cong!";
            file.close();
            return true;
        }
        else{
            cout << "Sai User hoac Pin";
            file.close();
            return false;
        }    
    }   
}
bool dangnhapKhachhang(){
    string id;
    string pin;

    cout << "************************" << endl;
    cout << "* DANG NHAP KHACH HANG *" << endl;
    cout << "************************" << endl;
    cout << "ID: ";
    cin >> id;
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
    ifstream lockFile("LockAccount.txt");
    if(!lockFile){
        cout << " ko mo dc file LockAccount.txt!" << endl;
        return false;
    }    
    string lockID;
    int solansai;
    int khoa;
    //kiemtra tai khoan bi khoa hay ko
    while(lockFile >> lockID >> solansai >> khoa){
        if(lockID == id){
            if(khoa == 1){
                cout << "tai khoan " << id << " da bi khoa" << endl;
                lockFile.close();
                return false;
            }
        }
        break;
    }
    lockFile.close();
    //kiem tra va luu so lan nhap sai mk
    ifstream file("TheTu.txt");
    if(!file){
        cout<< "ko mo duoc TheTu.txt!" << endl;
        return false;
    }
    string idfile;
    string pinfile;
    while(file >> idfile >>pinfile){
        if(idfile == id){
            if(pinfile == pin){
                cout<<"Dang nhap thanh cong!";
                capNhapLockAccount(id, 0, 0);
                file.close();
                return true;
            }
            if(pinfile != pin){
                cout << "sai pin";
                solansai++;
                if(solansai > 3){
                    khoa =1;
                    cout<< "tai khoan cua ban da bi khoa"<<endl;
                    cout<< "ban da nhap sai 3 lan" << endl;
                }
                else{
                    cout << "ban da nhap sai " << solansai << "/3 lan." << endl; 
                }
                capNhapLockAccount(id, solansai, khoa);
                file.close();
                return false;
            }
        }
    }
    file.close();
    return false;
}
void themtk(){
    string id;
    cout << "Nhap id can them: "; 
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
    fileTaiKhoan.close();
    //add file lichsuid tk vua them
    string tenfileLichSu = "LichSu" + id + ".txt" ;
    ofstream fileLichSu(tenfileLichSu);
    fileLichSu << "ID: " << id << endl;
    fileLichSu << "Lich su giao dich:" << endl;
    fileLichSu.close();

    //add file dem so lan nhap sai mk id 
    ofstream fileLock("LockAccount.txt", ios::app);
    fileLock << id << " " << 0 << " " << 0 << endl;
    fileLock.close();
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
void mokhoatk(){
    string id;
    cout<< " Nhap id can mo khoa: ";
    cin >> id;
    ifstream lockfile("LockAccount.txt");
    string lockid;
    int solansai;
    int khoa;
    while (lockfile >> lockid >> solansai >> khoa){
        if(id == lockid){
            solansai =0;
            khoa = 0;
            capNhapLockAccount(id, solansai, khoa);
            cout << "Da mo khoa id thanh cong!";
            break;
        }
    }
    cout << "ko tim thay id can mo khoa: " ;
    lockfile.close();
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
                mokhoatk();
                break;
            case 5:
                cout << "Thoat!" << endl;
                break;

            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (chose != 5);
}
void menuTaikhoan(){
    int chose;
    do {
        cout << endl;
        cout << "*************MENU*************" << endl;
        cout << "1. Xem thong tin tai khoan" << endl;
        cout << "2. Rut tien" << endl;
        cout << "3. Chuyen tien" << endl;
        cout << "4. Xem noi dung giao dich" << endl;
        cout << "5. Doi ma pin" << endl;
        cout << "6. Thoat"<<endl;
        cout << "******************************" << endl;
        cout << "Nhap lua chon: ";
        cin >> chose;


        switch (chose) {
            case 1:
                break;
             case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                cout << "Thoat!" << endl;
                break;    
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (chose != 6);

}    
int main(){
    int choose;
    cout<< "=========================" << endl;
    cout<< "        HE THONG ATM     " <<endl;
    cout<< "=========================" << endl;
    cout<< "1. Dang nhap Admin" << endl;
    cout<< "2. Dang nhap khach hang"<< endl;
    cout<< "3. Thoat" << endl;

    cout << "Nhap lua chon: ";
    cin >> choose ;
    switch (choose)
    {
    case 1:
        if(dangnhapAdmin()){
                menuAdmin();
            }
        break;
    case 2:
        if(dangnhapKhachhang()){
            menuTaikhoan();
        }
    default:
        break;
    }
    return 0;
}
