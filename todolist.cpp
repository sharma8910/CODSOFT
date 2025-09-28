#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Task {
    string description;
    bool completed;
};

void addTask(vector<Task> &tasks) {
    string taskDesc;
    cout << "Enter the task: ";
    cin.ignore(); // clear input buffer
    getline(cin, taskDesc);
    tasks.push_back({taskDesc, false});
    cout << "Task added successfully!\n";
}


void viewTasks(const vector<Task> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks available!\n";
        return;
    }

    cout << "\nTo-Do List \n";
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description;
        if (tasks[i].completed)
            cout << " [Completed]";
        else
            cout << " [Pending]";
        cout << endl;
    }
}


void markCompleted(vector<Task> &tasks) {
    int index;
    cout << "Enter task number to mark completed: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }
    tasks[index - 1].completed = true;
    cout << "Task marked as completed!\n";
}


void deleteTask(vector<Task> &tasks) {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;
    if (index < 1 || index > tasks.size()) {
        cout << "Invalid task number!\n";
        return;
    }
    tasks.erase(tasks.begin() + (index - 1));
    cout << "Task deleted successfully!\n";
}

int main() {
    vector<Task> tasks;
    int choice;

    while (true) {
        cout << "\n To-Do List \n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: viewTasks(tasks); break;
            case 3: markCompleted(tasks); break;
            case 4: deleteTask(tasks); break;
            case 5: cout << "Exiting... Bye!\n"; return 0;
            default: cout << "Invalid Try again.\n";
        }
    }
}
