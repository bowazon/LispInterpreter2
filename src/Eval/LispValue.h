#ifndef LISPINTERPRETER2_LISPVALUE_H
#define LISPINTERPRETER2_LISPVALUE_H

#include "../Level1Parser/Level1Token.h"
#include "../Level2Parser/Level2Token.h"
#include <list>

using namespace std;

class LispValue;

typedef LispValue* (*ReservedProc) (LispValue* operands, LispValue* (*eval) (list<Level2Token*>));

enum class LispValueType {
    kNumber,
    kBoolean,
    kQuot,
    kIdentifier,
    kBuiltIn, // TODO is ts built in function or any built in? because #t and #f are also built in
    kLazy, // TODO is it more like Lisp List?
    kMsgToTheWorld
};

class LispValue {
protected:
    LispValueType type;
    LispValue(){}; // TODO move to protected or private
public:
    LispValueType get_type() {return type; }
    virtual string get_val() {return "";} // TODO DUMMY!
    virtual list<Level2Token*> get_list() {return list<Level2Token*>();}// TODO DUMMY!
    virtual ReservedProc get_proc() {return nullptr; }
    virtual string to_string() = 0;

    // TODO all this virtual methods that return dummy values are even worse than just bad,
    // they are very confusing, I always think that type dispatch -> dynamic cast ->
    // -> call proper function would be much better.
    // So how can I get rid of dispatching and virtual dummy methods?
};

enum class NumberType {
    kInteger,
    kFloat
};

class NumberVal : public LispValue {
private:
    NumberType num_type;
    int int_val;
    float float_val;
public:
    NumberVal(int val) {
        this->int_val = val;
        this->num_type = NumberType::kInteger;
        this->type = LispValueType::kNumber;
    }
    NumberVal(float val) {
        this->float_val = val;
        this->num_type = NumberType::kFloat;
        this->type = LispValueType::kNumber;
    }
    NumberVal(string s) {
        this->int_val = stoi(s); // TODO do for floats
        this->num_type = NumberType::kInteger;
        this->type = LispValueType::kNumber;
    }
    void add(int n) { // TODO overload operator+
        if (num_type == NumberType::kInteger) {
            int_val += n;
        } else {
            float_val += n;
        }
    }
    void add(float n) {
        if (num_type == NumberType::kInteger) {
            int_val += n;
        } else {
            float_val += n;
        }
    }
    void add(NumberVal* n) {
        if (num_type == NumberType::kInteger) {
            if(n->num_type == NumberType::kInteger) {
                int_val += n->int_val;
            } else {
                int_val += n->float_val;
            }
        } else {
            if(n->num_type == NumberType::kInteger) {
                float_val += n->int_val;
            } else {
                float_val += n->float_val;
            }
        }
    }
    string to_string() override {
        if (num_type == NumberType::kFloat) {
            return std::to_string(float_val);
        } else {
            return std::to_string(int_val);
        }
    }
};

class BooleanVal : public LispValue {
private:
    bool val;
public:
    BooleanVal(bool val) {
        this->val = val;
        this->type = LispValueType::kBoolean;
    }
    BooleanVal(string val) {
        if (val.compare("#f") == 0) {
            this->val = false;
        } else if (val.compare("#t") == 0) {
            this->val = true;
        } else {
            // TODO
        }
        this->type = LispValueType::kBoolean;
    }
    string to_string() override {
        return val ? "#t" : "#f";
    }
};

class IdentifierVal : public LispValue {
private:
    string val;
public:
    IdentifierVal(string val) {
        this->val = val;
        this->type = LispValueType::kIdentifier;
    }
    string to_string() override {
        return val;
    }
};

class BuiltIn : public LispValue {
private:
    //string val;
    // TODO built in types????
    ReservedProc proc;
public:
    BuiltIn(ReservedProc proc) {
        this->proc = proc;
        this->type = LispValueType::kBuiltIn;
    }
    ReservedProc get_proc() override {
        return proc;
    }
    string to_string() override {
        return "built in procedure";
    }
    /*
    BuiltIn(string val) {
        this->val = val;
        this->type = LispValueType::kBuiltIn;
    }
    string get_val() override {
        return val;
    }
    string to_string() override {
        return "primitive procedure " + val;
    }
     */
};

class LazyVal : public LispValue {
private:
    list<Level2Token*> tokens;
public:
    LazyVal(list<Level2Token*> tokens) {
        this->tokens = tokens;
        this->type = LispValueType::kLazy;
    }
    list<Level2Token*> get_list() override {
        return tokens;
    }
    string to_string() override { // TODO implement
        list<Level2Token*>::iterator it;
        string output = "";
        for (it = tokens.begin(); it != tokens.end(); ++it) {
            Level2Token* crnt = *it;
            output.append(crnt->to_string());
            output.append(" ");
        }
        return output;
    }
    // do we need methods like get_first_token(), get_second_token()????s
    // maybe token setters will be useful in lambdas?
};

class MsgToTheWorld : public LispValue {
private:
    string msg;
public:
    MsgToTheWorld(string msg) {
        this->msg = msg;
        this->type = LispValueType::kMsgToTheWorld;
    }
    string to_string() override {
        return msg;
    }
};

// TODO can we set types using visitor pattern???

#endif //LISPINTERPRETER2_LISPVALUE_H
