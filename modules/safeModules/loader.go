package safemodules

import (
    "plugin"
)

func LoadModule() {
    // Load plugin
    plug, err := plugin.Open("some.so")
    if err != nil {
        panic(err)
    }
	



    // // Lookup the symbol
    // sym, err := plug.Lookup("Some")
    // if err != nil {
    //     panic(err)
    // }
    //
    // // Type assert the symbol to a function
    // someFunc, ok := sym.(func(string))
    // if !ok {
    //     panic("unexpected type from module symbol")
    // }
    //
    // // Call the function
    // someFunc("Hello from main")
}
