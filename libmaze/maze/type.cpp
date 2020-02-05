#include <maze/type.h>

namespace maze {

const std::string to_string(const Type& type) {
  switch (type) {
    case Type::Null:
      return "null";
    case Type::Bool:
      return "bool";
    case Type::Int:
      return "int";
    case Type::Double:
      return "double";
    case Type::String:
      return "string";
    case Type::Array:
      return "array";
    case Type::Object:
      return "object";
    default:
      return "unknown";
  }
}

}  // namespace maze
