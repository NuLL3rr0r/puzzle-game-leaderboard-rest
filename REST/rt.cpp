#include <boost/filesystem/path.hpp>
#include <CoreLib/crypto.hpp>
#include <CoreLib/db.hpp>
#include <CoreLib/make_unique.hpp>
#include <CoreLib/log.hpp>
#include "rt.hpp"
#include "dbtables.hpp"

using namespace std;
using namespace NowruzPuzzle;

struct RT::Impl
{
    typedef std::unique_ptr<StorageStruct> Storage_ptr;
    typedef std::unique_ptr<CoreLib::Crypto> Crypto_ptr;
    typedef std::unique_ptr<CoreLib::DB> DB_ptr;
    typedef std::unique_ptr<NowruzPuzzle::DBTables> DBTables_ptr;

    std::mutex StorageMutex;
    Storage_ptr StorageInstance;

    std::mutex DBMutex;
    DB_ptr DBInstance;

    std::mutex DBTablesMutex;
    DBTables_ptr DBTablesInstance;

    std::mutex TokenClientMutex;
    Crypto_ptr TokenClientInstance;

    std::mutex TokenServerMutex;
    Crypto_ptr TokenServerInstance;

    Impl();
    ~Impl();
};

std::unique_ptr<RT::Impl> RT::s_pimpl = std::make_unique<RT::Impl>();

RT::StorageStruct *RT::Storage()
{
    lock_guard<mutex> lock(s_pimpl->StorageMutex);
    (void)lock;

    if (s_pimpl->StorageInstance == nullptr) {
        s_pimpl->StorageInstance = std::make_unique<RT::StorageStruct>();
    }

    return s_pimpl->StorageInstance.get();
}

CoreLib::DB *RT::DB()
{
    lock_guard<mutex> lock(s_pimpl->DBMutex);
    (void)lock;

    if (s_pimpl->DBInstance == nullptr) {
        static const std::string DB_FILE((boost::filesystem::path(Storage()->AppPath)
                                          / boost::filesystem::path("..")
                                          / boost::filesystem::path("db")
                                          / boost::filesystem::path(SCORES_DB_FILE_NAME)).string());
        CoreLib::DB::Vacuum(DB_FILE);
#ifdef CORELIB_STATIC
        DB::LoadSQLite3Driver();
#endif  // CORELIB_STATIC
        s_pimpl->DBInstance = std::make_unique<CoreLib::DB>(DB_FILE);
    }

    return s_pimpl->DBInstance.get();
}

NowruzPuzzle::DBTables *RT::DBTables()
{
    lock_guard<mutex> lock(s_pimpl->DBTablesMutex);
    (void)lock;

    if (s_pimpl->DBTablesInstance == nullptr) {
        s_pimpl->DBTablesInstance = std::make_unique<NowruzPuzzle::DBTables>();
    }

    return s_pimpl->DBTablesInstance.get();
}

CoreLib::Crypto *RT::TokenClient()
{
    lock_guard<mutex> lock(s_pimpl->TokenClientMutex);
    (void)lock;

    if (s_pimpl->TokenClientInstance == nullptr) {
        // Use this nice HEX/ASCII converter and your editor's replace dialog,
        // to create your own Key and IV.
        // http://www.dolcevie.com/js/converter.html

        // f;W07U*7-[5e6554
        static constexpr CoreLib::Crypto::Byte_t KEY[] = {
            0x66, 0x3b, 0x57, 0x30, 0x37, 0x55, 0x2a, 0x37, 0x2d, 0x5b, 0x35, 0x65, 0x36, 0x35, 0x35, 0x34
        };

        // K$,G!{B{a5<*NZ?b
        static constexpr CoreLib::Crypto::Byte_t IV[] = {
            0x4b, 0x24, 0x2c, 0x47, 0x21, 0x7b, 0x42, 0x7b, 0x61, 0x35, 0x3c, 0x2a, 0x4e, 0x5a, 0x3f, 0x62
        };

        s_pimpl->TokenClientInstance = std::make_unique<CoreLib::Crypto>(KEY, sizeof(KEY), IV, sizeof(IV));
    }

    return s_pimpl->TokenClientInstance.get();
}

CoreLib::Crypto *RT::TokenServer()
{
    lock_guard<mutex> lock(s_pimpl->TokenServerMutex);
    (void)lock;

    if (s_pimpl->TokenServerInstance == nullptr) {
        // Use this nice HEX/ASCII converter and your editor's replace dialog,
        // to create your own Key and IV.
        // http://www.dolcevie.com/js/converter.html

        // 783^61{!_KW38"w0
        static constexpr CoreLib::Crypto::Byte_t KEY[] = {
            0x37, 0x38, 0x33, 0x5e, 0x36, 0x31, 0x7b, 0x21, 0x5f, 0x4b, 0x57, 0x33, 0x38, 0x22, 0x77, 0x30
        };

        // MxU;{,-g*;f<8"25
        static constexpr CoreLib::Crypto::Byte_t IV[] = {
            0x4d, 0x78, 0x55, 0x3b, 0x7b, 0x2c, 0x2d, 0x67, 0x2a, 0x3b, 0x66, 0x3c, 0x38, 0x22, 0x32, 0x35
        };

        s_pimpl->TokenServerInstance = std::make_unique<CoreLib::Crypto>(KEY, sizeof(KEY), IV, sizeof(IV));
    }

    return s_pimpl->TokenServerInstance.get();
}

RT::Impl::Impl()
{

}

RT::Impl::~Impl()
{
    StorageInstance.reset();
    DBInstance.reset();
    TokenClientInstance.reset();
    TokenServerInstance.reset();
}

