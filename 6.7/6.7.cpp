#include <iostream>
using namespace std;
// інтерфейс, що описує функтори - унарні предикати
template<class T>
class Predicate
{
public:
	virtual bool operator () (T x) = 0;
};
// реалізуємо інтерфейс функтором - перевірка, чи значення дорівнює нулю
template<class T>
class Zero : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		T zero = T();
		return x == zero;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення додатне
// працює лише для числових типів
template<class T>
class Positive : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x > 0;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення від'ємне
// працює лише для числових типів
template<class T>
class Negative : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x < 0;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення парне
// працює лише для цілих типів
template<class T>
class Even : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x % 2 == 0;
	}
};
// реалізуємо інтерфейс функтором - перевірка, чи значення не парне
// працює лише для цілих типів
template<class T>
class Odd : public Predicate<T>
{
public:
	virtual bool operator () (T x)
	{
		return x % 2 != 0;
	}
};
// дублюємо всі елементи
// begin - ітератор початку вхідного контейнера (вказує на перший елемент)161
// end - ітератор кінця вхідного контейнера (вказує на елемент після останнього)
// to - ітератор початку результуючого контейнера (вказує на перший елемент)
template<class T>
int copy(T* begin, T* end, T* to)
{
	int n = 0; // n - кількість елементів у результуючому контейнері
	for (T* from = begin; from < end; from++) // from - ітератор вхідного контейнера
	{										  // вказує на поточний елемент
		*to = *from;
		to++;
		n++;
	}
	return n;
}
// дублюємо елементи, для яких предикат p набуває значення true
// begin - ітератор початку вхідного контейнера (вказує на перший елемент)
// end - ітератор кінця вхідного контейнера (вказує на елемент після останнього)
// to - ітератор початку результуючого контейнера (вказує на перший елемент)
template<class T>
int copy_if(T* begin, T* end, T* to, Predicate<T>& p)
{
	int n = 0; // n - кількість елементів у результуючому контейнері
	for (T* from = begin; from < end; from++) // from - ітератор вхідного контейнера
	{
		if (p(*from)) // якщо справджується умова предикату
		{
			*to = *from;
			to++; // то скопіювали цей елемент ще раз
			n++;
		}
	}
	return n;
}
int main()
{
	int a[5] = { 1, -2, 0, 4, -5 }; // вхідний контейнер
	int b[10], c[10], d[10]; // результуючі контейнери
	// (потрібно виділити достатньо пам'яті)
	int n = copy(&a[0], &a[5], &b[0]); // продублювали всі елементи
	for (int i = 0; i < n; i++)
		cout << b[i] << ' '; // вивели результат
	cout << endl;
	Predicate<int>* even = new Even<int>(); // функтор: "нульові елементи"
	n = copy_if(&a[0], &a[5], &c[0], *even); // продубювали нульові елементи
	for (int i = 0; i < n; i++)
		cout << c[i] << ' ';
	cout << endl;
	Predicate<int>* pos = new Positive<int>(); // функтор: "додатні елементи"
	n = copy_if(&a[0], &a[5], &d[0], *pos); // продублювали додатні елементи
	for (int i = 0; i < n; i++)
		cout << d[i] << ' ';
	cout << endl;
		system("pause");
	return 0;
}