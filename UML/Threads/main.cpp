//Threads
#include<iostream>
#include<thread>
using namespace std;
using namespace std::chrono_literals;

bool finish = false;

void Hello()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(100ms);
	}
}
void World()
{
	while (!finish)
	{
		cout << "- ";
		std::this_thread::sleep_for(100ms);
	}
}

void main()
{
	setlocale(LC_ALL, "");
	//Инициализация потоков при объявлении:
	/*std::thread hello_thread(Hello);	
	std::thread world_thread(World);*/

	//Объявление потоков:
	std::thread hello_thread;
	std::thread world_thread;

	//Инициализация потоков после объявления:
	hello_thread = std::thread(Hello);
	world_thread = std::thread(World);

	cin.get();	//Ожидает нажатие Enter
	finish = true;

	hello_thread.join();	//Синхронизирует потоки
	world_thread.join();
}