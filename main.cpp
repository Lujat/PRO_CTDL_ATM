#include<iostream>
#include<fstream>
#include<string>
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
void themtk(){
    string id;
    cin >> id;
    string defaultpin= "123456";
    ofstream fileTheTu("TheTu.txt", ios::app);
    cout << endl;
    fileTheTu <<  id << " " << defaultpin << endl;
    fileTheTu.close();
    string tenFileTaiKhoan = id + ".txt";
    ofstream fileTaiKhoan(tenFileTaiKhoan);
    cout<< endl;
    fileTaiKhoan << "ID: " << id << endl;
    fileTaiKhoan << "PIN: " << defaultpin << endl;
}
int main(){
    hienthiTheTu();
    themtk();
    return 0;
}
