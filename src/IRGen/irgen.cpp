/* 由AST生成IR的代码 */
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
//#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

#include "../AST/ast.hpp"
#include "../Parse/parser.hpp"

using namespace std;
using namespace llvm;

#include <string> //for cout <<

std::map<std::string, AllocaInst*> namedValues;//键值表保存当前的代码范围内定义的值和记录

/* -- Code Generation -- */
Value* NInteger::codegen(Builder builder) {//Creating interger
    std::cout << "create intger\n";
    Value* val = builder.getInt32(value);
    return val;
}

Value* NIdentifier::codegen(Builder builder) {//get identifier reference
    std::cout << "get identifier\n";
    Value* alloc = namedValues[name];
    
    LoadInst* load = builder.CreateLoad(alloc);//, name.c_str());;
    return load;
}

Value* NAssignment::codegen(Builder builder) {//Creating assignment
    std::cout << "crate assign \n" ;
    AllocaInst* alloc;
    Value* val = rhs.codegen(builder);
	if (namedValues.end() == namedValues.find(lhs.name)) {
	//create var alloc
        alloc = builder.CreateAlloca(builder.getInt32Ty(), nullptr, lhs.name);
        alloc->setAlignment(MaybeAlign(4));
        namedValues[lhs.name] = alloc;
    }else{
       alloc = namedValues[lhs.name];
    }
    StoreInst* store = builder.CreateStore(val, alloc);//, false);
    store->setAlignment(MaybeAlign(4));
    return store;
}

Value* NBinaryOperate::codegen(Builder builder) {//Creating binary operation
    std::cout << "Creating binary operation\n" ;
    Value* L = lhs.codegen(builder);
    Value* R = rhs.codegen(builder);
    switch (op) {
        case ADD:
            return builder.CreateAdd(L, R, "addrst");
        case SUB:
            return builder.CreateSub(L, R, "subrst");
        case MUL:
            return builder.CreateMul(L, R, "mulrst");
        case DIV:
            return builder.CreateUDiv(L, R, "divrst");
    }
    return nullptr;
}

Value* NBlock::codegen(Builder builder) {
    std::cout << "create block\n" ;
    std::vector<Node*>::const_iterator it;
    Value* last = nullptr;
    for (it = nodes.begin(); it != nodes.end(); it++) {
        last = (**it).codegen(builder);
        delete *it;
    }
    return last;
}
