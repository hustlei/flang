#include "init.hpp"

using namespace std;

void InitializeModule(string modulename) {
  // Open a new context and module.
  context = std::make_unique<LLVMContext>();
  module = std::make_unique<Module>(modulename, *context);

  // Create a new builder for the module.
  builder = std::make_unique<IRBuilder<>>(*context);
}