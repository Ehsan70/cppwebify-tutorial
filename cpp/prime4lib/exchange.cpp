#include "exchange.h"

/*
The pass function accepts a pointer to an exchange object (void *, since the exchange class
won’t be visible to C callers). Within the definition, found in exchange.cpp, we see that this
pointer is cast back to an exchange object and the send method is called
*/
void pass(void * exchanger, int data) {
    Exchange * x = (Exchange *) exchanger;
    x->send(data);
}
