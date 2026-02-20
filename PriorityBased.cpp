#include<bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
};

bool arrivalComp(process a, process b){
    if(a.arrivalTime == b.arrivalTime) return a.pid < b.pid;
    return a.arrivalTime < b.arrivalTime;
}

struct priorityComp{
    bool operator()(process a, process b){
        if(a.priority == b.priority) return a.arrivalTime > b.arrivalTime;
        return a.priority < b.priority;
    }
};

int main(){
    int n;
    cout<<"Enter Number of processes: ";
    cin>>n;
    
    vector<process> p(n);
    vector<process> completedProcess;

    for(int i=0;i<n;i++){
        cout<<endl<<endl<<"Process"<<i+1<<endl;
        p[i].pid = i + 1;
        
        cout<<"Priority: ";
        cin>>p[i].priority;
        
        cout<<endl<<"Arrival Time: ";
        cin>>p[i].arrivalTime;
        
        cout<<endl<<"Burst Time: ";
        cin>>p[i].burstTime;
    }

    sort(p.begin(),p.end(),arrivalComp);

    priority_queue<process,vector<process>,priorityComp> pq;
    int currentTime = 0;
    int currentProcess = 0;

    while(completedProcess.size() < n){
        while(currentProcess<n && p[currentProcess].arrivalTime <= currentTime){
            pq.push(p[currentProcess]);
            currentProcess++;
        }

        process topProcess = pq.top();
        pq.pop();

        currentTime += topProcess.burstTime;
        topProcess.completionTime = currentTime;
        topProcess.turnaroundTime = topProcess.completionTime - topProcess.arrivalTime;
        topProcess.waitingTime = topProcess.turnaroundTime - topProcess.burstTime;

        completedProcess.push_back(topProcess);
    }

    double totalTurnaroundTime = 0,totalWaitingTime = 0;
    cout<<endl<<"pid\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    
    sort(completedProcess.begin(),completedProcess.end(),[](process a,process b){
        return a.pid < b.pid;
    });
    
    
    for(auto &it:completedProcess){
         cout<<it.pid<<"\t\t"<<it.arrivalTime<<"\t\t"<<it.burstTime<<"\t\t"<<it.completionTime<<"\t\t"<<it.turnaroundTime<<"\t\t"<<it.waitingTime<<"\n";
         totalTurnaroundTime += it.turnaroundTime;
         totalWaitingTime += it.waitingTime;
    }

    cout<<"Average Turnaround Time: "<<totalTurnaroundTime/n<<endl;
    cout<<"Average Waiting Time: "<<totalWaitingTime/n<<endl;

}