#ifndef ARGCV_IR_INDEX_INDEX_HH
#define ARGCV_IR_INDEX_INDEX_HH

#include <string>

namespace argcv {
namespace ir {
namespace index {
class index {
public:
    index(const std::string& path) : path(path) {}
    ~index() {}

private:
    const std::string path;
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_INDEX_HH
