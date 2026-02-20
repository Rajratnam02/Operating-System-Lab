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

bool comp(process a,process b){
    if(a.arrivalTime == b.arrivalTime) return a.pid < b.pid;
    return a.arrivalTime < b.arrivalTime;
}

int main(){
    int n;
    cout<<"Enter total no of processes: ";
    cin>>n;

    int timeQuantum;
    cout<<endl<<"Enter allowed Time Quantum: ";
    cin>>timeQuantum;

    vector<process> p(n);
    vector<process> completedProcess;

    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        cout<<endl<<"Process "<<i+1<<endl;
        cout<<endl<<"Arrival Time: ";
        cin>>p[i].arrivalTime;
        cout<<endl<<"Burst Time: ";
        cin>>p[i].burstTime;
        p[i].remainingTime = p[i].burstTime;
    }
    
    sort(p.begin(),p.end(),comp);

    queue<process> q;

    int currentProcess = 0;
    int currentTime = 0;

    while(completedProcess.size() < n){
        while(currentProcess<n && p[currentProcess].arrivalTime <= currentTime){
            q.push(p[currentProcess]);
            currentProcess++;
        }

        process topProcess = q.front();
        q.pop();

        if(topProcess.remainingTime > timeQuantum){
            topProcess.remainingTime = topProcess.remainingTime - timeQuantum;
            currentTime = currentTime + timeQuantum;
            while(currentProcess<n && p[currentProcess].arrivalTime <= currentTime){
                q.push(p[currentProcess]);
                currentProcess++;
            }
            q.push(topProcess);
        }else{
            currentTime += topProcess.remainingTime;
            topProcess.completionTime = currentTime;
            topProcess.turnaroundTime = topProcess.completionTime - topProcess.arrivalTime;
            topProcess.waitingTime = topProcess.turnaroundTime - topProcess.burstTime;
            completedProcess.push_back(topProcess);
        }
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