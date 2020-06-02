/*****************************************************************************
MIT License

Copyright © 2020 Amir Beretar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef JSON_H
#define JSON_H

#include <string>

#include "field.h"

#define SEF_JSON_FIELD(fieldid_) SEF_JSON::impl::FieldGetter<fieldid_>(#fieldid_)

namespace SEF_JSON
{

template<class TEntity, class ... Args>
std::string convert(TEntity* entity_, Args ... args_);

template<typename T>
inline std::string toString(const T& t_) { return std::to_string(t_); }

template<>
inline std::string toString<std::string>(const std::string& str_) { return str_; }

namespace impl
{

template<int TFieldID>
struct FieldGetter
{
    FieldGetter(const char* key_) : key(key_){}

    template<class TEntity>
    typename SEF_Field<TEntity, TFieldID>::type get(TEntity* entity_) const
    {
        return entity_-> template get<TFieldID>();
    }

    const char* key;
};

template<class TEntity, class TGetter>
std::string convert(TEntity* entity_, const TGetter& getter_)
{
    std::string value = toString(getter_. template get<TEntity>(entity_));
    return std::string("   \"") + std::string(getter_.key) + std::string("\": ") + value;
}

template<class TEntity, class TGetter, class ... Args>
std::string convert(TEntity* entity_, const TGetter& getter_, Args ... args_)
{
    std::string result = convert<TEntity, TGetter>(entity_, getter_) + '\n';
    return result + convert<TEntity, Args ... >(entity_, args_ ...);
}

} // namespace impl

template<class TEntity, class ... Args>
std::string convert(TEntity* entity_, Args ... args_)
{
    return std::string("{\n") + impl::convert<TEntity, Args ... >(entity_, args_ ...) + std::string("\n}\n");
}

} // namespace SEF_JSON

#endif // JSON_H
