#include <iostream>
#include <string>
using namespace std;

//                 STRUCTURES:

//for queue - stage files
struct fileNode{
    string filename;
    fileNode* next;
};

//struct for commit - doubly LL
struct commit{
    int commitID;
    string commitMessage;
    commit* prev;
    commit* next;
};

//stacknode for undo redo
struct StackNode{
    commit* c;
    StackNode* next;
};



//1. Queue with LL - emaan
class fileQueue{
    private:
    fileNode* front;
    fileNode* rear;

    public:
    fileQueue(){
        front=rear=nullptr;
    }

    bool isEmpty(){
        return front==nullptr;
    }

    void enqueue(string n){
        fileNode* newNode=new fileNode();
        newNode->filename=n;
        newNode->next=nullptr;

        if(isEmpty()){
            front=newNode;
            rear=newNode;
        }else{
            rear->next=newNode;
            rear=newNode;
        }
    }

    void clear(){
        while (!isEmpty()){
            fileNode* temp=front;
            front=front->next;
            delete temp;
        }
        rear=nullptr;
    }

    void display(){
        if (isEmpty()){
            cout<<"No staged files \n";
            return;
        }

        fileNode* temp=front;
        cout<<"Staged files:\n";
        while(temp!=NULL){
            cout<<"->"<<temp->filename<<endl;
            temp=temp->next;
        }
    }
};

//2. stack using linked list - huma
class commitStack{
    private:
    StackNode* top;

    public:
    commitStack(){
        top=nullptr;
    }

    bool isEmpty(){
        return top==nullptr;
    }

    void push(commit* c){
        StackNode* newNode=new StackNode();
        newNode->c=c;
        newNode->next=top;
        top=newNode;
    }

    commit* pop(){
        if (isEmpty()){ return NULL; }

        StackNode* temp=top;
        commit* poppedval=temp->c;
        top=temp->next;
        delete temp;
        return poppedval;
    }

    void clear(){
        while(!isEmpty()){
            pop();
        }
    }
};

//3. version control system - alina
class versionControl{
    private:
    commit* head;
    commit* tail;
    commit* current;
    int commitCount;

    fileQueue staging;
    commitStack undoStack;
    commitStack redoStack;

    public:
    versionControl(){
        head=tail=current=nullptr;
        commitCount=0;
    }

    void stageFile(){
        string n;
        cout<<"Enter filename: ";
        cin>>n;
        staging.enqueue(n);
        cout<<"File is staged\n";
    }

    void commitChanges(){
        if(staging.isEmpty()){
            cout<<"Staging queue is empty\n";
            return;
        }

        string msg;
        cin.ignore();
        cout<<"Enter commit message: ";
        getline(cin,msg);

        commit* newCommit=new commit();
        newCommit->commitID=++commitCount;
        newCommit->commitMessage=msg;
        newCommit->prev=tail;
        newCommit->next=NULL;

        if(head==NULL){
            head=tail=newCommit;
        }else{
            tail->next=newCommit;
            tail=newCommit;
        }

        if(current!=NULL){
            undoStack.push(current);
        }

        current=newCommit;
        redoStack.clear();
        staging.clear();

        cout<<"Commit executed with ID: "<<newCommit->commitID<<endl;
    }

    void showStagedFiles(){
        staging.display();
    }

    void showHistory(){
        if (head==NULL){
            cout<<"No commits yet.\n";
            return;
        }

        commit* temp=head;
        cout<<"\nCommit History:\n";
        while (temp!=NULL){
            cout<<"Commit "<<temp->commitID<<": "<<temp->commitMessage;
            if (temp==current) cout<<"  <- current";
            cout<<endl;
            temp=temp->next;
        }
    }

    void undoCommit(){
        if (undoStack.isEmpty()){
            cout<<"Nothing to undo.\n";
            return;
        }

        redoStack.push(current);
        current=undoStack.pop();
        cout<<"Undo successful. Current commit ID: "<<current->commitID<<endl;
    }

    void redoCommit(){
        if (redoStack.isEmpty()){
            cout<<"Nothing to redo.\n";
            return;
        }

        undoStack.push(current);
        current=redoStack.pop();
        cout<<"Redo successful. Current commit ID: "<<current->commitID<<endl;
    }
};

int main(){
    versionControl vc;
    int choice;

    do{
        cout<<"\n===== VERSION CONTROL SYSTEM =====\n";
        cout<<"1. Stage File\n";
        cout<<"2. View Staged Files\n";
        cout<<"3. Commit Changes\n";
        cout<<"4. Undo Commit\n";
        cout<<"5. Redo Commit\n";
        cout<<"6. View Commit History\n";
        cout<<"0. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch (choice){
            case 1:
                 vc.stageFile(); 
                 break;
            case 2: 
                 vc.showStagedFiles(); 
                 break;
            case 3: 
                 vc.commitChanges(); 
                 break;
            case 4: 
                 vc.undoCommit(); 
                 break;
            case 5: 
                 vc.redoCommit(); 
                 break;
            case 6: 
                 vc.showHistory(); 
                 break;
            case 0: 
                 cout<<"exiting\n"; 
                 break;
            default: 
                     cout<<"Invalid choice.\n";
        }

    }while(choice!=0);

    return 0;
}
 
