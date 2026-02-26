#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class User {
private:
	int id = 0; 
	string user, name, organization, status, dob, doj, pass,ssn;
public:
	void setID(int ID) {
		id = ID;
	}
	void setSSN(string SSN) {
		ssn = SSN;
	}
	void setUsername(string Username) {
		user = Username;
	}
	void setName(string Name) {
		name = Name;
	}
	void setOrganization(string Organization) {
		organization = Organization;
	}
	void setStatus(string Status) {
		status = Status;
	}
	void setDOB(string DOB) {
		dob = DOB;
	}
	void setDOJ(string DOJ) {
		doj = DOJ;
	}
	void setPass(string Pass) {
		pass = Pass;
	}
	int getCID() {
		return id;
	}
	string getSSN() {
		return ssn;
	}
	string getUsername() {
		return user;
	}
	string getName() {
		return name;
	}
	string getOrganization() {
		return organization;
	}
	string getStatus() {
		return status;
	}
	string getDOB() {
		return dob;
	}
	string getDOJ() {
		return doj;
	}
	string getPass() {
		return pass;
	}
	User() {}
	User(int ID, string SSN, string Username, string Name, string Organiztion, string DOB, string DOJ, string Pass) {
		id =ID;
		ssn =SSN;
		user = Username;
		name = Name;
		organization = Organiztion;
		status = "Active";
		dob = DOB;
		doj = DOJ;
		pass = Pass;
	}
};
class customer : public User {
private:
	string type;
	vector<string> messages;
	vector<float> transactions;
	double balance=0;
	int warning = 0;
public:
	customer(string ty) {
		
		type =ty;
		
		messages.push_back("Welcome");
	}
	void SetWarning(int num) {
		warning = num;
	}
	int GetWarning() {
		return warning;
	}
	void SetPASS(string str) {
		setPass(str);
	}
	void Setuser(string str) {
		setUsername(str);
	}
	void Setname(string str) {
		setName(str);
	}
	void SetTYPE(string str) {
		type = str;
	}
	void SetORG(string str) {
		setOrganization(str);
	}
	void SetDob(string str) {
		setDOB(str);
	}
	void SetDoj(string str) {
		setDOJ(str);
	}
	void Setssn(string str) {
		setSSN(str);
	}
	vector<float> GetTran() {
		return transactions;
	}
	vector<string> GetMess() {
		return messages;
	}
	void PushMessege(string str) {
		messages.push_back(str);
	}
	void SetType(string str) {
		type = str;
	}
	void SetBalance(double num) {
		balance = num;
	}
	double GetBalance() {
		return balance;
	}
	string GetStatus() {
		return getStatus();
	}
	void SetId(int id) {
		setID(id);
	}
	void SetStatus(string str) {
		setStatus(str);
	}
	customer(){
		messages.push_back("Welcome");
	}
	
	int GetID() {
		return getCID();
	}
	string GetSsn() {
		return getSSN();
	}
	string GetUSER() {
		return getUsername();
	}
	string GetNAME() {
		return getName();
	}
	string GetType() {
		return type;
	}
	string GetORG() {
		return getOrganization();
	}
	string GetDob() {
		return getDOB();
	}
	string GetDoj() {
		return getDOJ();
	}
	string GetPassword() {
		return getPass();
	}
	void deposit(float num) {
		SetBalance(GetBalance()+num);
		int n = transactions.size();
		if (!transactions.empty()) {
			n = n - 1;
			transactions.push_back(transactions[n] + num);
		}
		else {
			transactions.push_back(num);
		}
		messages.push_back(to_string(num) + "D");
	}
	void withdraw(float num) {
		SetBalance(GetBalance() - num);
		int n = transactions.size();
		transactions.push_back(transactions[n - 1] - num);
		messages.push_back(to_string(num) + "W");
	}
	void ShowMessages() {
		int n = messages.size();
		for (int i = 0; i < n; i++) {
			cout << messages[i] << endl;
		}
	}
	void curBalance() {
		cout << "Balance: " << balance << endl;
	}
	void LastTran(int N) {
		int n = transactions.size();

		if (N < n) {
			n = n - 1;
			float tran;
			std::cout << "Last " << N << " Transactions:" << endl;
			int temp = transactions[n];
			for (int i = n - 1; i >= n - N; i--) {
				tran = temp - transactions[i];
				temp = transactions[i];
				std::cout << tran << endl;
			}
		}
		else {

			cout << "too many transaction you only had: " << n - 1 << " transactions" << endl;
		}
	}

};
class admin : public User {
	string rank;
public:
	void SetRank(string str) {
		rank = str;
	}
	admin() {};
	admin(string r) {
		rank = r;
	}
	void CheckNegative(vector<customer> c, int n) {
		for (int i = 0; i < n; i++) {
			//check if tran balance is smaller than 0



			if (c[i].GetBalance() < 0)
			{
				//print username and balance of negative accounts
				cout << "Username: " << c[i].GetUSER() << " Balance: " << c[i].GetBalance() << endl;
			}
		}
	}
	void CheckPositive(vector<customer> c, int n) {
		for (int i = 0; i < n; i++) {
			//check if tran balance is smaller than 0



			if (c[i].GetBalance() > 0)
			{
				//print username and balance of negative accounts
				cout << "Username: " << c[i].GetUSER() << " Balance: " << c[i].GetBalance() << endl;
			}
		}
	}
	void SendWarning(vector<customer> c, int n) {
		for (int i = 0; i < n; i++) {
			if (c[i].GetBalance() < 0) {
				c[i].PushMessege("Warning");
				c[i].SetWarning(c[i].GetWarning() + 1);
			}
			else {
				c[i].SetWarning(0);
			}
		}
	}
	void PayMonthlyInterest(vector<customer> c) {
		float total = 0;
		float temp;
		int n = c.size();
		for (int i = 0; i < n; i++) {
			int num = c[i].GetTran().size();

			num = num - 1;
			if (num != -1) {
				total = total + c[i].GetTran()[num];
			}
		}
		for (int i = 0; i < n; i++) {
			int num1 = c[i].GetTran().size();

			num1 = num1 - 1;
			if (n != -1) {
				if (c[i].GetBalance() > 0) {
					temp = (total * 5) / 100;
					c[i].GetTran().push_back(temp + c[i].GetTran()[num1]);
					c[i].GetMess().push_back(to_string(temp) + "interest-pay");
					c[i].SetBalance(c[1].GetBalance() + temp);
				}
			}
			
		}

	}
	void BlockAcount(vector<customer> c) {
		int n = c.size();
		for (int i = 0; i < n; i++) {
			if (c[i].GetWarning() > 1) {
				c[i].SetStatus("InActive");
			}
		}
	}
	void SummaryReport(vector<customer> c) {
		int tot = c.size();
		int pos = 0;
		int neg = 0;
		int active = 0;
		int inactive = 0;
		for (int i = 0; i < tot; i++) {
			
				if (c[i].GetStatus() == "Active") {
					active++;
				}
				else {
					inactive++;
				}
			 
				if (c[i].GetBalance() > 0) {
					pos++;
				}
				else if (c[i].GetBalance() < 0)
				{
					neg++;
				}
			
		}
		cout << "Total Customer: " << tot << endl;
		cout << "Total active customers: " << active << endl;
		cout << "Total inactive customer: " << inactive << endl;
		cout << "Total +ve balances: " << pos << endl;
		cout << "Total -ve balances: " << neg << endl;
	}
};