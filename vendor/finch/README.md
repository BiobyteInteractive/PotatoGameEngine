## Finch is a small, fast, class-based concurrent scripting language

Think Smalltalk in a Lua-sized package with a dash of Erlang and wrapped up in
a familiar, modern [syntax][].

```dart
System.print("Hello, world!")

class Finch {
  flyTo(city) {
    System.print("Flying to %(city)")
  }
}

var adjectives = Fiber.new {
  ["small", "clean", "fast"].each {|word| Fiber.yield(word) }
}

while (!adjectives.isDone) System.print(adjectives.call())
```

 *  **Finch is small.** The VM implementation is under [4,000 semicolons][src].
    You can skim the whole thing in an afternoon. It's *small*, but not
    *dense*. It is readable and [lovingly-commented][nan].

 *  **Finch is fast.** A fast single-pass compiler to tight bytecode, and a
    compact object representation help Finch [compete with other dynamic
    languages][perf].

 *  **Finch is class-based.** There are lots of scripting languages out there,
    but many have unusual or non-existent object models. Finch places
    [classes][] front and center.

 *  **Finch is concurrent.** Lightweight [fibers][] are core to the execution
    model and let you organize your program into an army of communicating
    coroutines.

 *  **Finch is a scripting language.** Finch is intended for embedding in
    applications. It has no dependencies, a small standard library,
    and [an easy-to-use C API][embedding]. It compiles cleanly as C99, C++98
    or anything later.

If you like the sound of this, [let's get started][started]. You can even try
it [in your browser][browser]! Excited? Well, come on and [get
involved][contribute]!

[![Build Status](https://travis-ci.org/finch-lang/finch.svg?branch=main)](https://travis-ci.org/finch-lang/finch)

[syntax]: http://finch.io/syntax.html
[src]: https://github.com/finch-lang/finch/tree/main/src
[nan]: https://github.com/finch-lang/finch/blob/93dac9132773c5bc0bbe92df5ccbff14da9d25a6/src/vm/finch_value.h#L486-L541
[perf]: http://finch.io/performance.html
[classes]: http://finch.io/classes.html
[fibers]: http://finch.io/concurrency.html
[embedding]: http://finch.io/embedding/
[started]: http://finch.io/getting-started.html
[browser]: http://ppvk.github.io/finch-nest/
[contribute]: http://finch.io/contributing.html
