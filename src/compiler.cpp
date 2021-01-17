#include <iostream>
#include "CodeGen/irgen.hpp"

#include "llvm/IR/LegacyPassManager.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <system_error>

extern int yyparse();
extern Node* astroot;

/* LLVM 模块和上下文环境 */
LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
Module module("compiler", context); //LLVM IR 对象的顶级容器。
IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。

Function* genIR() {
    std::cout << "Generating code...\n";
    FunctionType* main_functype;
    Function* main_func;
    main_functype = FunctionType::get(builder.getInt32Ty(), false);
    main_func = Function::Create(main_functype, Function::ExternalLinkage, "main", module); //GlobalValue::InternalLinkage会出错
    
    /* BasicBlock in function */
    BasicBlock *block = BasicBlock::Create(context, "entryblock", main_func);
    builder.SetInsertPoint(block);
    Value* val = astroot->codegen(builder);    /* Compile the AST into a module */
    
	//打印计算结果
    //先声明printf函数
    FunctionType *printFuncType = FunctionType::get(builder.getInt32Ty(), true);
    FunctionCallee printFunc = module.getOrInsertFunction("printf", printFuncType);
    vector<Value*> printArgs;
    Value *arg1_fmtStr = builder.CreateGlobalStringPtr("%d\n");
    Value *arg2_value = val;
    printArgs.push_back(arg1_fmtStr);
    printArgs.push_back(arg2_value);
    /*call printf*/
    builder.CreateCall(printFunc, printArgs);
    /* set return */
    builder.CreateRet(builder.getInt32(0));
    
    std::cout << "Code is generated.\n";
	//std::cout << "Printing IR code...\n";
	//module.print(outs(),nullptr);

    return main_func;
}


int main(int argc, char **argv) {
	/* scan token and parse src */
    std::cout << "\nPlease input the expr:\n";
	yyparse();	
    genIR();
	
	///compile objectfile
	//initialize all the targets for emitting object code.
	InitializeAllTargetInfos();
	InitializeAllTargets();
	InitializeAllTargetMCs();
	InitializeAllAsmParsers();
	InitializeAllAsmPrinters();
	//use target triple to get a Target
	auto TargetTriple = sys::getDefaultTargetTriple();
	module.setTargetTriple(TargetTriple);
	
	std::string Error;
	auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

	if (!Target) {
	  errs() << Error;
	  return 1;
	}
	//taget machine
	auto CPU = "generic";
	auto Features = "";

	TargetOptions opt;
	auto RM = Optional<Reloc::Model>();
	auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
	//Configuring the Module
	module.setDataLayout(TargetMachine->createDataLayout());
    module.setTargetTriple(TargetTriple);
	//emit object code
	auto Filename = "program.o";
	std::error_code EC;
	raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

	if (EC) {
	  errs() << "Could not open file: " << EC.message();
	return 1;}
	
	legacy::PassManager pass;
	auto FileType = CGFT_ObjectFile;

	if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
	  errs() << "TargetMachine can't emit a file of this type";
	  return 1;
	}

	pass.run(module);
	dest.flush();
	
	outs() << "Wrote " << Filename << "\n";
	return 0;
}
