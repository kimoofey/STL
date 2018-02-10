#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>

using namespace std;

template<typename Type>class LIST;
template<typename Type>class ITERATOR;
template<typename Type>class REVERSE_ITERATOR;
template<typename Type>class CONST_ITERATOR;
template<typename Type>class CONST_REVERSE_ITERATOR;

template<typename Type>
struct LIST_STRUCT
{
	Type Data;
	LIST_STRUCT<Type> *Next;
	LIST_STRUCT<Type> *Old;
};

template<class Type>
class ITERATOR
{
protected:
	LIST_STRUCT<Type> *cur_, *old_;
public:

	ITERATOR(LIST_STRUCT<Type> *new_elem, LIST_STRUCT<Type> *new_last_elem) : cur_(new_elem), old_(new_last_elem)
	{

	}
	ITERATOR() : cur_(NULL), old_(NULL)
	{

	}
	~ITERATOR()
	{

	}

	bool operator == (ITERATOR<Type> &iter)
	{
		return cur_ == iter.cur_;
	}
	void operator = (ITERATOR<Type> &iter)
	{
		cur_ = iter.cur_;
	}
	bool operator != (ITERATOR<Type> &iter)
	{
		return cur_ != iter.cur_;
	}
	bool operator > (ITERATOR<Type> &iter)
	{
		return сur_->Data > iter.сur_->Data;
	}
	bool operator >= (ITERATOR<Type> &iter)
	{
		return cur_->Data >= iter.cur_->Data;
	}
	bool operator < (ITERATOR<Type> &iter)
	{
		return cur_->Data < iter.cur_->Data;
	}
	bool operator <= (ITERATOR<Type> &iter)
	{
		return cur_->Data <= iter.cur_->Data;
	}
	void operator ++ (void)
	{
		if(cur_ != NULL)
			cur_ = cur_->Next;
	}
	void operator -- (void)
	{
		if(cur_ != NULL)
			cur_ = cur_->Old;
	}
	LIST_STRUCT<Type>* operator &(void)
	{
		return cur_;
	}
	LIST_STRUCT<Type>* operator ~(void)
	{
		return old_;
	}
	Type operator *(void)
	{
		if (cur_ == NULL)
			return 0;
		return cur_->Data;
	}
	bool is_zero(void)
	{
		return cur_ == NULL;
	}
};

template<class Type>
class REVERSE_ITERATOR :public ITERATOR<Type> {
protected:
	LIST_STRUCT<Type> *reverse_cur_, *reverse_old_;
public:
	REVERSE_ITERATOR(LIST_STRUCT<Type> *new_elem, LIST_STRUCT<Type> *new_last_elem)
	{
		reverse_cur_ = new_elem;
		reverse_old_ = new_last_elem;
	}
	REVERSE_ITERATOR()
	{
		reverse_cur_ = NULL;
		reverse_old_ = NULL;
	}
	~REVERSE_ITERATOR()
	{
	}

	Type operator *(void)
	{
		if (reverse_cur_ == NULL)
			return 0;
		return reverse_cur_->Data;
	}
	void operator ++ (void)
	{
		reverse_cur_ = reverse_cur_->Old;
	}
	void operator -- (void)
	{
		reverse_cur_ = reverse_cur_->Next;
	}
};

template<class Type>
class CONST_ITERATOR :public REVERSE_ITERATOR<Type> {
protected:
	LIST_STRUCT<Type> *const_cur_, *const_old_;
public:
	CONST_ITERATOR(LIST_STRUCT<Type> *new_elem, LIST_STRUCT<Type> *new_last_elem)
	{
		const_cur_ = new_elem;
		const_old_ = new_last_elem;
	}
	CONST_ITERATOR()
	{
		const_cur_ = NULL;
		const_old_ = NULL;
	}
	~CONST_ITERATOR()
	{
	}
	Type operator *(void)
	{
		if (const_cur_ == NULL)
			return 0;
		return const_cur_->Data;
	}
	const LIST_STRUCT<Type>* operator &(void)
	{
		return const_cur_;
	}
};

template<class Type>
class CONST_REVERSE_ITERATOR :public CONST_ITERATOR<Type> {
protected:
	LIST_STRUCT<Type> *const_reverse_cur_, *const_reverse_old_;
public:
	CONST_REVERSE_ITERATOR(LIST_STRUCT<Type> *new_elem, LIST_STRUCT<Type> *new_last_elem)
	{
		const_reverse_cur_ = new_elem;
		const_reverse_old_ = new_last_elem;
	}
	CONST_REVERSE_ITERATOR()
	{
		const_reverse_cur_ = NULL;
		const_reverse_old_ = NULL;
	}
	~CONST_REVERSE_ITERATOR()
	{
	}
	Type operator *(void)
	{
		if (const_reverse_cur_ == NULL)
			return 0;
		return const_reverse_cur_->Data;
	}
	void operator ++ (void)
	{
		const_reverse_cur_ = const_reverse_cur_->Old;
	}
	void operator -- (void)
	{
		const_reverse_cur_ = const_reverse_cur_->Next;
	}
	const LIST_STRUCT<Type>* operator &(void)
	{
		return const_reverse_cur_;
	}
};

template<class Type>
class LIST: public CONST_REVERSE_ITERATOR<Type>
{
private:
	LIST_STRUCT<Type> *Start , *Begin , *End;
	int len;

	ITERATOR<Type> current_; // текущий
	//ITERATOR<Type> end_; // конец

	REVERSE_ITERATOR<Type> reverse_current_; // реверс текущий
	//REVERSE_ITERATOR<Type> reverse_end_; // реверс конец

	CONST_ITERATOR<Type> const_current_;
	CONST_REVERSE_ITERATOR<Type>const_reverse_current_;

public:


	LIST()
	{
		Start = NULL;
		len = 0;
		Begin = new LIST_STRUCT<Type>;
		End = new LIST_STRUCT<Type>;
		Begin->Data = -1;
		End->Data = -1;
		Begin->Next = End;
		End->Old = Begin;
		End->Next = NULL;
		Begin->Old = NULL;
	}
	~LIST()
	{
		LIST_STRUCT<Type> *DELET = Begin;
		while (Start)
		{
			Start = Start->Next;
			free(DELET);
		}
	}
	LIST(LIST<Type> &new_list) {
		Start = NULL;
		len = 0;
		Begin = new LIST_STRUCT<Type>;
		End = new LIST_STRUCT<Type>;
		Begin->Data = -1;
		End->Data = -1;
		Begin->Next = End;
		End->Old = Begin;
		End->Next = NULL;
		Begin->Old = NULL;
		ITERATOR<Type> New_elem = new_list.START();
		while (New_elem.is_zero()) {
			ADD(*New_elem);
			++New_elem;
		}
	}
	void PRINT(void)
	{
		LIST_STRUCT<Type> *Find = Start;
		while (1)
		{
			if (Find == NULL)
				break;
			if (Find->Next == NULL)
				break;
			cout << Find->Data << "  " ;
			Find = Find->Next;
		}
		cout << "" << endl;
	}
	void ADD(Type new_element)
	{
		LIST_STRUCT<Type> *Find = Start, *New = NULL;
		while (1)
		{
			if (Find == NULL)
				break;
			if (Find->Data > new_element)
				break;
			if (Find->Next == NULL)
				break;
			if (Find->Next->Data == -1)
				break;
			Find = Find->Next;
		}
		New = new LIST_STRUCT<Type>;
		New->Data = new_element;
		if (Start == NULL)
		{
			Start = New;
			Start->Next = End;
			Start->Old = Begin;
			End->Old = Start;
			Begin->Next = Start;
			current_ = ITERATOR<Type>(Start , End);
			reverse_current_ = REVERSE_ITERATOR<Type>(Start, Begin);
		}
		else if (Find->Next == End && (Find->Data <= new_element))
		{
			Find->Next = New;
			New->Old = Find;
			New->Next = End;
			End->Old = New;
		}
		else if (Find->Next == End && (Find->Data > new_element))
		{
			New->Next = Find;
			New->Old = Find->Old;
			Find->Old->Next = New;
			Find->Old = New;
			if (New->Old == Begin)
				Start = New;
		}
		else if (Find->Old == Begin && (Find->Data > new_element))
		{
			Begin->Next = New;
			New->Old = Begin;
			New->Next = Find;
			Find->Old = New;
			Start = New;
		}
		else if (Find->Old == Begin && (Find->Data <= new_element))
		{
			Find->Next->Old = New;
			New->Next = Find->Next;
			Find->Next = New;
			New->Old = Find;
		}
		else if (Find->Data <= new_element)
		{
			New->Old = Find;
			New->Next = Find->Next;
			Find->Next->Old = New;
			Find->Next = New;
		}
		else if (Find->Data > new_element)
		{
			New->Old = Find->Old;
			Find->Old->Next = New;
			New->Next = Find;
			Find->Old = New;
		}
		len++;
		/*if (end_.is_zero())
		{
			LIST_STRUCT<Type> *PRE_OLD = new LIST_STRUCT<Type>, *Find = Start;
			end_ = ITERATOR<Type>();
			PRE_OLD->Data = -1;
			PRE_OLD->Next = NULL;
			while (Find->Next)
				Find = Find->Next;
			PRE_OLD->Old = Find;
			~end_ = PRE_OLD;
		}
		else
		{
			LIST_STRUCT<Type> *Find = Start;
			while (Find->Next)
				Find = Find->Next;
			end_.old_->Old = Find;
		}
		if (reverse_end_.is_zero())
		{
			LIST_STRUCT<Type> *PRE_NEW = new LIST_STRUCT<Type>, *Find = Start;
			reverse_end_ = REVERSE_ITERATOR<Type>();
			PRE_NEW->Data = -1;
			PRE_NEW->Next = Start;
			PRE_NEW->Old = NULL;
			reverse_end_.old_ = PRE_NEW;
		}
		else
			reverse_end_.old_->Next = Start;*/
	}
	//присваивание , копирование, удаление, сравнение (== , != , > , <) 
	bool Empty(void)
	{
		return Start == NULL ? true : false;
	}
	int Size(void)
	{
		return len;
	}
	void del(LIST_STRUCT<Type> *del){
		LIST_STRUCT<Type> *old_elem = del;
		if (old_elem->Data == -1)
			return;
		if (old_elem->Next == End && old_elem->Old == Begin) {
			Begin->Next = End;
			End->Old = Begin;
			Start = NULL;
		}
		else {
			old_elem->Old->Next = old_elem->Next;
			old_elem = old_elem->Old;
			old_elem->Next->Old = old_elem;
			if (del->Data == Start->Data)
				Start = old_elem->Next;
		}
		free(del);
		del = NULL;
	}
	//удаление по итератору, по диапозону
	ITERATOR<Type> del_iterator(ITERATOR<Type> iter){
		ITERATOR<Type> old = iter;
		if ((&iter)->Next->Data != -1)
			++iter;
		else if ((&iter)->Old->Data != -1)
			--iter;
		del(&old);
		return ITERATOR(&iter, End);
	}
	ITERATOR<Type> del_iterator(ITERATOR<Type> a , ITERATOR<Type> b) {
		ITERATOR<Type> old = a;
		while (1) {
			++a;
			del(&old);
			old = a;
			if (old == b) {
				del(&old);
				break;
			}
		}
		return ITERATOR(Start, End);
	}
	void operator=(LIST<Type> &second) {
		~LIST();
		LIST(second);
	}
	bool operator == (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second.START();
		while (First != End){
			if (*Second == -1)
				return false;
			else if (First->Data != *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	bool operator != (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second. START();
		while (First != End) {
			if (*Second == -1)
				return false;
			else if (First->Data == *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	bool operator > (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second.START();
		while (First != End) {
			if ( *Second == -1)
				return true;
			else if (First->Data <= *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	bool operator >= (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second.START();
		while (First != End) {
			if (*Second == -1)
				return true;
			else if (First->Data < *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	bool operator < (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second.START();
		while (First != End) {
			if (*Second == -1)
				return false;
			else if (First->Data >= *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	bool operator <= (LIST<Type> &second)
	{
		LIST_STRUCT<Type> *First = Start;
		ITERATOR<Type> Second = second.START();
		while (First != End) {
			if (*Second == -1)
				return false;
			else if (First->Data > *Second)
				return false;
			First = First->Next;
			++Second;
		}
		return true;
	}
	ITERATOR<Type> START(void) 
	{
		return ITERATOR(Start , End);
	}
	ITERATOR<Type> END(void)
	{
		return ITERATOR(End , End); // возвращает на след после последнего
	}

	CONST_ITERATOR<Type> START_CONST(void)
	{
		return CONST_ITERATOR(Start , End);
	}
	CONST_ITERATOR<Type> END_CONST(void)
	{
		return CONST_ITERATOR(End, End);
	}

	REVERSE_ITERATOR<Type> REVERSE_START(void)
	{
		return REVERSE_ITERATOR(End->Old, End);
	}
	REVERSE_ITERATOR<Type> REVERSE_END(void)
	{
		return REVERSE_ITERATOR(Begin , End);
	}

	CONST_REVERSE_ITERATOR<Type> REVERSE_START_CONST(void)
	{
		return CONST_REVERSE_ITERATOR(End->Old , End);
	}
	CONST_REVERSE_ITERATOR<Type> REVERSE_END_CONST(void)
	{
		return CONST_REVERSE_ITERATOR(Begin, End);
	}
};


int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	LIST<int> *MyList = new LIST<int>;
	LIST<int> *MyList2 = new LIST<int>;
	while (1)
	{
		int x = 0;
		cout << "Введите х: " << endl;
		cin >> x;
		if (x == 0)
			break;
		MyList->ADD(x);
		MyList->PRINT();
	}

	ITERATOR<int> Cur; //= MyList->START();
	cout << "Пуст ли список(0 - нет, заполнен ; 1 - пуст): " << MyList->Empty() << endl;
	cout << "Сколько элементов в списке: " << MyList->Size() << endl;
	
	while (1)
	{
		if (*Cur == *(MyList->END()))
			break;
		cout << *Cur << "   ";
		++Cur;
	}
	
	cout << endl << endl;
	
	REVERSE_ITERATOR<int> Reverse_Cur = MyList->REVERSE_START();
	while (1)
	{
		
		if (*Reverse_Cur == *(MyList->REVERSE_END()))
			break;
		cout << *Reverse_Cur << "   ";
		++Reverse_Cur;
	}
	cout << "" << endl;

	CONST_ITERATOR<int> CCur = MyList->START_CONST();
	
	
	while (1)
	{
		int x = 0;
		cout << "Введите х: " << endl;
		cin >> x;
		if (x == 0)
			break;
		MyList2->ADD(x);
		MyList2->PRINT();
	}
	cout << "Пуст ли список(0 - нет, заполнен ; 1 - пуст): " << MyList2->Empty() << endl;
	cout << "Сколько элементов в списке: " << MyList2->Size() << endl;
	if (MyList == MyList2)
		cout << "2 списка равны" << endl;
	else
	{
		if (MyList != MyList2)
			cout << "списки не равны" << endl;
		if (MyList > MyList2)
			cout << "первый список больше" << endl;
		if (MyList < MyList2)
			cout << "второй список больше" << endl;
	}
	
	cout << "My list 1:" << endl;
	MyList->PRINT();
	cout << "My list 2:" << endl;
	MyList2->PRINT();

	LIST<int> *MyList3 = MyList;
	cout << "My list 3:" << endl;
	MyList3->PRINT();
	MyList = MyList2;
	cout << "My list 1:" << endl;
	MyList->PRINT();

	if (MyList == MyList2)
		cout << "2 списка равны" << endl;
	else
	{
		if (MyList != MyList2)
			cout << "списки не равны" << endl;
		if (MyList > MyList2)
			cout << "первый список больше" << endl;
		if (MyList < MyList2)
			cout << "второй список больше" << endl;
	}
	ITERATOR<int> a = MyList->START() , b = MyList->START();
	
	++b;
	++b;
	++b;
	++b;
	a = MyList->del_iterator(a , b);
	
	MyList->PRINT();

	system("pause");
	return 1;
}
