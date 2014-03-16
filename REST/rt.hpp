#ifndef RT_HPP
#define RT_HPP


#include <memory>
#include <mutex>

namespace CoreLib {
    class Crypto;
    class DB;
}

namespace NowruzPuzzle {
    class DBTables;
    class RT;
}

class NowruzPuzzle::RT
{
public:
    struct StorageStruct
    {
        std::string AppPath;
    };

private:
    struct Impl;
    static std::unique_ptr<Impl> s_pimpl;

public:
    static StorageStruct *Storage();
    static CoreLib::DB *DB();
    static NowruzPuzzle::DBTables *DBTables();
    static CoreLib::Crypto *TokenClient();
    static CoreLib::Crypto *TokenServer();
};


#endif /* RT_HPP */

