/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Max Wipfli <max.wipfli@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/String.h"
#include "./AK/Vector.h"

namespace AK {

class LexicalPath {
public:
    explicit LexicalPath(String);

    bool is_absolute() const { return !m_string.is_empty() && m_string[0] == '/'; }
    String const& string() const { return m_string; }

    StringView dirname() const { return m_dirname; }
    StringView basename() const { return m_basename; }
    StringView title() const { return m_title; }
    StringView extension() const { return m_extension; }

    Vector<StringView> const& parts_view() const { return m_parts; }
    Vector<String> parts() const;

    bool has_extension(StringView) const;

    LexicalPath append(StringView) const;
    LexicalPath prepend(StringView) const;
    LexicalPath parent() const;

    static String canonicalized_path(String);
    static String absolute_path(String dir_path, String target);
    static String relative_path(StringView absolute_path, StringView prefix);

    template<typename... S>
    static LexicalPath join(StringView first, S&&... rest);

    static String dirname(String path);

    static String basename(String path);

    static String title(String path);

    static String extension(String path);

private:
    Vector<StringView> m_parts;
    String m_string;
    StringView m_dirname;
    StringView m_basename;
    StringView m_title;
    StringView m_extension;
};

template<>
struct Formatter<LexicalPath> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, LexicalPath const& value)
    {
        return Formatter<StringView>::format(builder, value.string());
    }
};

};

using AK::LexicalPath;
