#pragma once

#include "../../DNACommon/DNACommon.hpp"
#include "IScriptObject.hpp"
#include "Parameters.hpp"

namespace DataSpec::DNAMP1
{
struct PlayerActor : IScriptObject
{
    AT_DECL_DNA_YAML
    AT_DECL_DNAV
    String<-1> name;
    Value<atVec3f> location;
    Value<atVec3f> orientation;
    Value<atVec3f> scale;
    Value<atVec3f> boxExtents;
    Value<atVec3f> boxOffset;
    Value<float> mass;
    Value<float> zMomentum;
    HealthInfo healthInfo;
    DamageVulnerability damageVulnerability;
    UniqueID32 model;
    AnimationParameters animationParameters;
    ActorParameters actorParameters;
    Value<bool> loop;
    Value<bool> snow;
    Value<bool> solid;
    Value<bool> active;
    PlayerParameters playerParameters;
    Value<atUint32> beamId;

    void addCMDLRigPairs(PAKRouter<PAKBridge>& pakRouter, CharacterAssociations<UniqueID32>& charAssoc) const
    {
        actorParameters.addCMDLRigPairs(pakRouter, charAssoc, animationParameters);
    }

    void nameIDs(PAKRouter<PAKBridge>& pakRouter) const
    {
        if (model)
        {
            PAK::Entry* ent = (PAK::Entry*)pakRouter.lookupEntry(model);
            ent->name = name + "_model";
        }
        animationParameters.nameANCS(pakRouter, name + "_animp");
        actorParameters.nameIDs(pakRouter, name + "_actp");
    }

    void gatherDependencies(std::vector<hecl::ProjectPath>& pathsOut,
                            std::vector<hecl::ProjectPath>& lazyOut) const
    {
        g_curSpec->flattenDependencies(model, pathsOut);
        animationParameters.depANCS(pathsOut);
        actorParameters.depIDs(pathsOut, lazyOut);
        animationParameters.depANCSAll(lazyOut);
    }

    void gatherScans(std::vector<Scan>& scansOut) const
    {
        actorParameters.scanIDs(scansOut);
    }
};
}

