#include<bits/stdc++.h>
using namespace std;

struct process{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool vectorComp(process a, process b){
    if(a.arrivalTime == b.arrivalTime) return a.pid < b.pid;
    return a.arrivalTime < b.arrivalTime;
}

bool pqComp(process a, process b){
    return a.remainingTime > b.remainingTime;
}

int main(){
    int n;
    cout<<"Enter total number of processes: ";
    cin>>n;

    vector<process> allProcess(n);
    vector<process> completedProcess;

    for(int i=0;i<n;i++){
        allProcess[i].pid = i+1;
        cout<<"Process "<<i+1<<endl;
        cout<<"Arrival Time: "<<endl;
        cin>>allProcess[i].arrivalTime;
        cout<<"Burst Time: "<<endl;
        cin>>allProcess[i].burstTime;
        allProcess[i].remainingTime = allProcess[i].burstTime;
    }

    sort(allProcess.begin(),allProcess.end(),vectorComp);
    
    priority_queue<process, vector<process>, function<bool(process,process)>> pq(pqComp);

    
    int currentTime = 0;
    int currentProcess = 0;
    
    while(completedProcess.size() < n){
        while(currentProcess<n && allProcess[currentProcess].arrivalTime <= currentTime){
            pq.push(allProcess[currentProcess]);
            currentProcess++;
        }
        if(pq.empty()){
            currentTime++;
            continue;
        }

        process topProcess = pq.top();
        pq.pop();

        topProcess.remainingTime--;

        if(topProcess.remainingTime==0){
            topProcess.completionTime = currentTime+1;
            topProcess.turnaroundTime = topProcess.completionTime - topProcess.arrivalTime;
            topProcess.waitingTime = topProcess.turnaroundTime - topProcess.burstTime;
            completedProcess.push_back(topProcess);
        }
        else pq.push(topProcess);
        
        currentTime++;
    }

    double totalTurnaroundTime = 0,totalWaitingTime = 0;
    cout<<"pid\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
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