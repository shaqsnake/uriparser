#include <uriparser/Uri.hpp>

namespace uri {
struct Uri::Impl {};

Uri::~Uri() = default;

Uri::Uri() : impl_(new Impl) {}

} // namespace uri