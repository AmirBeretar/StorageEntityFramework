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

#ifndef ENTITY_H
#define ENTITY_H

#include "storage.h"

template<class TEntity>
class SEF_Entity
{
public:
    virtual ~SEF_Entity() {}

    template<int TFieldID>
    typename SEF_Field<TEntity, TFieldID>::type get()
    {
        return SEF_getFieldValue<TEntity, TFieldID>(static_cast<TEntity*>(this), repository);
    }

    SEF_ID getID() const
    {
        return id;
    }

protected:
    friend class SEF_Storage<TEntity>;

    SEF_ID id;
    SEF_Storage<TEntity>* repository;
};

#endif // ENTITY_H
