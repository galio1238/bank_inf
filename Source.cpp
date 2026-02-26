#include<iostream>
#include<string>
#include<vector>
#include"Bank.h"
#include<fstream>

vector<customer> Cus;

using namespace std;
admin CreateAdmin() {
	admin r = admin();
	r.setPass("1234");
	r.setUsername("galio");
	r.setID(1);
	r.setSSN("12345");
	r.setName("Ido");
	r.setOrganization("UC");
	r.setDOB("07/12/2000");
	r.setDOJ("y");
	r.SetRank("Manager");
	return r;
}


string Incrypt(string str) {
	int n = str.length();
	char temp;
	string newstr;
	if (n % 2 == 0) {
		for (int i = 0; i < n; i++) {
			temp = str[i] + 3;
			newstr += temp;
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			temp = str[i] + 4;
			newstr += temp;
		}
	}
	return newstr;
}

string Decrypt(string str) {
	int n = str.length();
	char temp;
	string newstr;
	if (n % 2 == 0) {
		for (int i = 0; i < n; i++) {
			temp = str[i] - 3;
			newstr += temp;
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			temp = str[i] - 4;
			newstr += temp;
		}
	}
	return newstr;
}
string get_hash(string str) {
	int n = str.length();
	const int p = 31, m = 1e9 + 7;
	long long hash = 0;
	long p_pow = 1;
	for (int i = 0; i < n; i++) {
		if (str[i] > 96) {
			hash = ((hash + str[i] - 'A' + 1) * p_pow) % m;
			p_pow = (p_pow * p) % m;
		}
		

	}
	return to_string(hash);
}

	

bool CheckUser_exist(string str, vector<customer> c) {
	bool check = false;
	int n = c.size();
	for (int i = 0; i < n; i++) {
		if (c[i].GetUSER() == str) {
			check = true;
		}
	}
	return check;
}
void WriteCus(vector<customer> c) {
	if (!c.empty()) {
		int n = c.size();
		ofstream file1;
		file1.open("CusInfo.txt");
		if (!file1.is_open()) {
			cout << "File is not opened";
		}
		for (int i = 0; i < n; i++) {
			string str = to_string(c[i].GetID());
			string user, pass, name, type, Org, Dob, SSN, Doj,warning;
			user = c[i].GetUSER();
			pass = c[i].GetPassword();
			name = c[i].GetNAME();
			type = c[i].GetType();
			Org = c[i].GetORG();
			Dob = c[i].GetDob();
			SSN = c[i].GetSsn();
			Doj = c[i].GetDoj();
			warning = to_string(c[i].GetWarning());
			int balance = c[i].GetBalance();
			file1 << (str) << " " << Incrypt(user) << " " << pass << " " << Incrypt(name) << " " << Incrypt(type) << " " << Incrypt(Org) << " " << Incrypt(Dob) << " " << Incrypt(SSN) << " " << Incrypt(Doj) <<" "<< warning <<" "<< balance<< endl;
		}
		file1.close();
	}
}

vector<customer> ReadTransaction(vector<customer> c) {
	if (!c.empty()) {
		ifstream inputfile;
		string line;
		int j = 0;
		inputfile.open("Transaction.txt");
		if (!inputfile.is_open()) {
			cout << "File is not opened";
		}
		else {
			while (getline(inputfile, line)) {
				string str = "";
				int n = line.length();
				for (int i = 0; i <= n; i++) {


					if (line[i] == ' ' || i == (n - 1)) {
						c[j].GetTran().push_back(stof(str + line[i]));
						str = "";
					}
					else {
						str = str + line[i];
					}
				}
				j++;

			}
		}
		inputfile.close();
	}
	return c;
}
bool checking(string pass, string user, vector<customer>c) {
	bool check = false;
	
	pass = get_hash(pass);
	int n = c.size();
	for (int i = 0; i < n; i++) {
		if (pass == c[i].GetPassword() && user == c[i].GetUSER()) {
			check = true;
		}
	}
	return check;
}
customer Getcus(vector<customer> c,string user) {
	int n = c.size();
	customer c1;
	for (int i = 0; i < n; i++) {
		if (c[i].GetUSER() == user) {
			c1 = c[i];
			break;
		}
	}
	return c1;
}


vector<customer> Readtextfile(vector<customer> c) {
	ifstream inFile;
	string c1, line;
	ofstream outFile("");
	
	int i = 1;
	
	customer cus = customer();
	
	inFile.open("CusInfo.txt");
	if (!inFile.is_open()) {
		cout << "File is not opened";
	}
	else {
		while (!inFile.eof()) {
			
			
				inFile >> c1;
				
				if (i % 11 == 1) {
					cus.SetId(stoi(c1));
					
				}
				else if (i % 11 == 2) {
					cus.Setuser(Decrypt(c1));
				}
				else if (i % 11 == 3) {
					cus.SetPASS(c1);
				}
				else if (i % 11 == 4) {
					cus.Setname(Decrypt(c1));
				}
				else if (i % 11 == 5) {
					cus.SetTYPE(Decrypt(c1));
				}
				else if (i % 11 == 6) {
					cus.SetORG(Decrypt(c1));
				}
				else if (i % 11 == 7) {
					cus.SetDob(Decrypt(c1));
				}
				else if (i % 11 == 8) {
					cus.Setssn(Decrypt(c1));
				}
				else if (i % 11 == 9) {
					cus.SetDoj(Decrypt(c1));
				}
				else if (i % 11 == 10) {
					cus.SetWarning(stoi(c1));
					
				}
				else if (i % 11 == 0) {
					cus.SetBalance(stoi(c1));
					cus.SetStatus("Active");
					c.push_back(cus);
					cus = customer();
				}
				i++;
			
			
		}
		
	}
	inFile.close();
	return c;
}
vector<customer> ReadMessages(vector<customer> c) {
	if (!c.empty()) {
		ifstream inputfile;
		string line;
		int j = 0;
		inputfile.open("Messages.txt");
		if (!inputfile.is_open()) {
			cout << "File is not opened";
		}
		else {
			while (getline(inputfile, line)) {
				string str = "";
				int n = line.length();
				for (int i = 0; i <= n; i++) {


					if (line[i] == ' ' || i == (n - 1)) {
						c[j].GetMess().push_back(str + line[i]);
						str = "";
					}
					else {
						str = str + line[i];
					}
				}
				j++;

			}
		}
		inputfile.close();

	}
	return c;
}
void WriteTransaction(vector<customer> c) {
	if (!c.empty()) {
		int n = c.size();
		ofstream file1;
		file1.open("Transaction.txt");
		if (!file1.is_open()) {
			cout << "File is not opened";
		}
		for (int i = 0; i < n; i++) {
			int x = c[i].GetTran().size();
			for (int j = 0; j < x; j++) {
				file1 << c[i].GetTran()[j] << " ";
			}
			file1 << "\n";
		}
		file1.close();

	}
}
void WriteMessages(vector<customer> c) {
	if (!c.empty()) {
		int n = c.size();
		ofstream file1;
		file1.open("Messages.txt");
		if (!file1.is_open()) {
			cout << "File is not opened";
		}
		for (int i = 0; i < n; i++) {
			int x = c[i].GetMess().size();
			
			vector<string> mes = c[i].GetMess();
			
			for (int j = 0; j < x; j++) {
				file1 << mes[j] << " ";
			}
			file1 << "\n";
		}
		file1.close();
	}
}
int CheckId(vector<customer> c) {
	int k = 0;
	if (c.empty()) {
		return k;
	}
	else {
		int n = c.size();


		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n; i++) {
				if (c[i].GetID() == k) {
					k++;
				}
			}
			if (k == c.size() - 1) {
				break;
			}


		}
		return k;
	}
}
bool CheckId(vector<customer> c, int k) {
	bool check = true;;
	int n = c.size();
	for (int i = 0; i < n; i++) {
		if (c[i].GetID() == k) {
			check = false;
		}
	}
	return check;
}
void CustomerSignUp() {
	int i = 0;
	std::string user, pass, name, type, Org, Dob, SSN, pass2, Doj;
	std::cout << "Enter Username " << endl;
	cin >> user;
	if (!Cus.empty()) {
		while (CheckUser_exist(user,Cus)) {
			cout << "User Exist Choose Differnt User";
			cin >> user;
		}
	}
	std::cout << "Enter Password " << endl;
	cin >> pass;
	std::cout << "Enter name " << endl;
	cin.ignore();
	getline(cin, name);
	std::cout << "Enter account type(B/P) " << endl;
	cin >> type;
	std::cout << "Enter organization " << endl;
	cin.ignore();
	getline(cin, Org);
	std::cout << "Enter Date Of Birth " << endl;
	cin >> Dob;
	std::cout << "Enter SSN " << endl;
	cin >> SSN;
	std::cout << "Enter Doj(y/n) " << endl;
	cin >> Doj;
	std::cout << "Password confirmation " << endl;
	cin >> pass2;
	while (pass != pass2) {
		std::cout << "passwords don't match please enter pass word again ";
		std::cin >> pass2;
	}
	int k = CheckId(Cus);
	
	pass = get_hash(pass);
	customer c1 = customer();
	
	c1.SetId(k);
	c1.SetPASS(pass);
	c1.Setuser(user);
	c1.Setname(name);
	c1.SetTYPE(type);
	c1.SetStatus("Active");
	c1.Setssn(SSN);
	c1.SetDoj(Doj);
	c1.setDOB(Dob);
	c1.SetORG(Org);
	cout << "Welcome" << endl;
	std::cout << "your bank ID is: " << k << endl;
	float d;
	std::cout << "Please make initial deposit: ";
	std::cin >> d;
	c1.deposit(d);
	Cus.push_back(c1);	
}
void CustomerFun(customer c) {
	int k = 0;
	if (c.GetStatus() == "Active") {
		while (k != 7) {
			std::cout << " ************WelcometoC++ProgrammersBank*********************" << endl;
			std::cout << "1. Statement summary last N transaction: " << endl;
			std::cout << "2. Current Balance: " << endl;
			std::cout << "3. Withdraw: " << endl;
			std::cout << "4. Deposit:" << endl;
			std::cout << "5. Tranfer to other CID: " << endl;
			std::cout << "6. Check Inbox: " << endl;
			std::cout << "7. logout: " << endl;
			std::cin >> k;

			if (k == 1) {
				int n;
				std::cout << "enter your desire last transactions: ";
				std::cin >> n;
				c.LastTran(n);
			}
			if (k == 2) {
				c.curBalance();
			}
			if (k == 3) {
				float n;
				std::cout << "enter your desire withdrawl: ";
				std::cin >> n;
				c.withdraw(n);
			}
			if (k == 4) {
				float n;
				std::cout << "enter your desire withdrawl: ";
				std::cin >> n;
				c.deposit(n);
			}
			if (k == 5) {
				int n;
				std::cout << "enter your desire new id: ";
				std::cin >> n;
				while (!CheckId(Cus, n)) {
					std::cout << "This ID is taken please choose another one: ";
					std::cin >> n;
				}
				c.SetId(n);
			}
			if (k == 6) {
				c.ShowMessages();
			}
		}
	}
	else {
		std::cout << "This account in blocked";
	}
}
void AdminFun(admin ad) {
	int k = 0;
	int n = Cus.size();
	while (k != 7) {
		std::cout << " ************WelcometoC++ProgrammersBank*********************" << endl;
		std::cout << "1. Pay Monthly Interest: " << endl;
		std::cout << "2. Check Acount with -ve balance: " << endl;
		std::cout << "3. Check Acount with +ve balance: " << endl;
		std::cout << "4. Warning messages to -ve balance accounts:" << endl;
		std::cout << "5. Block acounts: " << endl;
		std::cout << "6. Summary Report: " << endl;
		std::cout << "7. logout: " << endl;
		std::cin >> k;
		if (k == 1) {
			ad.PayMonthlyInterest(Cus);
		}
		if (k == 2) {
			ad.CheckNegative(Cus,n);
		}
		if (k == 3) {
			ad.CheckPositive(Cus,n);
		}
		if (k == 4) {
			ad.SendWarning(Cus,n);
		}
		if (k == 5) {
			ad.BlockAcount(Cus);
		}
		if (k == 6) {
			ad.SummaryReport(Cus);
		}
	}
}
void Cuslogin(vector<customer> c) {
	string user, pass;
	int n = c.size();
	cout << "Enter Username: " << endl; cin >> user;
	cout << "Enter Password: " << endl; cin >> pass;
	bool check = checking(pass, user, c);
	while (check == false && user != "b") {
		cout << "Invalid User or Password to exit enter b \n";
		cout << "Enter Username: " << endl; cin >> user;
		cout << "Enter Password: " << endl; cin >> pass;
	}
	if (check == true) {
		CustomerFun(Getcus(c, user));
	}
}
int main() {
	int i = 0;
	admin r = CreateAdmin();
	Cus = Readtextfile(Cus);
	Cus = ReadTransaction(Cus);
	Cus = ReadMessages(Cus);
	while (i != 4) {
		std::cout << " ************WelcometoC++ProgrammersBank*********************" << endl;
		std::cout << "1. Admin sign in" << endl;
		std::cout << "2. Costumer sign in page" << endl;
		std::cout << "3. CustomerSignUppage:" << endl;
		std::cout << "4. Exit application" << endl;
		std::cin >> i;
		if(i==1){
			string pass, user;
			cout << "Enter User name: ";
			cin >> user;
			cout << "Enter password: ";
			cin >> pass;
			if (r.getPass() == pass && r.getUsername() == user) {
				AdminFun(r);
			}
			else {
				cout << "Wrong Password";
			}
		}
		else if (i==2){
			Cuslogin(Cus);
		}
		else if (i==3){
			CustomerSignUp();
		}
		
	}
	WriteCus(Cus);
	WriteTransaction(Cus);
	WriteMessages(Cus);
}