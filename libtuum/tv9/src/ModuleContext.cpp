
#include <v8.h>
#include <v8pp/module.hpp>

#include "tv9_env.hpp"
#include "ModuleContext.hpp"

using namespace v8;

namespace tuum { namespace v9 {

  size_t ModuleContext::id_seq = 1;

  /*
  Handle<Value> Plus(const Arguments& args)
  {
    unsigned int A = args[0]->Uint32Value();
    unsigned int B = args[1]->Uint32Value();
    return uint32(A +  B);
  }*/

  // This function returns a new array with three elements, x, y, and z.
  /*
  Local<Array> NewPointArray(int x, int y, int z) {
    Isolate* isolate = Isolate::GetCurrent();

    // We will be creating temporary handles so we use a handle scope.
    HandleScope handle_scope(isolate);

    // Create a new empty array.
    Local<Array> array = Array::New(isolate, 3);

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
      return Local<Array>();

    // Fill out the values
    array->Set(0, Integer::New(isolate, x));
    array->Set(1, Integer::New(isolate, y));
    array->Set(2, Integer::New(isolate, z));

    // Return the value through Escape.
    return handle_scope.Escape(array);
  }*/

  void log(const char* event) {
    printf(":tv9: %s\n", event);
  }

  char const* Method() {
    return "world";
  }

  void test(Handle<Object> exports) {

  }

  Handle<Value> js_log(const v8::FunctionCallbackInfo<v8::Value>& args) {
    TV9_MOD_SCOPE();

    if(args.Length() < 1) return Undefined(cIsolate);

    Local<Value> arg = args[0];
    String::Utf8Value value(arg);

    log(*value);
    return Undefined(cIsolate);
  }

  ModuleContext::ModuleContext():
    m_id(id_seq++), m_init(false)
  {
    init();
  }

  int ModuleContext::init() {
    if(m_init) return 0;

    TV9_MOD_SCOPE();

    // Create a new context.
    Local<Context> context = Context::New(cIsolate);
    mContext.Reset(cIsolate, context);

    //Context::Scope scope(context);

    //mContext->Global()->Set(String::New("log"), FunctionTemplate::New(js_log)->GetFunction());

    v8pp::module addon(gIsolate);
    addon.set("log", &log);
    //mContext->Global()->Set(String::New("log"), addon.new_instance());
    addon.new_instance();
    //context->Global()->Set(String::NewFromUtf8(cIsolate, "log"), addon.new_instance());


    m_init = true;
    return 1;
  }

  int ModuleContext::exec() {
    printf("[ModuleContext::run]Do\n");

    //TV9_MOD_SCOPE();

    /*
    Context::Scope scope(Ctx());

    Handle<String> source = String::NewFromUtf8(cIsolate, "log2('Test');");
    Handle<Script> script = Script::Compile(source);
    Handle<Value> result = script->Run();

    String::Utf8Value ascii(result);
    printf("RESULT: %s\n", *ascii);
    */


    {
      Isolate* isolate = gIsolate;
      Isolate::Scope isolate_scope(isolate);

      // Create a stack-allocated handle scope.
      HandleScope handle_scope(isolate);

      // Create a new context.
      Local<Context> context = Context::New(isolate);

      // Enter the context for compiling and running the hello world script.
      Context::Scope context_scope(context);

      // Create a string containing the JavaScript source code.
      Local<String> source =
          String::NewFromUtf8(isolate, "'Hello' + ', World!'",
                              NewStringType::kNormal).ToLocalChecked();

      // Compile the source code.
      Local<Script> script = Script::Compile(context, source).ToLocalChecked();

      // Run the script to get the result.
      Local<Value> result = script->Run(context).ToLocalChecked();

      // Convert the result to an UTF8 string and print it.
      String::Utf8Value utf8(result);
      printf("%s\n", *utf8);
    }

    return 0;
  }

}}
