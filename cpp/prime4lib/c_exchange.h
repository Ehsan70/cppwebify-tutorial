
/*

    This should not be included directly from C++ code.  Instead, 
    always include exchange.h

    C code cannot include exchange.h, and should only include this file.

    Using _exchangeclass a guard because g++ on Mac wasn't properly
    setting the _cplusplus definition!

*/

/*
The header exchange.h, which declares the exchange class defines the _exchangeclass symbol. 
so the first line is just detecting if that symbol is already there. 
If it is, the pass function - which will be called from C - is wrapped in an extern block.
*/
#ifdef _exchangeclass
extern "C" {
#endif

void pass(void * exchanger, int data);

#ifdef _exchangeclass
}
#endif

