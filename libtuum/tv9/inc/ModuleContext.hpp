

#ifndef TV9_MODCTX_H
#define TV9_MODCTX_H

#include <cstring>
#include <stdio.h>

#include <v8.h>

namespace tuum { namespace v9 {

  void log(const char* event);

  v8::Handle<v8::Value> js_log(const v8::FunctionCallbackInfo<v8::Value>& args);

  class ModuleContext {
  public:
    static size_t id_seq;

    ModuleContext();

    int init();

    virtual int exec();

    template <class TypeName>
    inline v8::Local<TypeName> StrongPersistentToLocal(
      const v8::Persistent<TypeName>& persistent)
    {
      return *reinterpret_cast<v8::Local<TypeName>*>(
        const_cast<v8::Persistent<TypeName>*>(&persistent));
    }

    template <class TypeName>
    inline v8::Local<TypeName> StrongPersistentToLocal(
      const v8::Persistent<TypeName>& persistent) const
    {
      return *reinterpret_cast<const v8::Local<TypeName>*>(
        const_cast<const v8::Persistent<TypeName>*>(&persistent));
    }

    v8::Local<v8::Context> Ctx() { return StrongPersistentToLocal(mContext); }
    v8::Local<v8::Context> Ctx() const { return StrongPersistentToLocal(mContext); }

  protected:
    v8::Persistent<v8::Context> mContext;

  private:
    size_t m_id;

    bool m_init;
  };

}}

#endif
