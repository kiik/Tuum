
#ifndef TV9_ENV_H
#define TV9_ENV_H

#include <v8.h>

#define TV9_CTX() tuum::v9::ModuleContext* gV9MCtx = nullptr

#define TV9_CTX_HOOK() tuum::v9::_ctx_hook(gV9MCtx)

#define TV9_CTX_INIT() tuum::v9::_ctx_init(gV9MCtx)

#define TV9_CTX_INSERT(cls) printf("#TODO: :macro: 'TV9_CTX_INSERT'\n")


#define TV9_MOD_SCOPE() \
  Isolate* cIsolate = gIsolate; \
  Isolate::Scope iScope(cIsolate); \
  HandleScope hScope(cIsolate); \


namespace tuum { namespace v9 {

  extern v8::Isolate* gIsolate;

  int v8_init();

}}

#endif
