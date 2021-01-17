#include <iostream>
#include "CodeGen/irgen.hpp"

extern int yyparse();
extern NBlock* astroot;

/* LLVM 模块和上下文环境 */
LLVMContext context; //提供了一个用来创建变量等对象的上下文环境。
Module module("tstjit", context);
IRBuilder<> builder(context); //创建 LLVM 指令并将指令插入基础块的类。

Function* get_func() {
    /* Compile the AST into a module */
    /* Create the top level interpreter function to call as entry */
    FunctionType* main_functype;
    Function* main_func;        
    main_functype = FunctionType::get(Type::getInt32Ty(context), false);//builder.getInt32Ty()
    main_func = Function::Create(main_functype, Function::InternalLinkage, "mainfunc", module);
    
    /* BasicBlock in function */
    BasicBlock* block = BasicBlock::Create(context, "entryblock", main_func);
    builder.SetInsertPoint(block);
    
    /* gen ir code */
    std::cout << "Generating code...\n" ;
    Value* val = astroot->codegen(builder); /* emit bytecode for the toplevel block */
    
    //先声明printf函数
    FunctionType *printFuncType = FunctionType::get(builder.getInt32Ty(), true);
    FunctionCallee printFunc = module.getOrInsertFunction("printf", printFuncType);
    vector<Value*> printArgs;
    Value* arg1_fmtStr = builder.CreateGlobalStringPtr("%d\n");
    Value* arg2_value = val;
    printArgs.push_back(arg1_fmtStr);
    printArgs.push_back(arg2_value);
    /*call printf*/
    builder.CreateCall(printFunc, printArgs);
    
    /* set return */
    builder.CreateRet(builder.getInt32(0));
    /* Print the readable IR */
    //std::cout << "IR Code is generated.\n";
    module.print(outs(),nullptr);
    return main_func;
}



int main(int argc, char **argv) {
    std::cout << ">" ;
    yyparse();
    
    InitializeNativeTarget();
	// InitializeAllTargets();
	// InitializeAllTargetMCs();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
	ExecutionEngine* ee = EngineBuilder(unique_ptr<Module>(&module)).create();
    ee->addModule(unique_ptr<Module>(&module));
    
    Function* main_func = get_func();
    ee->finalizeObject();
    
    std::cout << "Running code:\n";
    vector<GenericValue> noargs;
    GenericValue v = ee->runFunction(main_func, noargs);    
    // void *addr = ee->getPointerToFunction(main_func);
    // typedef int (*FuncType)();
    // FuncType mainfunc = (FuncType)addr;
    // ee->finalizeObject();
    // mainfunc();    
        
    std::cout << "Exiting...\n";
    return 0;
}
