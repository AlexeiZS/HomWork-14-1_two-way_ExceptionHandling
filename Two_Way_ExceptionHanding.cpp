
//             * ���  Exception *
//   ������� 1.
// �������� � ����� ����������� ������ �������� ��������� 
// ����������. �� ��� ����� ����������� ���������� � ������
// ������. ��������, �������� ������, ������� �������� �� 
// ������� ������ � �.�.
//


#include <iostream>
#include <string>

using namespace std;


struct Node
{
	int data;                //���������� ��� �������� ���.
	Node* next;              //��������� �� ��������� �������
	Node* prev;              //��������� �� ���������� �������
};

class Two_list
{
	Node* head;              //��������� �� ������
	Node* tail;              //��������� �� �����  
	int count;               //���������� ��������� ������
public:
	Two_list()
	{
		head = tail = nullptr;
		count = 0;
	}
	//ctor - copy
	Two_list(const Two_list& L)
	{
		head = tail = nullptr;
		count = 0;
		Node* temp = L.head;
		while (temp != 0)
		{
			Addtail(temp->data);
			temp = temp->next;
		}
	}
	//dtor
	~Two_list() 
	{
		DelAll();
	}

	//�������� ����� ������
	void DelAll()
	{
		while (head != 0)
			Del(1);              
	}
	//�������� ��������
	void Del(int pos = 0)
	{
		if (count == 0) {

			throw" \n The list is empty!\n";
		}
		if (pos == 0)
		{
			cout << " Input position: ";
			cin >> pos;
		}
		if (pos < 1 || pos > count)
		{
			throw" \n Incorrect position!\n";
		}
		//���� ������� ��� ��������
		int i = 1;
		Node* elem = head;
		while (i < pos)
		{
			elem = elem->next;
			i++;
		}
		Node* prev_elem = elem->prev;
		Node* next_elem = elem->next;
		//���� ������� �� ������
		if (prev_elem != 0 && count != 1)
			prev_elem->next = next_elem;
		//���� ������� �� �����
		if (next_elem != 0 && count != 1)
			next_elem->prev = prev_elem;
		//��������� �������?
		if (pos == 1)
			head = next_elem;
		if (pos == count)
			tail = prev_elem;
		//�������� ��������
		delete elem;
		count--;


	}

	Node* getElem(int pos)
	{
		Node* temp = head;
		if (pos<1 || pos>count)
		{
			throw "\n Incorrect position!\n";
			
		}
		int i = 1;
		while(i < pos&& temp != 0)
		{
			temp = temp->next;
			i++;
		}
		if (temp == 0)
			return 0;
		else
			return temp;
	}

	int getcount()
	{
		return count;
	}
	//�������
	void Insert(int pos = 0)
	{
		if (pos == 0)
		{
			cout << " Input position: ";
			cin >> pos;
		}
		if (pos<1 || pos>count + 1)
		{
			cout << " Incorrect posinion!" << endl;
			return;
		}
		if (pos == count + 1)  //������� � ����� ������
		{
			int data;
			cout << " Input new number: ";
			cin >> data;
			Addtail(data);
			return;
		}
		else if (pos == 1)    
		{
			int data;
			cout << " Input new number: ";
			cin >> data;
			Addhead(data);
			return;
		}
		//������� ������� ����� ������� �����������
		int i = 1;
		Node* Ins = head;
		while (i < pos)
		{
			Ins = Ins->next;
			i++;
		}
		Node* prevIns = Ins->prev;
		Node* temp = new Node;
		cout << " Input new number: ";
		cin >> temp->data;
		// ��������� ������
		if (prevIns != 0 && count != 0)
			prevIns->next = temp;
		 
		temp->next = Ins;
		temp->prev = prevIns;
		Ins->prev = temp;

		count++;
		
	}
	//���������� � ������ ������
	void Addhead(int data)
	{
		Node* temp = new Node;
		temp->prev = nullptr;
		temp->data = data;
		temp->next = head;
		// ���� �������� ����?
		if (head != 0)
			head->prev = temp;
		//���� ������� ������, �� �� � ������ � �����
		if (count == 0)
			head = tail = temp;
		else
			head = temp;
		count++;

	}
	//���������� � ����� ������
	void Addtail(int data)
	{
		Node* temp = new Node;
		temp->next = nullptr;
		temp->data = data;
		temp->prev = tail;   

		if (tail!=0)
			tail->next = temp;
		if (count == 0)
			head = tail = temp;
		else
			tail = temp;

		count++;
	}

	void print(int pos)
	{
		if (!count)
		{
			throw"\n The list is empty!";
		}
		if (pos<1 || pos>count)
		{
			throw "\n Incorrect position!\n";
		}
		Node* temp;
		if (pos <= count / 2)
		{
			//����� � ������
			temp = head;
			int i = 1;
			while (i < pos)
			{
				temp = temp->next;
				i++;
			}
		}
		else
		{
			//����� � ������
			temp = tail;
			int i = 1;
			while (i <=count - pos)
			{
				temp = temp->prev;
				i++;
			}
		}
		cout << pos << " element: " << temp->data << endl;



	}
	void print()
	{
		if (!count)
		{
			throw"\n The list is empty!";
		}
			Node* temp = head;
			cout << " ( ";
			while (temp->next != nullptr)
			{
				cout << temp->data << ", ";
				temp = temp->next;
			}
			cout << temp->data<<" )"<< endl;
	}
	//�������� �����������                             //?
	Two_list& operator = (const Two_list& L)
	{
		//�������� ������������ �������� "������ ����"
		if (this == &L)
			return *this;
		//�������� ������� ������
		this-> ~Two_list();   //DelAll();

		Node* temp = L.head;
		//�������� ��������
		while (temp != 0)
		{
			Addtail(temp->data);
			temp = temp->next;
		}
		return *this;
	}
	//�������� ���� �������
	Two_list operator + (const Two_list& L)
	{
		//������� �� ��������� ������ �������� ������� ������
		Two_list Result(*this); //Two_list Result = *this;
		Node* temp = L.head;
		//��������� �� ��������� ������ �������� ������� ������
		while (temp != 0)
		{
			Result.Addtail(temp->data);
			temp = temp->next;
		}
		return Result;

	}
	bool operator == (const Two_list& L)
	{
		//���������� �� ����������
		if (count != L.count)
			return false;
		Node* t1, * t2;
		t1 = head;
		t2 = L.head;
		//��������� �� ����������
		while (t1 != 0)
		{
			//������� ������, ������� ��������� �� ���������� ��������
			if (t1->data != t2->data)
				return false;
			t1 = t1->next;
			t2 = t2->next;
		}
		return true;
	}
	bool operator != (const Two_list& L)
	{
		//���������� ���������� ������� ���������
		return !(*this == L);
	}
	bool operator >= (const Two_list& L)
	{
		//���������� �� ����������
		if (count > L.count)
			return true;
		//��������� �� ����������
		if (*this == L)
			return true;

		return false;
	}
	bool operator <= (const Two_list& L)
	{
		//���������� �� ����������
		if (count < L.count)
			return true;
		//��������� �� ����������
		if (*this == L)
			return true;

		return false;
	}
	bool operator < (const Two_list& L)
	{
		if (count < L.count)
			return true;

		return false;
	}
	bool operator > (const Two_list& L)
	{
		if (count > L.count)
			return true;

		return false;
	}
	//��������������� ������
	Two_list operator - ()
	{
		Two_list Result;
		Node* temp = head;
		// �������� �������� ������, ������� � ���������, � ���� ����� 
		// ���������� ��������� � ������, ����� ������� ��������� ������ 
		// Result ����� ��������� �������� � �������� ������� 
		while (temp != 0)
		{
			Result.Addhead(temp->data);
			temp = temp->next;
		}
		return Result;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	
	Two_list L;
	const int n = 10;
	int a[n] = { 0,1,2,3,4,5,6,7,8,9 };
	//���������� ������ �������� � ������, �������� � �����
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			L.Addhead(a[i]);
		else
			L.Addtail(a[i]);
	}
	//�����
	cout << " Two_list: " << endl;
	L.print();
	cout << endl;

	//������� �������� � ������
	L.Insert();
	cout << " Two_list: " << endl;
	L.print();
	cout << endl;

	// ����� 2-�� � 8-�� ���������
	L.print(2);
	L.print(8);
	cout << endl;

	//�������� ������
	Two_list L2;
	L2 = L;
	cout << " Two_list L2: " << endl;
	L2.print();
	cout << endl;

	////���������� ��� ������
	////(������ � ������������ ���������)
	//cout << " Two_list Sum: " << endl;
	//Two_list Sum = - L + L2;
	//Sum.print();
	//cout << endl;

	//�������� ��������
	cout << " �������� ��������" << endl;
	try {
		L.Del();
		L.print();
		cout << endl;
		//L.print(0);
		Two_list L3; //������ 
		cout << "\n list L3: ";
		//L3.Del();
		L3.print();
		
	}
	catch (const char* exception)
	{
		cout << exception;
	}

	return 0;
}
















