#include "std_lib_facilities.h"
#include <cmath>

class Token
{
public:
  char kind;
  double value;   // only relevant if kind is '8'
  string name;    // for variables
  Token() { }
  Token (char ch): kind(ch) { }
  Token (char ch, double val): kind(ch), value(val) { }
  Token (char ch, string n): kind(ch), name(n) { }
};

//-------------------------------------------------------

const char QUIT = 'q';
const char PRINT = ';';
const char LET = 'L';     // denotes let token
const char NAME = 'a';    // denotes a variable
const string DECLKEY = "let";

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
    case PRINT: case QUIT: case ',':
    case '+': case '-': case '*': case '/': case '!':
    case '(': case ')': case '{': case '}': case '=':
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
    {
      string s;
      if(isalpha(ch))
      {
        s += ch;
        while(cin.get(ch) && (isalpha(ch) || isdigit(ch)))
          s += ch;
        cin.putback(ch);
        if(s == DECLKEY)
          return Token{LET};
        else
        {
          //cout << "Found token " << s << endl;
          return Token{NAME,s};
        }
      }
      error("Token_stream::get: bad token.");
    }
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

//-------------------------------------------------------

class Variable
{
public:
  string name;
  double value;
  Variable(string var, double val): name(var), value(val) {}
};

vector<Variable> var_table;

double get_value(string s)
{
  for(const Variable &v : var_table)
    if(v.name == s)
      return v.value;
  error("get_value: undefined variable.");

  // should never get here
  return 0;
}

void set_value(string s, double d)  // sets existing variable
{
  for(Variable &v : var_table)
    if(v.name == s) {
      v.value = d;
      return;
    }
  error("set_value: undefined variable.");
}

bool is_declared(string var)
{
  for (Variable &v : var_table)
    if(v.name == var)
      return true;
  return false;
}

double define_name(string var, double val)
{
  if(is_declared(var))
    error("define_name: variable already declared.");
  var_table.push_back(Variable(var,val));
  return val;
}

//---------------------------------------------------------

double term();
double primary();
double factTerm();
double expression();
double declaration();

double statement()
{
  Token t = ts.get();
  switch (t.kind)
  {
    case LET:     // how to get a token that is more than 1 characters long
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }
}

double declaration()
{
  Token t = ts.get();
  if(t.kind != NAME)
    error("declaration: expecting variable name.");
  string var = t.name;    // TODO: add name field in token
  t = ts.get();
  if(t.kind != '=')
    error("declaration: expecting = symbol");
  double d = expression();
  return define_name(var, d);
}

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
    case NAME:
    {
      Token f = ts.get();
      if (f.kind == '(')  // this is a function
      {
        if(t.name == "sqrt") {
          double arg1 = expression();
          f = ts.get();
          if(f. kind != ')')
            error("primary: expected ( for closing function call.");

          if(arg1 < 0)
            error("primary: trying to take square root of a negative number.");
          return sqrt(arg1);
        }

        else if(t.name == "pow") {
          double arg1 = expression();
          f = ts.get();
          if(f.kind != ',')
            error("primary: expected \',\' for 2nd parameter of pow.");
          double arg2 = expression();
          f = ts.get();
          if(f. kind != ')')
            error("primary: expected ( for closing function call.");
          return pow(arg1, arg2);
        }
      }
      else {
        ts.putback(f);
        return get_value(t.name);
      }
    }

    default:
      error("primary: Primary expected, but found something else");
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
      {
        cout << "Quitting" << endl;
        break;
      }
      if(t.kind == PRINT) {
        cout << "= " << result << endl << "> ";
        while(t.kind == PRINT)
            t = ts.get();
        ts.putback(t);
        continue;
      }
      ts.putback(t);
      result = statement();
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
    define_name("k", 1000);
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
