/* 抽象语法树（Abstract Syntax Tree）定义 */
/* 仅定义抽象语法树的节点类，Ast树通过Bison自动生成 */

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

typedef IRBuilder<> Builder;

class Node {
public:
	virtual ~Node() {}
	virtual llvm::Value* codegen(Builder builder) = 0; //{ return NULL; }//通过llvm api创建IR最常用的方法就是调用IRBuilder
};

class NBlock: public Node {
public:
	std::vector<Node*> nodes;
	NBlock() { }
	llvm::Value* codegen(Builder builder) override;
};

class NInteger : public Node {
public:
	long long value;
	NInteger(long long value) : value(value) { }
	llvm::Value* codegen(Builder builder) override;
};

class NIdentifier : public Node {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	llvm::Value* codegen(Builder builder) override;
};

class NBinaryOperate : public Node {
public:
	int op;
	Node& lhs;
	Node& rhs;
	NBinaryOperate(Node& lhs, int op, Node& rhs):lhs(lhs), rhs(rhs), op(op) { }
	llvm::Value* codegen(Builder builder) override;
};

class NAssignment : public Node {
public:
	NIdentifier& lhs;
	Node& rhs;
	NAssignment(NIdentifier& lhs, Node& rhs): lhs(lhs), rhs(rhs) { }
	llvm::Value* codegen(Builder builder) override;
};
