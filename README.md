# meta

Static reflection tools for C++. I use it with EnTT but it can work with anything. The main features the library provides are:
- Registering types and then being able to iterate over them statically.
- Get the name of a type as a `constexpr` `std::string_view`.
- Iterate over fields of a `struct`, also attach attributes to them and get attribute values `constexpr`.

Check out the [example](./example.cc)!
