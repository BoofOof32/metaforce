#pragma once

#include "World/CPatterned.hpp"

namespace urde
{
class CDamageInfo;

namespace MP1
{

class CNewIntroBoss : public CPatterned
{
public:
    DEFINE_PATTERNED(NewIntroBoss)
    CNewIntroBoss(TUniqueId uid, std::string_view name, const CEntityInfo& info,
                  const zeus::CTransform& xf, CModelData&& mData, const CPatternedInfo& pInfo,
                  const CActorParameters& actParms, float, u32, const CDamageInfo& dInfo,
                  u32, u32, u32, u32);

    void Accept(IVisitor &visitor);
};

}
}

