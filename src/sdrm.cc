#include <windows.h>
#include <napi.h>

typedef bool (__cdecl *SteamAPI_Init)();
typedef bool (__cdecl *SteamAPI_RestartAppIfNecessary)(uint32_t);

using namespace Napi;

Napi::Boolean Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if(!info[1].IsNumber())
  {
    Napi::TypeError::New(env, "App ID should be nunmber. Uint32.").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  SteamAPI_Init f_SteamAPI_Init;
  SteamAPI_RestartAppIfNecessary f_SteamAPI_RestartAppIfNecessary;

  std::string arg1 = info[0].ToString().Utf8Value();
  std::uint32_t app_id = info[1].As<Napi::Number>().Uint32Value();

  const char* steamlibpath = arg1.c_str();
  HINSTANCE steamLib = LoadLibrary(steamlibpath);

  if(!steamLib)
  {
    Napi::Error::New(env, "Cannot load steam api .dll file").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  f_SteamAPI_Init = (SteamAPI_Init) GetProcAddress(steamLib, "SteamAPI_Init");
  f_SteamAPI_RestartAppIfNecessary = (SteamAPI_RestartAppIfNecessary) GetProcAddress(steamLib, "SteamAPI_RestartAppIfNecessary");

  if(!f_SteamAPI_Init || !f_SteamAPI_RestartAppIfNecessary)
  {
    Napi::Error::New(env, "Cannot load steam api functions.").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  if(f_SteamAPI_RestartAppIfNecessary(app_id))
  {
    Napi::Error::New(env, "App must be running through your steam client.").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  if(!f_SteamAPI_Init())
  {
    Napi::Error::New(env, "Steam must be running. You may not own a license of the application.").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "SDRM"), Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(addon, Init)
