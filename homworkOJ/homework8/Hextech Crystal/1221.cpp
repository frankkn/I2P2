#include <cmath>

class Constant : public Function
{
	private:
    	double val;
        Constant(double _val): val(_val) {}
	public:
        static Constant *create(double _val) {
        	return new Constant(_val);
        }
        Function *differential() override {
        	return new Constant(0);
        }
        double eval(double _val) override {
        	return val;
        }
};

class Variable : public Function
{
	private:
    	string var;
		Variable(string _var):var(_var) {}
	public:
        static Variable *create(string _var) {
        	return new Variable(_var);
        }
        Function *differential() override {
        	return Constant::create(1);
        }
        double eval(double val) override {
        	return val;
        }
};

class Polynomial : public Function
{
	private:
		Function *base, *exp;
        Polynomial(Function *_base, Function *_exp):base(_base), exp(_exp) {}
	public:
        static Polynomial *create(Function *_base, Function *_exp) {
        	return new Polynomial(_base, _exp);
        }
        Function *differential() override;
        double eval(double val) override {
        	return pow(base->eval(val), exp->eval(val));
        }
};

class Arithmetic : public Function
{
	private:
    	enum class Type {Add, Sub, Mul, Div};
        Type type;
        Function *l, *r;
        Arithmetic(Type _type, Function *_l, Function *_r): type(_type), l(_l), r(_r) {}
	public:
        static Arithmetic *create(Function *l, char op, Function *r) {
        	switch(op) {
            	case '+':
                	return new Arithmetic(Type::Add, l, r);
                case '-':
                	return new Arithmetic(Type::Sub, l, r);
                case '*':
                	return new Arithmetic(Type::Mul, l, r);
                case '/':
                	return new Arithmetic(Type::Div, l, r);
            }
        }
        Function *differential() override {
        	Function *dl = l->differential(), *dr = r->differential();
            switch(type) {
            	// (A+B)' = A' + B'
            	case Type::Add:
                case Type::Sub:
                	return new Arithmetic(type, dl, dr);
                // (AB)' = AB' + A'B
                case Type::Mul:
            		return new Arithmetic(Type::Add, new Arithmetic(Type::Mul, l, dr), new Arithmetic(Type::Mul, dl, r));
                // (A/B)' = (A'B - AB') / B^2
                case Type::Div:
                	return new Arithmetic(Type::Div, new Arithmetic(Type::Sub, new Arithmetic(Type::Mul,dl,r), new Arithmetic(Type::Mul,l,dr)), Polynomial::create(r, Constant::create(2)));
            }
        
        }
        double eval(double val) override {
        	switch(type) {
            	case Type::Add:
                	return l->eval(val) + r->eval(val);
                case Type::Sub:
                	return l->eval(val) - r->eval(val);
                case Type::Mul:
                	return l->eval(val) * r->eval(val);
                case Type::Div:
                	return l->eval(val) / r->eval(val);
            }   	
        }
};

class Sin : public Function
{	
	private:
    	Function *base;
        Sin(Function *_base):base(_base) {}
	public:
        static Sin *create(Function *_base) {
        	return new Sin(_base);
        }
        Function *differential() override;
        double eval(double val) override {
        	return sin(base->eval(val));
        }
};

class Cos : public Function
{
	private:
    	Function *base;
        Cos(Function *_base):base(_base) {}
	public:
        static Cos *create(Function *_base) {
        	return new Cos(_base);
        }
        Function *differential() override {
        	// cos(A)' = -sin(A) * A'
            return Arithmetic::create(Arithmetic::create(Constant::create(0),'-',Sin::create(base)),'*', base->differential());
        }
        double eval(double val) override {
        	return cos(base->eval(val));
        }
};

Function *Polynomial::differential() {
	// (b^e)' = e * b^e-1 * b'
    return Arithmetic::create(exp, '*', Arithmetic::create(new Polynomial(base, Constant::create(exp->eval(0)-1)),'*', base->differential()));
}

Function *Sin::differential() {
	// sin(A)' = cos(A) * A'
    return Arithmetic::create(Cos::create(base),'*', base->differential());
}