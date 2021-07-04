#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

typedef struct
{
	int year = 0;
	int month = 0;
	int day = 0;
}Date;

class linkedlist;

class listnode {
private:
	string ID;
	int Substraction = 0;
	//int Substraction[3] = {};
	Date InDay, OutDay;
	string ICD;
	listnode* next;
public:
	listnode() : next(0) {};
	listnode(string id, Date in, Date out, string a, int sub) :ID(id), next(0) {
		InDay = in;
		OutDay = out;
		Substraction = sub;
		ICD = a;
	}
	void clear() {
		ID = { "" };
		Date d;
		InDay = d, OutDay = d;
		listnode* next = 0;
		Substraction = 0;
		ICD = "";
	}
	void setID(string i) {
		ID = i;
	}
	string getID() {
		return ID;
	}
	void setSubstraction(int sub) {
		Substraction = sub;
	}
	/*void setSubstraction(int i,int sub) {
		Substraction[i] = sub;
	}*/
	int getSubstraction() {
		return Substraction;
	}
	/*int* getSubstraction() {
		return Substraction;
	}*/
	void setInDay(Date in) {
		InDay = in;
	}
	Date getInDay() {
		return InDay;
	}
	/*Date* getInDay() {
		return InDay;
	}*/
	void setOutDay(Date out) {
		OutDay = out;
	}
	Date getOutDay() {
		return OutDay;
	}
	/*Date* getOutDay() {
		return OutDay;
	}*/
	void setICD(string icd) {
		ICD = icd;
	}
	string getICD() {
		return ICD;
	}
	bool equal(const listnode& right)const {
		if ((right.ID == this->ID) && (right.ICD == this->ICD) && (right.Substraction == this->Substraction)) {
			if ((right.InDay.year == this->InDay.year) && (right.InDay.month == this->InDay.month) && (right.InDay.day == this->InDay.day))return true;
			return false;
		}
		return false;
	}
	friend class linkedlist;
	friend int sub(Date, Date);
};
int sub(Date b, Date a) {//a-b 後減前
	int amark = 0, bmark = 0;//判斷是否為閏年
	int da = 0, db = 0;//day-a day-b
	int mon[12] = { 0 , 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
	if ((a.year % 4 == 0) && (a.year % 100 != 0) || a.year % 400 == 0) amark = 1;
	if ((b.year % 4 == 0) && (b.year % 100 != 0) || b.year % 400 == 0)bmark = 1;

	if (a.year == b.year) {
		if (a.month > 2)da = mon[a.month - 1] + amark + a.day;
		else da = mon[a.month - 1] + a.day;
		if (b.month > 2)db = mon[b.month - 1] + bmark + b.day;
		else db = mon[b.month - 1] + b.day;
		return da - db + 1;
	}//如果同一年
	else if (a.year > b.year) {
		int d = a.year - b.year;
		int dy = 0;//相差的年變成日
		for (; d > 0; d--) {
			if (((b.year + (d - 1)) % 4 == 0) && ((b.year + (d - 1)) % 100 != 0) || (b.year + (d - 1)) % 400 == 0)dy += 366;
			else dy += 365;
		}
		if (a.month > 2)da = mon[a.month - 1] + amark + a.day;
		else da = mon[a.month - 1] + a.day;
		if (b.month > 2)db = mon[b.month - 1] + bmark + b.day;
		else db = mon[b.month - 1] + b.day;
		return da - db + dy + 1;
	}//如果不同年

}

class linkedlist {
private:
	int size=0;
	listnode* first=0;
public:
	linkedlist() :size(0), first(0) {};
	int getSize() {
		return size;
	}
	void sort() {
		if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
			cout << "List is empty.\nCouldn't sort.\n";
			return;
		}
		listnode* current = first, * previous = 0, * temp = 0;
		int i = this->size;
		while (i != 0) {
			while (current->next != 0) {
				if ((current->getID() > current->next->getID())||((current->getID() == current->next->getID())&&(current->getICD()>current->next->getICD()))) {
					if (current == first) {
						first = current->next;
						temp = first->next;
						first->next = current;
						current = current->next;
						current->next->next = temp;
					}
					else {
						temp = current;
						current = current->next;
						previous->next = current;
						temp->next = current->next;
						current->next = temp;
					}
				}
				previous = current;
				current = current->next;
				
			}//找ID最小的
			current = first, previous = 0, temp = 0;
			i--;
		}
		delete temp;
		temp = 0;
	}
	void PrintList() {
		if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
			cout << "List is empty.\n";
			return;
		}
		listnode* current = first;             // 用pointer *current在list中移動
		while (current != 0) {                 // Traversal
			cout << current->getID() << "," << current->getICD() << "," << current->getSubstraction() << endl;
			current = current->next;
		}
	} // 印出list的所有資料
	void Push_front(string id, Date in, Date out, string a, int sub) {
		++size;
		listnode* newNode = new listnode(id, in, out, a, sub);   // 配置新的記憶體
		newNode->next = first;                 // 先把first接在newNode後面
		first = newNode;               // 再把first指向newNode所指向的記憶體位置
	}// 在list的開頭新增node
	void Push_back(string id, Date in, Date out, string a, int sub) {
		++size;
		listnode* newNode = new listnode(id, in, out, a, sub);   // 配置新的記憶體

		if (first == 0) {                      // 若list沒有node, 令newNode為first
			first = newNode;
			return;
		}

		listnode* current = first;
		while (current->next != 0) {  // Traversal
			current = current->next;
		}
		current->next = newNode;  // 將newNode接在list的尾巴
	}// 在list的尾巴新增node
	void Clear() {
		size = 0;
		while (first != 0) {            // Traversal
			listnode* current = first;
			first = first->next;
			delete current;
			current = 0;
		}
	} // 把整串list刪除
	void Delete(listnode x) {

		listnode* current = first, * previous = 0;
		while (current != 0 && !(current->equal(x))) {  // Traversal
			previous = current;                       // 如果current指向NULL
			current = current->next;                  // 或是current->data == x
		}                                             // 即結束while loop

		if (current == 0) {                 // list沒有要刪的node, 或是list為empty
			std::cout << "There is no this node in list.\n";
			// return;
		}
		else if (current == first) {        // 要刪除的node剛好在list的開頭
			first = current->next;          // 把first移到下一個node
			delete current;                 // 如果list只有一個node, 那麼first就會指向NULL
			current = 0;     //  當指標被delete後, 將其指向NULL, 可以避免不必要bug
			size--; 
			// return;                     
		}
		else {                              // 其餘情況, list中有欲刪除的node, 
			previous->next = current->next; // 而且node不為first, 此時previous不為NULL
			delete current;
			current = 0;
			size--;
			// return;
		}
	}
	void DealWith() {
		if (first == 0) {                      // 如果first node指向NULL, 表示list沒有資料
			cout << "List is empty.\nCouldn't deal with it.\n";
			return;
		}
		listnode* current = first, * previous = 0, * temp = 0;
		int i = this->size;
		while (i > 0) {
			while (current!=0&&current->next!= 0&&first->next!=0) {
				if ((current->getID() == current->next->getID()) && (current->getICD() == current->next->getICD())) {
					//重疊(包含於/交錯)
					if ((sub(current->getInDay(), current->next->getInDay()) > 0) && (sub(current->next->getOutDay(), current->getOutDay()) > 0)) {
						current->setSubstraction(sub(current->getInDay(), current->getOutDay()));
						this->Delete(*current->next);
					}//current包含current->next的日期
					else if ((sub(current->next->getInDay(), current->getInDay()) > 0) && (sub(current->getOutDay(), current->next->getOutDay()) > 0)) {
						if (current == first) {
							first = current->next;
							temp = first->next;
							first->next = current;
							current->next = temp;
							current = first;
						}
						else {
							temp = current;
							current = current->next;
							previous->next = current;
							temp->next = current->next;
							current->next = temp;//current current->next swap
						}
						current->setSubstraction(sub(current->getInDay(), current->getOutDay()));
						this->Delete(*current->next);
					}//current->next包含current的日期
					else if ((sub(current->next->getInDay(), current->getOutDay()) > 0) && (sub(current->getInDay(), current->next->getInDay()) > 0)) {
						current->setOutDay(current->next->getOutDay());
						current->setSubstraction(sub(current->getInDay(), current->getOutDay()));
						this->Delete(*current->next);
					}//p1 p2交錯 取p1 in~p2 out
					else if ((sub(current->getInDay(), current->next->getOutDay()) > 0) && (sub(current->next->getInDay(), current->getInDay()) > 0)) {
						current->setInDay(current->next->getInDay());
						current->setSubstraction(sub(current->getInDay(), current->getOutDay()));
						this->Delete(*current->next);
					}//p2 p1交錯 取p2 in~p1 out
				}
				previous = current;
				current = current->next;
			}
			current = first;
			previous = 0;
			i--;
		}
		 i = this->size;
		 while (i > 0) {
			 while (current != 0 && current->next != 0 && first->next != 0) {
				 if ((current->getID() == current->next->getID()) && (current->getICD() == current->next->getICD())) {
					 //分開
					 if ((sub(current->getOutDay(), current->next->getInDay()) > 0) || (sub(current->next->getOutDay(), current->getInDay()) > 0)) {
						 current->setSubstraction(current->getSubstraction() + current->next->getSubstraction());
						 this->Delete(*current->next);
					 }//分開就加起來
				 }
				 previous = current;
				 current = current->next;
			 }
			 current = first;
			 previous = 0;
			 i--;
		 }
	}
};

int main(int argc, char* argv[]) {
	linkedlist list;
	vector<listnode> temp;
	listnode node;
	ifstream fin;
	fin.open(argv[1]/*"123.txt"*/);
	string data, data1, data2;
	stringstream ss, ss1;
	Date d;
	int  j = 0, k = 0, z = 0;
	int x = 0, i = 0, value = 0;
	while (getline(fin, data)) {
		ss.str("");
		ss.clear();
		ss << data;
		while (getline(ss, data1, ',')) {
			ss1.str("");
			ss1.clear();
			if (x == 0) {
				node.setID(data1);
			}
			else if (x == 1) {
				data2 = data1.substr(0, 4);
				ss1 << data2;
				ss1 >> d.year;
				data2 = data1.substr(4, 2);
				ss1.str("");
				ss1.clear();
				ss1 << data2;
				ss1 >> d.month;
				data2 = data1.substr(6, 2);
				ss1.str("");
				ss1.clear();
				ss1 << data2;
				ss1 >> d.day;
				node.setInDay(d);
			}
			else if (x == 2) {
				if (data1 != "") {
					data2 = data1.substr(0, 4);
					ss1 << data2;
					ss1 >> d.year;
					data2 = data1.substr(4, 2);
					ss1.str("");
					ss1.clear();
					ss1 << data2;
					ss1 >> d.month;
					data2 = data1.substr(6, 2);
					ss1.str("");
					ss1.clear();
					ss1 << data2;
					ss1 >> d.day;
					node.setOutDay(d);
				}
				else {
					if (d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month == 12) {
						d.day = 31;
					}
					else if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11)d.day = 30;
					else {
						if ((d.year % 4 == 0) && (d.year % 100 != 0) || d.year % 400 == 0) d.day = 29;
						else d.day = 28;
					}
					node.setOutDay(d);
				}
			}
			else if (x == 3) {
				if (data1 != "") {
					node.setICD(data1);
					temp.push_back(node);
				}
			}
			else if (x == 4) {
				if (data1 != "") {
					node.setICD(data1);
					temp.push_back(node);
				}
			}
			else if (x == 5) {
				if (data1 != "") {
					node.setICD(data1);
					temp.push_back(node);
				}
			}
			x++;
		}
		for (i = 0; i < temp.size(); i++) {
			temp[i].setSubstraction(sub(temp[i].getInDay(), temp[i].getOutDay()));
			list.Push_back(temp[i].getID(), temp[i].getInDay(), temp[i].getOutDay(), temp[i].getICD(), temp[i].getSubstraction());
		}//先把檔案都放進list
		x = 0;
		node.clear();
		temp.clear();
	}
	list.sort();//由小到大排序
	list.DealWith();

	list.PrintList();
	list.Clear();
	return 0;
}