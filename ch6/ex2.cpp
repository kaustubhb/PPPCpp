#include "std_lib_facilities.h"

class Token
{
public:
  char kind;
  double value;   // only relevant if kind is '8'
  Token() { }
  Token (char ch): kind(ch) { }
  Token (char ch, double val): kind(ch), value(val) { }
};

//-------------------------------------------------------

class Token_stream
{
public:
  Token_stream();
  Token get();
  void putback(Token t);

private:
  Token bufTok;
  bool isFull;
};

Token_stream ts;  // global

Token_stream::Token_stream()
{
  isFull = false;
}

void Token_stream::putback(Token t)
{
  //cout << "Putting back " << t.kind << endl;
  if(isFull)
    error("Trying to push more than 1 token to token_stream");
  bufTok = t;
  isFull = true;
}

Token Token_stream::get()
{
  if(isFull)
  {
    isFull = false;
    return bufTok;
  }

  char ch;
  cin >> ch;
  switch(ch)
  {
    case ';': case 'q':
    case '+': case '-': case '*': case '/':
    case '(': case ')': case '{': case '}':
      return Token{ch}; 
    case '.':
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9':
    {
      cin.putback(ch);
      double d;
      cin >> d;
      return Token{'8', d}; 
    }
    default:
      error("Bad token, can't recognize"); 
  }

  cerr << "Should never reach here";
  return Token();
}

//---------------------------------------------------------

double term();
double primary();

double expression()
{
  double left = term();
  Token t = ts.get();   // Token stream

  while(true)
  {
    switch(t.kind)
    {
    case '+':
      left += term();
      t = ts.get();
      break;
    case '-':
      left -= term();
      t = ts.get();
      break;
    default:
      ts.putback(t);
      return left;
    }
  }
}

double term()
{
  double left = primary();
  Token t = ts.get();

  while(true)
  {
    switch(t.kind)
    {
    case '*':
      left *= primary();
      t = ts.get();
      break;
    case '/':
      {
        double right = primary();
        if(right == 0)
          error("Division by 0 error");
        left /= right;   
        t = ts.get();
      }
      break;
    default:
      ts.putback(t);
      return left;
    }
  }
}

double primary()
{
  Token t = ts.get();
  if(t.kind == '(')
  {
    double val = expression();
    t = ts.get();
    if (t.kind != ')')
      error ("Closing parenthesis expected, but not found");
    return val;
  }
  else if(t.kind == '{')
  {
    double val = expression();
    t = ts.get();
    if(t.kind != '}')
      error ("Closing brace expected, but not found");
    return val;
  }
  else if (t.kind == '8')
    return t.value;
  error("Primary expected, but found something else");

  // can never reach here
  cerr << "Should never reach here" << endl;
  return 0;
}

//----------------------------------------------------------

int main()
{
  try
  {
    double result = 0;
    while (cin)
    { 
      Token t = ts.get();
      //cout << "Token: " << t.kind << endl;
      if(t.kind == 'q') {
        break;
      }
      if(t.kind == ';') {
        cout << "= " << result << endl;
        continue;
      }
      ts.putback(t);
      result = expression();
    }
  }
  catch (exception &ex) {
    cerr << ex.what() << endl;
    return 1;
  }
  catch (...) {
    cerr << "Some exception occurred" << endl;
    return 2;
  }
}