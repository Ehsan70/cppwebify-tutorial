#include <nan.h>
#include <functional>
#include <iostream>

#include "exchange.h"
#include "prime_sieve.h"


using namespace Nan;
using namespace std;
using namespace v8;

// Synchronous access to the `getPrimes()` function
/*
the function signature is actually a call to a Nan macro. NAN_METHOD decorates the CalculatePrimes function to 
have the correct parameters and return types - which are highly specific to the version of V8 you are using.
*/
NAN_METHOD(CalculatePrimes) {
    /*
    think of a scope object as a slab of memory - like a stack frame - where your V8 local variables are created
    within. V8 local variables can be passed back to JavaScript calling code, and can expose data coming from
    the calling JavaScript as well.
    */
    Nan:: HandleScope scope;

    /*
    Extract the parameter this function would be called with. Nan wraps the actual call signature in an info 
    object. It’s an array of parameters, representing the parameters the JavaScript code called the function with.
    */
    int under = To<int>(info[0]).FromJust();
    v8::Local<v8::Array> results = New<v8::Array>(under);

    int i = 0;
    Exchange x(
        [&](void * data) {
            Nan::Set(results, i, New<v8::Number>(*((int *) data)));
            i++;
       });

    generate_primes(under, (void*)&x);

    info.GetReturnValue().Set(results);
}


NAN_MODULE_INIT(Init) {
    Nan::Set(target, New<String>("getPrimes").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(CalculatePrimes)).ToLocalChecked());
}

NODE_MODULE(addon, Init)

