#pragma once

#include <AK/Forward.h>
#include <AK/HashMap.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <AK/String.h>
#include <AK/Vector.h> 

namespace Core {

class ConfigFile : public RefCounted<ConfigFile> {
public:
    enum class AllowWriting {
        Yes,
        No,
    };

    static ErrorOr<NonnullRefPtr<ConfigFile>> open_for_lib(String const& lib_name, AllowWriting = AllowWriting::No);
    static ErrorOr<NonnullRefPtr<ConfigFile>> open_for_app(String const& app_name, AllowWriting = AllowWriting::No);
    static ErrorOr<NonnullRefPtr<ConfigFile>> open_for_system(String const& app_name, AllowWriting = AllowWriting::No);
    static ErrorOr<NonnullRefPtr<ConfigFile>> open(String const& filename, AllowWriting = AllowWriting::No);
    static ErrorOr<NonnullRefPtr<ConfigFile>> open(String const& filename, int fd);
    ~ConfigFile();
};

}