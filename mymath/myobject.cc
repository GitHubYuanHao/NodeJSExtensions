// myobject.cc
#include <node.h>
#include "myobject.h"
#include "CppLib/mynumber.h"

namespace demo {

using node::AddEnvironmentCleanupHook;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Global;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Exception;

// Warning! This is not thread-safe, this addon cannot be used for worker
// threads.
Global<Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value)
{
}

MyObject::~MyObject()
{
}

void MyObject::Init(Isolate* isolate)
{
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", PlusOne);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Add",     Add);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Sub",     Sub);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Mul",     Mul);
  NODE_SET_PROTOTYPE_METHOD(tpl, "Div",     Div);

  Local<Context> context = isolate->GetCurrentContext();
  constructor.Reset(isolate, tpl->GetFunction(context).ToLocalChecked());

  AddEnvironmentCleanupHook(isolate, [](void*) {
    constructor.Reset();
  }, nullptr);
}

void MyObject::New(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = args[0]->IsUndefined() ?
        0 : args[0]->NumberValue(context).FromMaybe(0);
    MyObject* obj = new MyObject(value);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> instance =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(instance);
  }
}

void MyObject::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  const unsigned argc = 1;
  Local<Value> argv[argc] = { args[0] };
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> instance =
      cons->NewInstance(context, argc, argv).ToLocalChecked();

  args.GetReturnValue().Set(instance);
}

void MyObject::PlusOne(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());
  obj->value_ += 1;

  args.GetReturnValue().Set(Number::New(isolate, obj->value_));
}

void MyObject::Add(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    // Check the argument types
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
        return;
    }

    // Perform the operation
    double value = MyNumber::add(args[0].As<Number>()->Value(), args[1].As<Number>()->Value());
    //double value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}

void MyObject::Sub(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    // Check the argument types
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
        return;
    }

    // Perform the operation
    double value = MyNumber::sub(args[0].As<Number>()->Value(), args[1].As<Number>()->Value());
    //double value = args[0].As<Number>()->Value() - args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}


void MyObject::Mul(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    // Check the argument types
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
        return;
    }

    // Perform the operation
    //double value = MyNumber::mul(args[0].As<Number>()->Value(), args[1].As<Number>()->Value());
    double value = args[0].As<Number>()->Value() * args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}

void MyObject::Div(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 2)
    {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }

    // Check the argument types
    if (!args[0]->IsNumber() || !args[1]->IsNumber())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
        return;
    }

    // Perform the operation
    //double value = MyNumber::div(args[0].As<Number>()->Value(), args[1].As<Number>()->Value());
    double value = args[0].As<Number>()->Value() / args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}

}  // namespace demo
