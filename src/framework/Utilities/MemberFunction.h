/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MEMBERFUNCTION_H
#define MEMBERFUNCTION_H

#include <algorithm>

template<typename ParamType>
struct MemberFunction
{
    struct HolderBase
    {
        virtual void call(ParamType) = 0;
        virtual HolderBase* clone() const = 0;
        virtual ~HolderBase() {}
    };
    template<typename ObjType, typename ActualParamType>
    struct Holder : HolderBase
    {
        Holder(ObjType& obj, void (ObjType::*func)(ActualParamType)):
            obj(obj), func(func)
        {}
        void call(ParamType p)
        {
            (obj.*func)(static_cast<ActualParamType>(p));
        }
        HolderBase* clone() const
        {
            return new Holder<ObjType, ActualParamType>(obj, func);
        }
        ObjType& obj;
        void (ObjType::*func)(ActualParamType);
    };
    template<typename ObjType, typename ActualParamType>
    MemberFunction(ObjType& obj, void (ObjType::*func)(ActualParamType)):
        impl(new Holder<ObjType, ActualParamType>(obj, func))
    {}
    ~MemberFunction() { delete impl; }
    MemberFunction(const MemberFunction& other):
        impl(other.impl ? other.impl->clone() : 0)
    {}
    MemberFunction& operator=(MemberFunction other)
    {
        std::swap(other.impl, impl);
        return *this;
    }

    void operator()(ParamType p) { impl->call(p); }

    operator size_t() const { return (size_t)this; }

    HolderBase* impl;
};

template<typename ParamType> bool operator==(const MemberFunction<ParamType>& x, const MemberFunction<ParamType> y) {
    return (x.impl == y.impl);
}

#endif
