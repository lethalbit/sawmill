# Compiler Plugins

Sawmill ships with a plugin for both [gcc](https://gcc.gnu.org/) and [clang](https://clang.llvm.org/) which add standards compliant attributes to make using sawmill easier, mimicking how [rust](https://www.rust-lang.org/)'s [attribute macros](https://doc.rust-lang.org/reference/procedural-macros.html#attribute-macros) work. Allow for the automatic instrumentation of a decorated function.

The plugins for both compilers are installed in `$PREFIX/share/sawmill/compiler_plugins`, and are suffixed with their respective compiler (e.g. `sawmill-gcc.so` and `sawmill-clang.so`). Throughout the rest of the documentation, the location of the plugins will be referred to as `$SAWMILL_PLUGINS` for brevity.

## Language Extensions

The primary language extension provided by sawmill is the `[[sawmill::instrument]]` attribute. This signals the compiler that has the plugin loaded, to automatically construct a [`slice`](./api/slice/index.md) and enter it in the prelude of the annotated function, and exit it in the epilogue of the function.

By default the automatically instrumented slice will have the functions name, and will automatically register any function parameters as metadata to be recorded.

A simple example would be as follows:

```cpp

[[sawmill::instrument]]
int foo(int a, int b) {
	sawmill::event(sawmill::Level::Debug, "Doing math");
	return a*2 + b*3;
}

```

In addition to this, you may pass arguments to the `[[sawmill::instrument]]` attribute to specify options for the slice construction.

For example, specifying a slice with a different name and level would look like this:

```cpp

[[sawmill::instrument({"name", "bar"}, {"level", sawmill::Level::Trace})]]
void baz(int a) {
	/* Does some work */
	sawmill::event(sawmill::Level::Debug, "Done!");
}

```

Unfortunately the syntax to specify arbitrary arguments to the attribute is messy, but it's the only way to provide the functionality to emulate the rust attribute macros.

```{warning}
With clang there is a hard limit of 15 possible arguments to the attribute. If you ***really*** need to
pass more than 15 arguments, wrap them in an outer initializer list
```

## Usage

To use the language extensions, simply invoke your chosen compiler with the correct sawmill plugin specified.

### GCC

To use GCC with the sawmill extensions, simply pass the `-fplugin=$SAWMILL_PLUGINS/sawmill-gcc.so` argument to your `g++` invocations.

### Clang

To use Clang with the sawmill extensions, simply pass the `-fplugin=$SAWMILL_PLUGINS/sawmill-clang.so` argument to your `clang++` invocations.
