//evaluate string and return result
//7+8*3-4/2+9

#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

//This class only supports decimal number format 
//and following list of operators:
//*,/,%,+,-
//This class only support binary operator
//if at end or start operator is found than left rt default value to consider is 0
class ArithmeticParser
{
	map<char,int> operatorPriority;
	stack<char> operators;
	stack<double> operand;
	const double LEFT;
	const double RIGHT;

	bool isOperator(char val) const 
	{
		return (val<'0' || val>'9') && (val != '.');
	}
	
	int convertCharToInt(const string& val) const
	{
		return stod(val);
	}
	
	double performOperation(pair<double,double>&& values, char opratr) const 
	{
		double result;
		
		switch(opratr)
		{
			case '+':
				result = values.first + values.second;
			break;
			case '/':
				result = values.first / values.second;
			break;
			case '*':
				result = values.first * values.second;
			break;
			case '%':
				result = int(values.first) % int(values.second);
			break;
		}
		
		return result;
	}
	
	public:
	ArithmeticParser():LEFT(0.0),RIGHT(0.0)
	{
		//current supported opeartor set
		operatorPriority['*'] = 0;
		operatorPriority['/'] = 0;
		operatorPriority['%'] = 0;
		operatorPriority['+'] = 1;
		operatorPriority['-'] = 1;
	}
	
	double evaluate(const string& input)
	{
		double right = 0.0;
		double left = 0.0;
		string number = "";
		bool negate = false;
		
		for(auto c : input)
		{
			if(!isOperator(c))
				number += c;
			else
			{
				if(!number.empty())
				{
					operand.emplace(negate ? convertCharToInt(number) * -1 : convertCharToInt(number));
					negate = false;
					number.clear();
				}	
				if(operators.empty())
				{
					if(operand.empty())
						operand.push(LEFT);
					if(c != '-')	
						operators.push(c);
					else
					{
						negate = true;
						operators.push('+');
					}
				}
				else
				{
					char topOp = operators.top();
					if(operatorPriority[topOp] < operatorPriority[c])
					{
						operators.pop();
						right =  operand.top();//right operand
						operand.pop();
						left = operand.top();//left operand
						operand.pop();
						operand.emplace(performOperation(make_pair(left,right),topOp));
					}
					if(c != '-')	
						operators.push(c);
					else
					{
						negate = true;
						operators.push('+');
					}
				}
			}		
		}
		if(!number.empty())
		{
			operand.emplace(negate ? convertCharToInt(number) * -1 : convertCharToInt(number));
			negate = false;
			number.clear();
		}
		//if(!operand.empty())
		//		cout << "recent operand :" << operand.top() << " size of opernad stack "<<operand.size() << endl;
		//if(!operators.empty())	
		//		cout << "recent operator :" << operators.top() << " size of operator stack "<<operators.size()  << endl;
		while(!operators.empty())
		{
			char topOp = operators.top();
			operators.pop();
			right =  operand.top();//right operand
			operand.pop();
			left = 0.0;
			if(!operand.empty())
			{	
				left = operand.top();//left operand
				operand.pop();	
			}
			else
			{
				left = right;
				right = RIGHT;//in case we are running out of operand's and still an operator is remaining
			}
			operand.emplace(performOperation(make_pair(left,right),topOp));		
		}
		double output = operand.top();
		operand.pop();
		
		return output;
	}
	
};

int main()
{
	string input = "7+8*3-4/2+9";
	ArithmeticParser obj;
	cout << obj.evaluate(input);
	
	return 0;
}
