
//             * ООП  Exception *
//   Задание 1.
// Добавьте в класс двусвязного списка механизм обработки 
// исключений. На ваш выбор генерируйте исключения в случае
// ошибок. Например, нехватка памяти, попытка удаления из 
// пустого списка и т.д.
//


#include <iostream>
#include <string>

using namespace std;


struct Node
{
	int data;                //переменная для хранения инф.
	Node* next;              //указатель на следующий элемент
	Node* prev;              //указатель на предыдущий элемент
};

class Two_list
{
	Node* head;              //указатель на голову
	Node* tail;              //указатель на хвост  
	int count;               //количество элементов списка
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

	//удаление всего списка
	void DelAll()
	{
		while (head != 0)
			Del(1);              
	}
	//удаление элемента
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
		//ищем элемент для удаления
		int i = 1;
		Node* elem = head;
		while (i < pos)
		{
			elem = elem->next;
			i++;
		}
		Node* prev_elem = elem->prev;
		Node* next_elem = elem->next;
		//если удаляем не голову
		if (prev_elem != 0 && count != 1)
			prev_elem->next = next_elem;
		//если удаляем не хвост
		if (next_elem != 0 && count != 1)
			next_elem->prev = prev_elem;
		//удаляются крайние?
		if (pos == 1)
			head = next_elem;
		if (pos == count)
			tail = prev_elem;
		//удаление элемента
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
	//вставка
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
		if (pos == count + 1)  //вставка в конец списка
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
		//находим элемент перед которым вставляемся
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
		// настройка связей
		if (prevIns != 0 && count != 0)
			prevIns->next = temp;
		 
		temp->next = Ins;
		temp->prev = prevIns;
		Ins->prev = temp;

		count++;
		
	}
	//добавление в начало списка
	void Addhead(int data)
	{
		Node* temp = new Node;
		temp->prev = nullptr;
		temp->data = data;
		temp->next = head;
		// если элементы есть?
		if (head != 0)
			head->prev = temp;
		//если элемент первый, то он и колова и хвост
		if (count == 0)
			head = tail = temp;
		else
			head = temp;
		count++;

	}
	//добавление в конец списка
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
			//отчет с головы
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
			//отчет с хвоста
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
	//оператор копирований                             //?
	Two_list& operator = (const Two_list& L)
	{
		//проверка присваивания элемента "самому себе"
		if (this == &L)
			return *this;
		//удаление старого списка
		this-> ~Two_list();   //DelAll();

		Node* temp = L.head;
		//копируем элементы
		while (temp != 0)
		{
			Addtail(temp->data);
			temp = temp->next;
		}
		return *this;
	}
	//сложение двух списков
	Two_list operator + (const Two_list& L)
	{
		//Заносим во временный список элементы первого списка
		Two_list Result(*this); //Two_list Result = *this;
		Node* temp = L.head;
		//добавляем во временный список элементы второго списка
		while (temp != 0)
		{
			Result.Addtail(temp->data);
			temp = temp->next;
		}
		return Result;

	}
	bool operator == (const Two_list& L)
	{
		//Сравниваем по количеству
		if (count != L.count)
			return false;
		Node* t1, * t2;
		t1 = head;
		t2 = L.head;
		//Сравнение по содержанию
		while (t1 != 0)
		{
			//сверяем данные, которые находятся на одинаковых позициях
			if (t1->data != t2->data)
				return false;
			t1 = t1->next;
			t2 = t2->next;
		}
		return true;
	}
	bool operator != (const Two_list& L)
	{
		//используем предыдущию функцию сравнения
		return !(*this == L);
	}
	bool operator >= (const Two_list& L)
	{
		//сравниваем по количеству
		if (count > L.count)
			return true;
		//сравнение по содержанию
		if (*this == L)
			return true;

		return false;
	}
	bool operator <= (const Two_list& L)
	{
		//сравниваем по количеству
		if (count < L.count)
			return true;
		//сравнение по содержанию
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
	//переворачивание списка
	Two_list operator - ()
	{
		Two_list Result;
		Node* temp = head;
		// копируем элементы списка, начиная с головного, в свой путем 
		// добавления элементов в голову, таким образом временный список 
		// Result будет содержать элементы в обратном порядке 
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
	//добавление четных индексов в голову, нечетных в хвост
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
			L.Addhead(a[i]);
		else
			L.Addtail(a[i]);
	}
	//вывод
	cout << " Two_list: " << endl;
	L.print();
	cout << endl;

	//вставка элемента в список
	L.Insert();
	cout << " Two_list: " << endl;
	L.print();
	cout << endl;

	// вывод 2-го и 8-го элементов
	L.print(2);
	L.print(8);
	cout << endl;

	//копируем список
	Two_list L2;
	L2 = L;
	cout << " Two_list L2: " << endl;
	L2.print();
	cout << endl;

	////складываем два списка
	////(первый в перевернутом состоянии)
	//cout << " Two_list Sum: " << endl;
	//Two_list Sum = - L + L2;
	//Sum.print();
	//cout << endl;

	//удаление элемента
	cout << " удаление элемента" << endl;
	try {
		L.Del();
		L.print();
		cout << endl;
		//L.print(0);
		Two_list L3; //пустой 
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
















