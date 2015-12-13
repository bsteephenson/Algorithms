// Task Runner

// Problem:
// Given a list of tasks, their priorities, and their dependencies (which tasks must come before others),
// determine the order to write tasks

// Solution:
// Make a graph to represent dependencies, each vertex (task) is pointed to by its dependencies
// Add all tasks with no dependencies onto a priority queue
// While prioritiy queue is not empty
// Get max task T of the queue. Add T to taskList.
// For every task U that depends on T, remove T from U's depenency list.
// If U's dependency list is now empty, add U to the priority queue.
// Finally print out / return taskList which represents the tasks in the order they should be performed

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class TaskRunner {
public:
    void addTask(int taskID, int priority);
    void addDependency(int before, int after); // 'before' must be run before 'after'
    void run();
private:
    struct Task {
        int id;
        int priority;
        set<int> neededTasks; // all the tasks I depend on
        set<int> nextTasks; // all the tasks that depend on me
        bool operator()(Task const &t1, Task const &t2) const
        {
            return t1.priority < t2.priority;
        }
    };
    unordered_map<int, Task> tasks;
};

int main ()
{
    TaskRunner tr;
    tr.addTask(1, 2);
    tr.addTask(2, 4);
    tr.addTask(3, 5);
    tr.addTask(4, 10);
    tr.addTask(5, 1);
    tr.addDependency(1, 3);
    tr.addDependency(1, 4);
    tr.addDependency(5, 2);

    cout << "Run tasks in this order" << endl;
    tr.run();
}

void TaskRunner::addTask(int taskID, int priority)
{
    Task t;
    t.id = taskID;
    t.priority = priority;
    tasks[taskID] = t;

}
void TaskRunner::addDependency(int before, int after)
{
    tasks[before].nextTasks.insert(after);
    tasks[after].neededTasks.insert(before);
}
void TaskRunner::run()
{
    vector<int> taskList;
    priority_queue<Task, vector<Task>, Task> q;

    // enqueue every reachable task
    for (auto t = tasks.begin(); t != tasks.end(); t++) {
        if (t->second.neededTasks.empty()) {
            q.push(t->second);
        }
    }

    while (!q.empty()) {
        
        Task t = q.top();
        q.pop();
        taskList.push_back(t.id);
        
        // for every task that depended on me
        for (auto next = t.nextTasks.begin(); next != t.nextTasks.end(); next++) {
            
            int taskID = *next;
            
            // unmark me as a dependency off that task
            tasks[taskID].neededTasks.erase(t.id);
            
            // if that task now has no uncleared dependencies, enqueue task
            if (tasks[taskID].neededTasks.size() == 0) {
                q.push(tasks[taskID]);
            }

        }

    }


    for (int i = 0; i < taskList.size(); i++) {
        cout << taskList[i] << endl;
    }
}





