#include <iostream>
#include <tuple>
#include <map>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>, позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(TasksInfo tasks_info);

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return developers.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		++(developers[person][TaskStatus::NEW]);
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo modified;
		TasksInfo unmodified;

		if (developers.find(person) == developers.end())
			return make_tuple(modified, unmodified);

		TasksInfo &per = developers[person];
		unmodified = per; unmodified.erase(TaskStatus::DONE);
		int num_new = per[TaskStatus::NEW], num_in_progress = per[TaskStatus::IN_PROGRESS], nem_testing = per[TaskStatus::TESTING];

//		cout << endl << "MY_TEST: task_count = " << task_count << endl;
//		cout << "MY_TEST(per): ";
//		PrintTasksInfo(per);

		int sum = num_new + num_in_progress + nem_testing;
		if (sum < task_count)
			task_count = sum;

/*
		if ((per[TaskStatus::NEW] > 0 && task_count > 0) && per[TaskStatus::NEW] >= task_count) {
			unmodified[TaskStatus::NEW] -= task_count;
			modified[TaskStatus::IN_PROGRESS] = task_count;
			per[TaskStatus::IN_PROGRESS] += task_count;
			per[TaskStatus::NEW] = per[TaskStatus::NEW] - task_count;
			task_count = 0;
		} else if ((per[TaskStatus::NEW] > 0 && task_count > 0) && per[TaskStatus::NEW] < task_count) {
			unmodified[TaskStatus::NEW] -= per[TaskStatus::NEW];
			modified[TaskStatus::IN_PROGRESS] = per[TaskStatus::NEW];
			per[TaskStatus::IN_PROGRESS] += per[TaskStatus::NEW];
			task_count = task_count - per[TaskStatus::NEW];
			per[TaskStatus::NEW] = 0;
		}

		if ((per[TaskStatus::IN_PROGRESS] > 0 && task_count > 0) && per[TaskStatus::IN_PROGRESS] >= task_count) {
			unmodified[TaskStatus::IN_PROGRESS] -= task_count;
			modified[TaskStatus::TESTING] = task_count;
			per[TaskStatus::TESTING] += task_count;
			per[TaskStatus::IN_PROGRESS] = per[TaskStatus::IN_PROGRESS] - task_count;
			task_count = 0;
		} else if ((per[TaskStatus::IN_PROGRESS] > 0 && task_count > 0) && per[TaskStatus::IN_PROGRESS] < task_count) {
			unmodified[TaskStatus::IN_PROGRESS] -= per[TaskStatus::IN_PROGRESS];
			modified[TaskStatus::TESTING] = per[TaskStatus::IN_PROGRESS];
			per[TaskStatus::TESTING] += per[TaskStatus::IN_PROGRESS];
			task_count = task_count - per[TaskStatus::IN_PROGRESS];
			per[TaskStatus::IN_PROGRESS] = 0;
		}

		if ((per[TaskStatus::TESTING] > 0 && task_count > 0) && per[TaskStatus::TESTING] >= task_count) {
			unmodified[TaskStatus::TESTING] -= task_count;
			modified[TaskStatus::DONE] = task_count;
			per[TaskStatus::DONE] += task_count;
			per[TaskStatus::TESTING] = per[TaskStatus::TESTING] - task_count;
			task_count = 0;
		} else if ((per[TaskStatus::TESTING] > 0 && task_count > 0) && per[TaskStatus::TESTING] < task_count) {
			unmodified[TaskStatus::TESTING] -= per[TaskStatus::TESTING];
			modified[TaskStatus::DONE] = per[TaskStatus::TESTING];
			per[TaskStatus::DONE] += per[TaskStatus::TESTING];
			task_count = task_count - per[TaskStatus::TESTING];
			per[TaskStatus::TESTING] = 0;
		}
*/

		CheckTasksInfo(per, modified, unmodified, task_count, TaskStatus::NEW, TaskStatus::IN_PROGRESS, num_new);
		CheckTasksInfo(per, modified, unmodified, task_count, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, num_in_progress);
		CheckTasksInfo(per, modified, unmodified, task_count, TaskStatus::TESTING, TaskStatus::DONE, nem_testing);

		ClearTaskINfo (modified); ClearTaskINfo (unmodified); ClearTaskINfo (per);

//		cout << "MY_TEST(modified): ";
//		PrintTasksInfo(modified);
//		cout << "MY_TEST(unmodified): ";
//		PrintTasksInfo(unmodified);
//		cout << "MY_TEST(per): ";
//		PrintTasksInfo(per);
//		cout << endl;

		return make_tuple(modified, unmodified);
	}

private:
	map<string, TasksInfo> developers;

	void ClearTaskINfo(TasksInfo &inf) {
		if (inf[TaskStatus::NEW] == 0)
			inf.erase(TaskStatus::NEW);
		if (inf[TaskStatus::IN_PROGRESS] == 0)
			inf.erase(TaskStatus::IN_PROGRESS);
		if (inf[TaskStatus::TESTING] == 0)
			inf.erase(TaskStatus::TESTING);
		if (inf[TaskStatus::DONE] == 0)
			inf.erase(TaskStatus::DONE);
	}

	void CheckTasksInfo(TasksInfo &inf, TasksInfo &modified, TasksInfo &unmodified, int &task_count, TaskStatus begin, TaskStatus end, int count) {
		if ((count > 0 && task_count > 0) && count >= task_count) {
			unmodified[begin] -= task_count;
			modified[end] = task_count;
			inf[begin] -= task_count;
			inf[end] += task_count;
			task_count = 0;
		} else if ((count > 0 && task_count > 0) && count < task_count) {
			unmodified[begin] -= count;
			modified[end] = count;
			inf[begin] -= count;
			inf[end] += count;
			task_count = task_count - count;

		}
	}
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " testing" <<
		", " << tasks_info[TaskStatus::DONE] << " done" << endl;
}


int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tasks.AddNewTask("Alice");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "Alice's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);

	cout << "Alice's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

	return 0;
}


/* образцовое решение
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчика
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

private:
  map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo& tasks_info) {
  // Соберём те статусы, которые нужно убрать из словаря
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
    const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;

  // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор []
  // в случае отсутствия ключа инициализирует значение по умолчанию,
  // если это возможно.
  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];

  // Посчитаем, сколько задач каждого из статусов нужно обновить,
  // пользуясь тем фактом, что по умолчанию enum class инциализирует значения
  // от нуля по возрастанию.
  // enum class -> http://ru.cppreference.com/w/cpp/language/enum
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    // Считаем обновлённые
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    // Считаем, сколько осталось обновить
    task_count -= updated_tasks[Next(status)];
  }

  // Обновляем статус текущих задач в соответствии с информацией об обновлённых
  // и находим количество нетронутых
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

  // По условию в словарях не должно быть нулей
  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);
  RemoveZeros(person_tasks_.at(person));

  return {updated_tasks, untouched_tasks};
}

 */

