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
    // Allocating a new local V8 array that will be our return value - an array of prime numbers less than “under”.
    v8::Local<v8::Array> results = New<v8::Array>(under);

    // In exchange class, We are creating a callback, which primesieve (generate_primes) will call each time a prime number is found
    int i = 0;
    Exchange x(
        [&](void * data) {
            Nan::Set(results, i, New<v8::Number>(*((int *) data)));
            i++;
       });

    // Calling the primesieve implementation, which executes and incrementally fills up the array with primes through the exchange object.
    generate_primes(under, (void*)&x);

    // Returning the data to JavaScript - which is done through the info object.
    info.GetReturnValue().Set(results);
    // At this point, control will be returned to our JavaScript.
}

//////// Register this function (CalculatePrimes) with V8 ////////

// Associates an exported “getPrimes” function with CalculatePrimes. It’s an initialization function that V8 will call when the addon is loaded.
NAN_MODULE_INIT(Init) {
    Nan::Set(target, New<String>("getPrimes").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(CalculatePrimes)).ToLocalChecked());
}

NODE_MODULE(addon, Init)

