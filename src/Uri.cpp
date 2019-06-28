// Copyright (c) 2019 shaqsnake. All rights reserved.
/**
 * @Author: shaqsnake
 * @Email: shaqsnake@gmail.com
 * @Date: 2019-06-27 09:17:12
 * @LastEditTime: 2019-06-28 10:18:14
 * @Description: An implementation of class uri::Uri.
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