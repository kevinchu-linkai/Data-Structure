//============================================================================
// Name         : lab5.cpp
// Author       :
// Version      : 1.0
// Date Created :
// Date Modified:
// Copyright    : All rights are reserved
// Description  : Convert Infix expression to PostFix and then evaluate it
//============================================================================
#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<ctype.h>

using namespace std;

bool isOperator(char); //Function which checks if the input char is an operator
int convertOpToInt (char); //Function which converts operators into int so their precdence can be compared
bool isleq(char, char); //Function which compare two operators  and return True if first operator has less or equal predence than the right operator
string infix2postfix(string);   //Function which converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);     //Function which will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton which will check for balanced parentheses

//==============CStack Class===============
class StackEmpty:public exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Top of empty stack";
        }
};

class StackFull:public exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Push to full stack";
        }
};

template <typename T>
class CStack{
    enum{DEF_CAPACITY = 100};
    private:
        T* S;
        int capacity;
        int t;
    public:
        CStack(int cap = DEF_CAPACITY);
        void push(const T& e) throw();
        void pop() throw();
        const T& top() const throw();
        int size() const;
        bool empty() const;
};
template <typename T> CStack<T>::CStack(int cap) : S(new T[cap]), capacity(cap), t(-1) { }

template <typename T> int CStack<T>::size() const { return (t + 1);}

template <typename T> bool CStack<T>::empty() const { return (t < 0);}

template <typename T> const T& CStack<T>::top() const throw() {
    if (empty()) {
        throw StackEmpty();
    } return S[t];
}

template <typename T> void CStack<T>::push(const T& e) throw() {
    if (size() == capacity){
        throw StackFull();
    }S[++t] = e;
}

template <typename T> void CStack<T>::pop() throw() {
    if (empty()){
        throw StackEmpty();
    }--t;
}


//=============Main funciton ==============
int main()
{

    while(true)
    {
        string infix;                          //Infix expression
        cout<<"Enter an Infix Expression: ";
        cin>>infix;
        try
        {
            if(infix=="exit")
                break;
            
            else if(!isBalanced(infix))
            {
                cout<<"Expression is not Balanced "<<endl;
                continue;
            }

            string postfix = infix2postfix(infix);    //Postfix Expression
            cout<<"The postfix form is: "<<postfix<<endl;
            float ans=evaluate(postfix);            //evaluate the postfix Expresion
            cout<<infix<<"="<<ans<<endl;        //print the final answer
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }
    }

    return EXIT_SUCCESS;
}
//=====================================================================
bool isOperator(char ch)
{
    if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
        return true;
    else
        return false;

}
//Function which converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper Function which compare two operators and return True if first operator
//has less or equal predence than the right operator
bool isleq(char opA, char opB)
{
    return (convertOpToInt(opA)<=convertOpToInt(opB));
}

//Funciton which will check for balanced parentheses
bool isBalanced(string expression)
{
    int right_parentheses = 0;
    CStack <char> input;
    for(int i = 0; i < expression.size(); i++){
        if(expression[i] == '(' || expression[i] == ')'){
            input.push(expression[i]);
        }
    }
    int x = input.size();
    for(int i = 0; i < x; i++){
        cout << input.top();
        if(right_parentheses == 0 && input.top() == '('){return false;}
        else{
            if(input.top() == ')'){right_parentheses++;}
            else if(right_parentheses != 0 && input.top() == '('){right_parentheses--;}
        }
        input.pop();
    }
    if(right_parentheses == 0){
        return true;
    }
    else{
        return false;
    }
}

// Function which converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix)
{
    string postfix;
    CStack <char> op_paren;//0.    Create a stack of type char to store operators/parenthesis
    op_paren.push('(');
    infix += ')';//1.    Push “(“onto Stack, and add “)” to the end of INFIX.
    
    for (int i = 0; i < infix.length(); i++) {
        //2.    Scan INFIX from left to right and repeat Step 3 to 6 for each element of X
        //until the Stack is empty.3.
        if(infix[i] == '('){
            op_paren.push(infix[i]);
        }
        //4.    If a left parenthesis is found, push it onto Stack.
        else if(isOperator(infix[i])){
            while(!op_paren.empty() && isleq(infix[i], op_paren.top())){
                postfix += op_paren.top();
                op_paren.pop();
            }
            op_paren.push(infix[i]);
        }
        //5.    If an operator is found, then:
                //a.    Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack)
                    //which has the same precedence as or higher precedence than operator.
                //b.    Push the operator onto Stack.
        else if(infix[i] == ')'){
            while (op_paren.top() !='(') {
                postfix += op_paren.top();
                op_paren.pop();
            }
            op_paren.pop();
        }
        //.6.    If a ")" is found, then:
                //a.    Repeatedly pop from Stack and add to POSTFIX each operator
                //(on the top of Stack) until a "(" found.
                //b.    Remove(pop) the "(" from the stack
        else{
            postfix += infix[i];
        }
        //3.    If an operand is found, add it to POSTFIX.
    }
    
    return postfix;
}
        
// //Function which will evaluate a PostfixExpression and return the result
float evaluate(string postfix)
{
    CStack <float> operand; //1. Create a stack of type float to store the operands
    for(int i = 0; i < postfix.length(); i++){
        if (isOperator(postfix[i])) {
            int a = operand.top();
            operand.pop();
            int b = operand.top();
            operand.pop();
            if (postfix[i] == '+') {
                a = a + b;
            }
            else if (postfix[i] == '-') {
                a = a - b;
            }
            else if (postfix[i] == '*') {
                a = a * b;
            }
            else if (postfix[i] == '/') {
                a = a / b;
            }
            else if (postfix[i] == '^') {
                a = pow(a, b);
            }
            operand.push(a);
        }
        else{
            operand.push(postfix[i]-48);
        }
        
    }
    //2. Scan the postfix expression from left to right for every element
    //     a. if an operand is found push it to the stack
    //   b. if an operator is found pop 2 elements from the stack,
    //      apply the operator on it and push the result back to the stack
    
    return operand.top();
    //3. return the value from the top of the stack (i.e. the final answer)
}
