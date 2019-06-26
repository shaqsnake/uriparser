#ifndef URI_HPP
#define URI_HPP

#include <memory>

namespace uri {

class Uri {
public:
    Uri();
    ~Uri();
    Uri(const Uri &) = delete;
    Uri(Uri &&) = delete;
    Uri &operator=(const Uri &) = delete;
    Uri &operator=(Uri &&) = delete;

private:
    struct Impl;
    std::unique_ptr<struct Impl> impl_;
};

} // namespace uri
#endif
