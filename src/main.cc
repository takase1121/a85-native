#include <napi.h>
#include "a85/a85.h"

Napi::String a85_encode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::Error::New(env, "No argument specified").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    if (!info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Only Buffer is supported").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    Napi::Buffer<uint8_t> buf = info[0].As<Napi::Buffer<uint8_t>>();

    size_t srcBufSize = buf.Length();
    uint8_t *srcBuf = buf.Data();

    int outputSize = a85::size_for_a85(srcBufSize, true);
    char output[outputSize];
    a85::to_a85(srcBuf, srcBufSize, output, true);

    return Napi::String::New(env, output);
}

Napi::Buffer<uint8_t> a85_decode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::Error::New(env, "No argument specified").ThrowAsJavaScriptException();
        return Napi::Buffer<uint8_t>::New(env, 0);
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Only string is supported").ThrowAsJavaScriptException();
        return Napi::Buffer<uint8_t>::New(env, 0);
    }

    Napi::String str = info[0].As<Napi::String>();
    std::string rawStr = str.Utf8Value();

    int outputSize = a85::size_for_bin(rawStr.length());
    uint8_t output[outputSize];

    a85::from_a85(rawStr.c_str(), rawStr.length(), output);

    if (!output) {
        Napi::Error::New(env, "Decode error").ThrowAsJavaScriptException();
        return Napi::Buffer<uint8_t>::New(env, 0);
    }

    return Napi::Buffer<uint8_t>::Copy(env, output, outputSize);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set("stringify", Napi::Function::New(env, a85_encode));
    exports.Set("parse", Napi::Function::New(env, a85_decode));
    return exports;
}

NODE_API_MODULE(ascii85native, InitAll)