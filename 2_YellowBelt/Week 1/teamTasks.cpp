class TeamTasks {
private:
	std::map<std::string, TasksInfo> tasksByPerson;

public:

	// ѕолучить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
			return tasksByPerson.at(person);
	}

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
	void AddNewTask(const std::string& person) {
		++tasksByPerson[person][TaskStatus::NEW];
	}

	// ќбновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count) {
		int uCounter = 0;
		TasksInfo tasksUpdated, tasksUntouched;
		if (tasksByPerson.count(person) == 0) {
			return std::tie(tasksUpdated, tasksUntouched);
		}
		TasksInfo tasksInfo = GetPersonTasksInfo(person);

		int iUntouched = 0;
		iUntouched = tasksInfo[TaskStatus::NEW];
		for (int i = 0; i < 4; ++i) {		
			uCounter = 0;
			TaskStatus itemFirst = static_cast<TaskStatus>(i);
			int& itemSecond = tasksInfo[itemFirst];

			if (itemFirst != TaskStatus::DONE) {

				if (task_count == 0 && iUntouched > 0) {
					tasksUntouched[itemFirst] = iUntouched;
					iUntouched = tasksInfo[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)];
				}
				else if (iUntouched >= task_count) {
					itemSecond -= task_count;
					if (iUntouched > 0 && (iUntouched - task_count) != 0) {
						tasksUntouched[itemFirst] = iUntouched - task_count;
					}
					iUntouched = tasksInfo[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)];
					tasksInfo[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)] += task_count;
					if (task_count > 0) {
						tasksUpdated[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)] = task_count;
					}
					task_count = 0;
				}
				else if (iUntouched < task_count) {
					uCounter = iUntouched;
					task_count -= iUntouched;
					iUntouched = tasksInfo[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)];
					tasksInfo[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)] += uCounter;					
					if ((uCounter > 0 && itemSecond - uCounter <= 0) || itemSecond == 0) {
						tasksInfo.erase(itemFirst);
					}
					else {
						tasksInfo[itemFirst] -= uCounter;
					}
					if (uCounter > 0) {
						tasksUpdated[static_cast<TaskStatus>(static_cast<int>(itemFirst) + 1)] = uCounter;
					}
				}
			}
		}
		tasksByPerson[person] = tasksInfo;
		return std::tie(tasksUpdated, tasksUntouched);
	}
};