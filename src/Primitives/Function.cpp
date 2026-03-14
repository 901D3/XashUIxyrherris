
#include "Primitives/Function.h"

FunctionWithClassInstance::FunctionWithClassInstance() {
  function = nullptr;
  instance = nullptr;
}

FunctionWithClassInstance::~FunctionWithClassInstance() {
}

void FunctionWithClassInstance::operator()() {
  function();
}

void FunctionWithClassInstance::free() {
  function = nullptr;
  instance = nullptr;
}

void FunctionWithClassInstance::bind(PtrToVoidFunction function, void *instance) {
  this->function = function;
  this->instance = instance;
}
