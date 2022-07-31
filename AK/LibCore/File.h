#pragma once

#include "./AK/Error.h"
#include "./AK/String.h"

namespace Core {

// FIXME: this shouldn't be here
enum class OpenMode {
    NotOpen = 0,
    ReadOnly = 1,
    WriteOnly = 2,
    ReadWrite = 3,
    Append = 4,
    Truncate = 8,
    MustBeNew = 16,
    KeepOnExec = 32,
};

class File final {
public:
    bool is_directory() const { return false; }
    static bool is_directory(String const& filename) { return false; }

    static bool exists(String const& filename) { return false; }

    virtual bool open(OpenMode) override;

    enum class ShouldCloseFileDescriptor {
        No = 0,
        Yes
    };
    bool open(int fd, OpenMode, ShouldCloseFileDescriptor);
};

}
