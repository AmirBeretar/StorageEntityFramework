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

#ifndef STORAGE_H
#define STORAGE_H

#include <vector>

#include "defines.h"
#include "field.h"
#include "condition.h"
#include "entityfactory.h"

template<class TEntity>
class SEF_Storage
{
public:
    SEF_Storage(SEF_EntityFactory<TEntity>* factory_) : factory(factory_) {}
    virtual ~SEF_Storage() {}
    virtual TEntity* getByID(SEF_ID id_) = 0;
    virtual std::vector<TEntity*> getByCondition(SEF_Condition<TEntity>* cond_) = 0;
    virtual void update(TEntity* entity_) = 0;
    virtual void remove(SEF_ID id_) = 0;
    virtual void insert(TEntity* entity_)
    {
        entity_->repository = this;
        entity_->id = generageID();
    }

protected:
    virtual SEF_ID generageID() = 0;

protected:
    SEF_EntityFactory<TEntity>* factory;
};

template<class TEntity, int TFieldID>
typename SEF_Field<TEntity, TFieldID>::type SEF_getFieldValue(TEntity* entity_, SEF_Storage<TEntity>* repository_);

template<class TEntity, int TFieldID>
void SEF_setFieldValue(TEntity* entity_, SEF_Storage<TEntity>* repository_, const typename SEF_Field<TEntity, TFieldID>::type& value_);

#endif // STORAGE_H
