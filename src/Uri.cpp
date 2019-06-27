/**
 * @file Uri.cpp
 * @brief An implementation of Class uri::Uri.
 * @author shaqsnake
 * @email shaqsnake@gmail.com
 */

#include <uriparser/Uri.hpp>

namespace uri {
/**
 * The concrete implemetation of Uri class.
 */
struct Uri::Impl {};

/**
 * Constructor by default.
 */
Uri::Uri() : impl_(new Impl) {}

/**
 * Destructor.
 */
Uri::~Uri() = default;

} // namespace uri