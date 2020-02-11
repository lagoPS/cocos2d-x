﻿// automatically generated by the FlatBuffers compiler, do not modify

#pragma once

#include "flatbuffers/flatbuffers.h"

namespace flatbuffers
{
    struct LanguageItem;
    struct LanguageSet;

    struct LanguageItem : private flatbuffers::Table
    {
        const flatbuffers::String* key() const { return GetPointer<const flatbuffers::String*>(4); }
        const flatbuffers::String* value() const { return GetPointer<const flatbuffers::String*>(6); }
        bool Verify(flatbuffers::Verifier& verifier) const
        {
            return VerifyTableStart(verifier) && VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* key */) && verifier.Verify(key()) &&
                VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* value */) && verifier.Verify(value()) && verifier.EndTable();
        }
    };

    struct LanguageItemBuilder
    {
        flatbuffers::FlatBufferBuilder& fbb_;
        flatbuffers::uoffset_t start_;
        void add_key(flatbuffers::Offset<flatbuffers::String> key) { fbb_.AddOffset(4, key); }
        void add_value(flatbuffers::Offset<flatbuffers::String> value) { fbb_.AddOffset(6, value); }
        LanguageItemBuilder(flatbuffers::FlatBufferBuilder& _fbb)
        : fbb_(_fbb)
        {
            start_ = fbb_.StartTable();
        }
        LanguageItemBuilder& operator=(const LanguageItemBuilder&);
        flatbuffers::Offset<LanguageItem> Finish()
        {
            auto o = flatbuffers::Offset<LanguageItem>(fbb_.EndTable(start_, 2));
            return o;
        }
    };

    inline flatbuffers::Offset<LanguageItem> CreateLanguageItem(flatbuffers::FlatBufferBuilder& _fbb, flatbuffers::Offset<flatbuffers::String> key = 0,
                                                                flatbuffers::Offset<flatbuffers::String> value = 0)
    {
        LanguageItemBuilder builder_(_fbb);
        builder_.add_value(value);
        builder_.add_key(key);
        return builder_.Finish();
    }

    struct LanguageSet : private flatbuffers::Table
    {
        const flatbuffers::Vector<flatbuffers::Offset<LanguageItem>>* languageItems() const
        {
            return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<LanguageItem>>*>(4);
        }
        bool Verify(flatbuffers::Verifier& verifier) const
        {
            return VerifyTableStart(verifier) && VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* languageItems */) && verifier.Verify(languageItems()) &&
                verifier.VerifyVectorOfTables(languageItems()) && verifier.EndTable();
        }
    };

    struct LanguageSetBuilder
    {
        flatbuffers::FlatBufferBuilder& fbb_;
        flatbuffers::uoffset_t start_;
        void add_languageItems(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<LanguageItem>>> languageItems) { fbb_.AddOffset(4, languageItems); }
        LanguageSetBuilder(flatbuffers::FlatBufferBuilder& _fbb)
        : fbb_(_fbb)
        {
            start_ = fbb_.StartTable();
        }
        LanguageSetBuilder& operator=(const LanguageSetBuilder&);
        flatbuffers::Offset<LanguageSet> Finish()
        {
            auto o = flatbuffers::Offset<LanguageSet>(fbb_.EndTable(start_, 1));
            return o;
        }
    };

    inline flatbuffers::Offset<LanguageSet>
    CreateLanguageSet(flatbuffers::FlatBufferBuilder& _fbb, flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<LanguageItem>>> languageItems = 0)
    {
        LanguageSetBuilder builder_(_fbb);
        builder_.add_languageItems(languageItems);
        return builder_.Finish();
    }

    inline const LanguageSet* GetLanguageSet(const void* buf) { return flatbuffers::GetRoot<LanguageSet>(buf); }

    inline bool VerifyLanguageSetBuffer(flatbuffers::Verifier& verifier) { return verifier.VerifyBuffer<LanguageSet>(); }

    inline void FinishLanguageSetBuffer(flatbuffers::FlatBufferBuilder& fbb, flatbuffers::Offset<LanguageSet> root) { fbb.Finish(root); }

} // namespace flatbuffers