
#include <v8/libplatform/libplatform.h>

#include "tv9_env.hpp"

using namespace v8;

namespace tuum { namespace v9 {

  v8::Isolate* gIsolate = nullptr;

  int v8_init() {
    v8::V8::InitializeICUDefaultLocation("/usr/local/lib/v8/");
    v8::V8::InitializeExternalStartupData("/usr/local/lib/v8/");

    v8::Platform* platform = v8::platform::CreateDefaultPlatform();
    v8::V8::InitializePlatform(platform);

    v8::V8::Initialize();

    Isolate::CreateParams params;
    params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    gIsolate = v8::Isolate::New(params);


    return 0;
  }

}}
