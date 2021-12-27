// Output of running the example:
//
//   component type: Position
//     props:
//       x: 0.000000
//       y: 0.000000
//   component type: Name
//     props:
//       first: First
//       last: Last (example flag set)
// 


#include "meta.hh"

#include <string>


// Register component types by wrapping the struct name in `Comp(...)`

struct Comp(Position) {
  // Register reflectable fields ('props') using the `Prop` macro
  Prop(float, x) = 0;
  Prop(float, y) = 0;
};

struct Comp(Name) {
  Prop(std::string, first) = "First";

  // Props can have additional attributes, see the `PropAttribs` type. You can customize and add
  // your own attributes there.
  Prop(std::string, last, .exampleFlag = true) = "Last";

  int internal = 42; // This is a non-prop field that doesn't show up in reflection. IMPORTANT NOTE:
                     // All such non-prop fields must be at the end of the struct, with all props at
                     // the front. Mixing props and non-props in the order is not allowed.
};

// After all compnonent types are defined, this macro must be called to be able to use
// `forEachComponentType` to iterate all component types
UseComponentTypes();


// Define `print` functions so we can print a prop of any type. Since the type is statically
// available when reflecting props we can just use regular C++ overloading.

void print(const float &val) {
  std::printf("%f", val);
}

void print(const std::string &val) {
  std::printf("%s", val.c_str());
}


// Main example. Make default values of each component type and print their props.

int main() {
  forEachComponentType([&]<typename T>() {
    // Print the type name. It's an `std::string_view` into a larger string so we use the `%.*s`
    // form of `std::printf`.
    constexpr auto typeName = getTypeName<T>();
    std::printf("component type: %.*s\n", int(typeName.size()), typeName.data());

    // Make a default value of the component and print its props
    T val;
    std::printf("  props:\n");
    forEachProp(val, [&](auto propTag, auto &propVal) {
      // `propTag` is of a distinct type per prop, and holds attributes including the name. We print
      // the name first. The name is an `std::string_view` but the whole string it points to is the
      // name so we can print its data directly.
      std::printf("    %s: ", propTag.attribs.name.data());

      // Call one of the overloaded `print` functions above to print the value itself
      print(propVal);

      // Now we print if `exampleFlag` is set. Note that we can check attributes `constexpr`!
      if constexpr (propTag.attribs.exampleFlag) {
        std::printf(" (example flag set)");
      }

      std::printf("\n");
    });
  });
  return 0;
}
