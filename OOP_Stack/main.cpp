#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "MyStack.h"

using namespace std;

class Calculator {
	Stack* Sh; //toan hang
	Stack* St; //toan tu
	string OperatorList[15] = {"sqrt", "exp", "log", "sin", "cos", "tan", "asin", "acos", "atan", "sinh", "cosh", "tanh", "abs"};
	int OpeNum;

	int Priority(string x) {
		if(x == "^")
			return 3;
		if (x == "*" || x == "/" || x == "%")
			return 2;
		else if (x == "+" || x == "-")
			return 1;
		else if (x == "(")
			return 0;
		return -1;
	}

	char Check(string x) {
		if (x == "*" || x == "/" || x == "%" || x == "+" || x == "-" || x == "^")
			return 0;
		for(int i = 0; i < OpeNum; i++) {
			if(x == OperatorList[i])
				return 1;
		}

		return 2;
	}

	string calculateOpe(string b, string x) {
		float fb = atof(b.c_str());

		if(x == "sqrt")
			return to_string(sqrt(fb));
		else if(x == "exp")
			return to_string(exp(fb));
		else if(x == "log")
			return to_string(log(fb));
		else if(x == "abs")
			return to_string(fabs(fb));
		else if(x == "sin")
			return to_string(sin(fb));
		else if(x == "cos")
			return to_string(cos(fb));
		else if(x == "tan")
			return to_string(tan(fb));
		else if(x == "asin")
			return to_string(asin(fb));
		else if(x == "acos")
			return to_string(acos(fb));
		else if(x == "atan")
			return to_string(atan(fb));
		else if(x == "sinh")
			return to_string(sinh(fb));
		else if(x == "cosh")
			return to_string(cosh(fb));
		else if(x == "tanh")
			return to_string(tanh(fb));

		return "none";
	}

	string CalculateVal(string b, string x, string a) {
		float fResult = 0;
		float fa = atof(a.c_str());
		float fb = atof(b.c_str());

		if(x == "^")
			fResult = pow(fb, fa);
		else if(x == "%")
			fResult = int(fb) % int(fa);
		else if (x == "*")
			fResult = fb * fa;
		else if (x == "/")
			fResult = fb / fa;
		else if (x == "+")
			fResult = fb + fa;
		else if (x == "-")
			fResult = fb - fa;

		return to_string(fResult);
	}

public:
	Calculator() {
		Sh = new Stack(); 
		St = new Stack();
		OpeNum = 13;
	}

	~Calculator() {
		delete Sh;
		delete St;
	}

	vector<string> ParseInput(string input) {
		size_t spacePos;
		while((spacePos = input.find(" ")) != string::npos)
			input.erase(spacePos,1);
		vector<string> M;
		int pos;
		while(input.length() > 0) {
			if(input[0] >= '0' && input[0] <= '9') {
				pos = 1;
				while(pos < input.length() && input[pos] >= '0' && input[pos] <= '9')
					pos++;
				M.push_back(input.substr(0, pos));
				input.erase(0, pos);
			}
			else if(input.length() > 3 && input[0]=='(' && input[1] == '-') {
				pos = 2;
				while(pos < input.length() && input[pos] != ')')
					pos++;
				M.push_back(input.substr(1, pos-1));
				input.erase(0, pos+1);
			}
			else if(input[0] == '(' || input[0] == ')' || input[0] == '*' || input[0] == '/' || input[0] == '+' ||
					input[0] == '-' || input[0] == '%' || input[0] == '^') {
				M.push_back(input.substr(0, 1));
				input.erase(0, 1);
			}
			else {
				pos = 1;
				while(pos < input.length() && input[pos] >= 'a' && input[pos] <= 'z')
					pos++;
				M.push_back(input.substr(0, pos));
				input.erase(0, pos);
			}
		}
		return M;
	}

	float Calculate(vector<string> M) {


		float fResult = 0;
		string a, b, x;

		for (int i = 0; i < M.size(); i++)
		{
			// toan hang
			if (Check(M[i]) == 2 && M[i] != "(" && M[i] != ")") 
				Sh->Push(M[i]); 

			if (M[i] == "(") 
				St->Push(M[i]);
			// toan tu
			if (Check(M[i]) == 0) 
			{
				while (!St->IsEmpty() && (Priority(M[i]) <= Priority(St->GetHead()->Info))) 
				{
					Sh->Pop(a);       
					St->Pop(x);       
					Sh->Pop(b);      
					Sh->Push(CalculateVal(b, x, a));   
				}
				St->Push(M[i]); 
			}
			// operator
			if(Check(M[i]) == 1) {
				St->Push(M[i]);
			}

			if (M[i] == ")") 
			{
				while (St->GetHead()->Info != "(") 
				{
					Sh->Pop(a);       
					St->Pop(x);       
					Sh->Pop(b);      
					Sh->Push(CalculateVal(b, x, a));   
				}
				St->Pop(b);
				if(!St->IsEmpty() && !Sh->IsEmpty()) {
					x = St->GetHead()->Info;
					b = Sh->GetHead()->Info;
					a = calculateOpe(b, x);
					if(a != "none") {
						St->Pop(x);
						Sh->Pop(b);
						Sh->Push(a);
					}
				}
			}
		}

		while (!St->IsEmpty()) {	
			Sh->Pop(a);      
			St->Pop(x);
			Sh->Pop(b);      
			Sh->Push(CalculateVal(b, x, a));   
		}

		string strResult = "";
		Sh->Pop(strResult); 
		fResult = atof(strResult.c_str());
		return fResult;
	}
};

int main()
{
	string input;
	cout << "When input negative number, please add (). Ex: sin((-1))" << endl;
	cout << "When input sin, cos, sqrt,... , please add (). Ex: sin(5+(5*2))" << endl;
	cout << "Input \"exit\" to out of the program" << endl;
	Calculator *myCal;
	bool gExit = false;
	while(!gExit) {
		cout << endl << "Enter:  ";
		getline(cin, input);
		if(input == "exit") {
			gExit = true;
			break;
		}
		myCal = new Calculator();
		vector<string> listInput = myCal->ParseInput(input);
		// for(string s : listInput)
		// 	cout << s << endl;
		cout << "Result: " << myCal->Calculate(listInput) << endl;
		delete myCal;
	}
	
	return 0;
}