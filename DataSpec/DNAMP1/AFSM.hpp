#ifndef _DNAMP1_AFSM_HPP_
#define _DNAMP1_AFSM_HPP_

#include <Athena/FileWriter.hpp>
#include "../DNACommon/DNACommon.hpp"
#include "DNAMP1.hpp"

namespace DataSpec
{
namespace DNAMP1
{
struct AFSM : public BigYAML
{
    DECL_YAML
    Value<atUint32> stateCount;
    Vector<String<-1>, DNA_COUNT(stateCount)> stateNames;
    Value<atUint32> triggerCount;

    struct State : public BigYAML
    {
        DECL_YAML
        Value<atUint32> transitionCount;
        struct Transition : public BigYAML
        {
            Delete _d;
            Value<atUint32> triggerCount;

            struct Trigger : public BigYAML
            {
                Delete _d;
                bool first = false;
                String<-1> name;
                Value<float> parameter;
                Value<atUint32> targetState;
                void read(Athena::io::IStreamReader& __dna_reader)
                {
                    /* name */
                    name = __dna_reader.readString(-1);
                    /* parameter */
                    parameter = __dna_reader.readFloatBig();
                    if (first)
                    {
                        /* targetState */
                        targetState = __dna_reader.readUint32Big();
                    }
                }

                void write(Athena::io::IStreamWriter& __dna_writer) const
                {
                    /* name */
                    __dna_writer.writeString(name, -1);
                    /* parameter */
                    __dna_writer.writeFloatBig(parameter);
                    if (first)
                    {
                        /* targetState */
                        __dna_writer.writeUint32Big(targetState);
                    }
                }

                void read(Athena::io::YAMLDocReader& __dna_docin)
                {
                    /* name */
                    name = __dna_docin.readString("name");
                    /* parameter */
                    parameter = __dna_docin.readFloat("parameter");
                    if (first)
                    {
                        /* targetState */
                        targetState = __dna_docin.readUint32("targetState");
                    }
                }

                void write(Athena::io::YAMLDocWriter& __dna_docout) const
                {
                    /* name */
                    __dna_docout.writeString("name", name);
                    /* parameter */
                    __dna_docout.writeFloat("parameter", parameter);
                    if (first)
                    {
                        /* targetState */
                        __dna_docout.writeUint32("targetState", targetState);
                    }
                }

                static const char* DNAType()
                {
                    return "Retro::DNAMP1::AFSM::Transition::Trigger";
                }

                size_t binarySize(size_t __isz) const
                {
                    __isz += name.size() + 1;
                    return __isz + (first ? 8 : 4);
                }
            };

            Vector<Trigger, DNA_COUNT(triggerCount)> triggers;

            void read(Athena::io::IStreamReader& __dna_reader)
            {
                /* triggerCount */
                triggerCount = __dna_reader.readUint32Big();
                int i = 0;
                /* triggers */
                __dna_reader.enumerate<Trigger>(triggers, triggerCount,
                                                [&](Athena::io::IStreamReader& in, Trigger& tr){
                    tr.first = i == 0;
                    tr.read(in);
                    i++;
                });
            }

            void write(Athena::io::IStreamWriter& __dna_writer) const
            {
                /* triggerCount */
                __dna_writer.writeInt32Big(triggerCount);
                /* triggers */
                __dna_writer.enumerate(triggers);
            }

            void read(Athena::io::YAMLDocReader& __dna_docin)
            {
                int i = 0;
                /* triggers */
                triggerCount = __dna_docin.enumerate<Trigger>("triggers", triggers,
                [&](Athena::io::YAMLDocReader& in, Trigger& tr){
                    tr.first = i == 0;
                    tr.read(in);
                    i++;
                });
            }

            void write(Athena::io::YAMLDocWriter& __dna_docout) const
            {
                /* triggers */
                __dna_docout.enumerate("triggers", triggers);
            }

            static const char* DNAType()
            {
                return "Retro::DNAMP1::AFSM::Transition";
            }

            size_t binarySize(size_t __isz) const
            {
                __isz = __EnumerateSize(__isz, triggers);
                return __isz + 4;
            }
        };

        Vector<Transition, DNA_COUNT(transitionCount)> transitions;
    };

    Vector<State, DNA_COUNT(stateCount)> states;

    static bool Extract(PAKEntryReadStream& rs, const HECL::ProjectPath& outPath)
    {
        AFSM afsm;
        afsm.read(rs);
        FILE* fp = HECL::Fopen(outPath.getAbsolutePath().c_str(), _S("wb"));
        afsm.toYAMLFile(fp);
        fclose(fp);
        return true;
    }
};
}
}

#endif // _RETRO_AFSM_HPP_
