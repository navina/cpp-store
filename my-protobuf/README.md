# Protocol Buffers

*Ref:* _[Google Developers Tutorial (c++)](https://developers.google.com/protocol-buffers/docs/cpptutorial)_

## Files Generated)

* For each `*.proto` file, `protoc` command generates a `*.pb.h` header file, which declares the generated classes 
and `*/pb.cc` implementation files for the classes.

## Code Generation

### Message Fields
* For each field, generates getters (`get_`), setters (`set_`) and `clear_` method with exact same field name.
* String fields have extra methods:
  * `mutable_` method - getter that returns a direct pointer to the string
  * extra setter with a string argument
* Repeated fields have methods for:
  * `_size` - size of the set
  * `$fieldName(int index)` - Getter /Accessor of a field at index `index`
  * `mutable_$fieldName` - Update handlers
* Nested Types -> `$parentType::$childType`

### Standard Message Methods
* For each message class, there are some standard methods:
  * `bool IsInitialized() const;` checks if all required fields aeset
  * `string DebugString() const;` retuhuman readable form of the message
  * `void CopyFrom(const $typeName& from);` Overrides message with given message's value
  * `void Clear();` Clears all the elements back to empty state
* The above methods and other I/O methods implement `Message` interface in protobuf

### Parsing and Serialization
* `bool SerializeToString(string* output) const;` -> serialized to bytes, not text (`string` is used as a container)
* `bool ParseFromString(const string& data);`
* `bool SerializeToOstream(ostream* output) const;` 
* `bool ParseFromIstream(istream* input);`

