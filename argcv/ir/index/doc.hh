#ifndef ARGCV_IR_INDEX_DOC_HH
#define ARGCV_IR_INDEX_DOC_HH

#include <string>

namespace argcv {
namespace ir {
namespace index {
class doc {
public:
    doc(const std::string& id) : id(id){}
    virtual ~doc();

private:
    const std::string id;
};
}
}
}  // namespace argcv::ir::index

#endif  //  ARGCV_IR_INDEX_DOC_HH
