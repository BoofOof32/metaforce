#ifndef __URDE_IVPARAMOBJ_HPP__
#define __URDE_IVPARAMOBJ_HPP__

#include <memory>
#include "IObj.hpp"

namespace urde
{

class IVParamObj : public IObj
{
public:
    virtual ~IVParamObj() {}
};

class CVParamTransfer
{
    std::shared_ptr<IVParamObj> m_ref;
public:
    CVParamTransfer() = default;
    CVParamTransfer(IVParamObj* obj) : m_ref(obj) {}
    CVParamTransfer(const CVParamTransfer& other) : m_ref(other.m_ref) {}
    IVParamObj* GetObj() const {return m_ref.get();}
    CVParamTransfer ShareTransferRef() {return CVParamTransfer(*this);}

    static CVParamTransfer Null() {return CVParamTransfer();}
};

template<class T>
class TObjOwnerParam : public IVParamObj
{
    T m_param;
protected:
    ~TObjOwnerParam() {}
public:
    TObjOwnerParam(T&& obj) : m_param(std::move(obj)) {}
    T& GetParam() {return m_param;}
};

}

#endif // __URDE_IVPARAMOBJ_HPP__
