#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <string>

using namespace std;
using namespace llvm;

/* LLVM 模块和上下文环境 *//*
LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
Module module("compiler", context); //LLVM IR 对象的顶级容器。
IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。*/



static std::unique_ptr<LLVMContext> context;
static std::unique_ptr<Module> module;
static std::unique_ptr<IRBuilder<>> builder;
//static std::map<std::string, Value *> NamedValues;

void InitializeModule(string modulename);