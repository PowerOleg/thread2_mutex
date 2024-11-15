#### Оператор копирования использует конструктор копирования.

Data::Data(const Data& data) : var(data.var)
{

	if (&data == this)
	{
		throw std::invalid_argument("Invalid_argument: this object and the argument object are the same");
	}
}

Data& Data::operator=(const Data& other_data)
{

	if (&other_data == this)
	{
		throw std::invalid_argument("Invalid_argument: this object and the argument object are the same");
	}
 
	return *this = Data(other_data);//создается объект используя конструктор копирования
}

+1)std::lock_guard<std::mutex> lg1(m1) - предсказуемый и !при исключении разблокирует mutex! 
По принципу RAII блокирует от начала скобочек до конца скобочки(области видимости).
Принимает только один mutex

+2)std::scoped_lock<...> sl1(m1, m2)—это улучшенная версия std::lock_guard<std::mutex> lg1(m1),
конструктор которого блокирует произвольное количество мьютексов в фиксированном порядке. (c++ 17)
предотвращает при этом взаимную блокировку (сомнительно).

-3)используя m1.lock; m1.unlock; при ислючении mutex не разблокируется! 

4)std::lock l1(m1, m2) имеет встроенный алгоритм недопущения deadlock(сомнительно) и работает с несколькими mutex. для разблокировки нужно писать l1.unlock();

+5)std::unique_lock<std::mutex> lk(m1); lk.lock(); lk.unlock(); когда надо тогда и блочит
есть функционал std::condition_variable


