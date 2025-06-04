#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

class Student
{
public:
    string name;
    int roll;
    float CGPA;

    Student(string name, int roll, float CGPA)
    {
        this->name = name;
        this->roll = roll;
        this->CGPA = CGPA;
    }

    Student(int roll)
    {
        this->roll = roll;
    }
};
queue<Student>q;
stack<queue<Student>>s;

void saveDataToFile()
{
    ofstream file("students.txt");
    queue<Student> temp = q;

    while (!temp.empty())
    {
        Student s = temp.front();
        temp.pop();
        file << s.name << " " << s.roll << " " << s.CGPA << "\n";
    }

    file.close();
    cout << "Data saved to file successfully.\n";
}

void loadDataFromFile()
{
    ifstream file("students.txt");
    string name;
    int roll;
    float cgpa;

    while (file >> name >> roll >> cgpa)
    {
        q.push(Student(name, roll, cgpa));
    }

    file.close();
    cout << "Data loaded from file successfully.\n";
}

class Node : public Student
{
public:
    int data;
    Node *left;
    Node *right;

    Node(string name, int roll, float CGPA)
        : Student(name, roll, CGPA), data(roll), left(NULL), right(NULL) {}
};

// build BST;
Node *helper(Node *root, Student s)
{
    if (root == NULL)
    {
        root = new Node(s.name, s.roll, s.CGPA);
        return root;
    }

    if (s.roll < root->data)
    {
        root->left = helper(root->left, s);
    }

    if (s.roll > root->data)
    {
        root->right = helper(root->right, s);
    }

    return root;
}

Node *buildBST()
{
    Node *root = NULL;
    queue<Student> temp = q;
    while (!temp.empty())
    {
        root = helper(root, temp.front());
        temp.pop();
    }

    return root;
}

class Add : public Student
{
public:
    Add(string name, int roll, float CGPA)
        : Student(name, roll, CGPA) {}

    void add()
    {
        s.push(q);
        q.push({name, roll, CGPA});
    }

};

void inorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    cout << "Roll Number : " << root->data << endl;
    cout << "Name : " << root->name << endl;
    cout << "CGPA : " << root->CGPA << endl;
    inorder(root->right);
}

bool updateNode(Node *root, int newRoll = -1, int oldRoll = -1, string newName = "", float newCGPA = -1.0)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->roll == oldRoll)
    {
        if (newRoll != -1)
        {
            root->roll = newRoll;
            root->data = newRoll;
        }
        if (newName != "")
        {
            root->name = newName;
        }
        if (newCGPA != -1.0)
        {
            root->CGPA = newCGPA;
        }

        queue<Student> temp;
        while (!q.empty())
        {
            Student s = q.front();
            q.pop();

            if (s.roll == oldRoll)
            {
                if (newRoll != -1)
                    s.roll = newRoll;
                if (newName != "")
                    s.name = newName;
                if (newCGPA != -1.0)
                    s.CGPA = newCGPA;
            }

            temp.push(s);
        }
        q = temp;
        return true;
    }

    if (root->roll < oldRoll)
    {
        return updateNode(root->right, newRoll, oldRoll, newName, newCGPA);
    }

    else
    {
        return updateNode(root->left, newRoll, oldRoll, newName, newCGPA);
    }
}

class del : public Student{
protected:
    queue<Student>temp;
public:
    del(int roll) 
        : Student(roll) {}

    Node* getInorderedSuccesor(Node* root) {
        while(root->left != NULL) {
            root = root->left;
        }

        return root;
    }

    Node* Del(Node* root, int val) {
        if(root == NULL) {
            return NULL;
        }

        if (val < root->data)
        {
            root->left = Del(root->left, val);
        }

        if (val > root->data)
        {
            root->right = Del(root->right, val);
        } else {
        
            //case 1
            if(root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            }

            //case 2
            if(root->left == NULL || root->right == NULL) {
                return root->left == NULL ? root->right : root->left;
            }

            //case 3
            Node* IS = getInorderedSuccesor(root->right);
            root->data = IS->data;
            root->right = Del(root->right, IS->data);
            return root;
        }
        return root;
    }
    
    void change(int val) {
        while(!q.empty()) {
            Student s = q.front();
            q.pop();
            if(s.roll != val) {
                temp.push(s);
            }
        }
        q = temp;
    }
};
Node* root = NULL;
bool isBuild = false; // avoid every time build tree

int main()
{
    loadDataFromFile();
    int in;
    while (true)
    {
        cout << "\n1. Add Data\n2. Update Data\n3. Delete Data\n4. Print Data\n5. Undo\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> in;

        if (in == 1)
        {
            string name;
            int roll;
            float cgpa;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter roll: ";
            cin >> roll;
            cout << "Enter CGPA: ";
            cin >> cgpa;

            Add a1(name, roll, cgpa);
            a1.add(); // adds to global queue
            if(!isBuild) {
                root = buildBST(); // builds BST
            }          
            
        }
        else if (in == 2)
        {
            // update data... name roll CGPA

            int oldRoll, newRoll;
            string newName;
            float newCGPA;

            cout << "Enter old roll number to update: ";
            cin >> oldRoll;

            cout << "Enter new roll (-1 to skip): ";
            cin >> newRoll;

            cout << "Enter new name (type '-' to skip): ";
            cin >> newName;

            cout << "Enter new CGPA (-1 to skip): ";
            cin >> newCGPA;

            if (newName == "-")
                newName = "";

            s.push(q);
            bool updated = updateNode(root, newRoll, oldRoll, newName, newCGPA);
            if (updated){
                cout << "Student record updated successfully.\n";
                if(!isBuild) {
                    root = buildBST(); // builds BST
                } 
            }
            else
                cout << "Student with roll " << oldRoll << " not found.\n";
            
            
            inorder(root);
        }
        else if (in == 3)
        {
            int r;
            cout << "Enter The Roll Number You want To Delete : ";
            cin >> r;
            // delete data
            s.push(q);
            del d1(r);
            d1.Del(root, r);
            d1.change(r);
            if(!isBuild) {
                root = buildBST(); // builds BST
            } 
        }
        else if (in == 4)
        {   //print data
            if(!isBuild) {
                root = buildBST(); // builds BST
            }
            inorder(root); 
        }
        else if (in == 5)
        {
            //undo
            if(!s.empty()) {
                q = s.top();
                s.pop(); 
                cout <<"Undo successful.\n";
            } else {
                cout << "No previous state to undo.\n";
            }
        }
        else if(in == 6) {
            break;
        }
    }
    saveDataToFile();
    return 0;
}
