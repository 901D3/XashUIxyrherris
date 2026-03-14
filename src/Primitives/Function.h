
#pragma once

typedef void (*PtrToVoidFunction)(void);
typedef void (*PtrToVoidFunctionData)(void *);

static void dummyFunction() {
}

class FunctionWithClassInstance {
public:
  FunctionWithClassInstance();
  ~FunctionWithClassInstance();

  PtrToVoidFunction function;
  void *instance;

  void operator()();
  void free();
  void bind(PtrToVoidFunction function, void *instance);
};
