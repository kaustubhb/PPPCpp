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

const char QUIT = 'q';
const char PRINT = ';';

class Token_stream
{
public:
  Token_stream();
  Token get();
  void putback(Token t);
  void ignore(char c);  // ignore everything up till c

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
    case PRINT: case QUIT:
    case '+': case '-': case '*': case '/': case '!':
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

void Token_stream::ignore(char c)
{
  if(isFull)
  {
    isFull = false;
    if(bufTok.kind == ';')
      return;
  }
  char ch;
  while(cin >> ch)
    if(ch == c)
      return;
}

//---------------------------------------------------------

double term();
double primary();
double factTerm();

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
  double left = factTerm();
  Token t = ts.get();

  while(true)
  {
    switch(t.kind)
    {
    case '*':
      left *= factTerm();
      t = ts.get();
      break;
    case '/':
      {
        double right = factTerm();
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

double factTerm()
{
  double left = primary();
  Token t = ts.get();

  if(t.kind == '!')
  {
    double result = 1;
    for(size_t i=2;i<=left;++i)
      result *= i;
    return result;
  }

  ts.putback(t);
  return left;
}

// Handling unary '-' here creates a complication. Now expressions like ---1; are valid.
// Ideally, unary should be handled at one higher level.

double primary()
{
  Token t = ts.get();

  switch(t.kind)
  {
    case '(':
    {
      double val = expression();
      t = ts.get();
      if (t.kind != ')')
        error ("Closing parenthesis expected, but not found");
      return val;
    }

    case '{':
    {
      double val = expression();
      t = ts.get();
      if(t.kind != '}')
        error ("Closing brace expected, but not found");
      return val;
    }

    case '-':   // unary minus
      return - primary();
    case '+':
      return primary();
    case '8':
      return t.value;

    default:
      error("Primary expected, but found something else");
  }

  // can never reach here
  cerr << "Should never reach here" << endl;
  return 0;
}

//----------------------------------------------------------

void clean_up_mess();

double calculateLoop()
{
  double result = 0;

  cout << "> ";
  while (cin)
  {

    try
    {
      Token t = ts.get();
      if(t.kind == QUIT)
        break;
      if(t.kind == PRINT) {
        cout << "= " << result << endl << "> ";
        while(t.kind == PRINT)
            t = ts.get();
        ts.putback(t);
        continue;
      }
      ts.putback(t);
      result = expression();
    }
    catch(exception &ex)
    {
      cerr << ex.what() << endl;
      clean_up_mess();
      cout << "> ";
    }
  }
  return result;
}

void clean_up_mess()
{
  ts.ignore(PRINT);
}

int main()
{
  try
  {
    calculateLoop();
    return 0;
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