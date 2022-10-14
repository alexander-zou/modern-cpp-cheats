
/**
 * 
 * @File   : filesystem.cpp   
 * @Author : jiachen.zou@jiiov.com   
 * @Date   : 2022-10-14 10:52    (+0800)   
 * @Brief  :  
 * 
**/

#include <filesystem>

#include <iostream>

constexpr char ALIGN[] = "                                ";
#define SHOW( x) std::cout << #x << " :" << (ALIGN+sizeof( #x)) << ( x) << std::endl

int main() {
    namespace fs = std::filesystem;

    // the path class:

    SHOW( fs::current_path());

    fs::path me = "./filesystem.cpp";
    SHOW( me);
    SHOW( me.c_str());
    SHOW( me.string());
    SHOW( fs::exists( me));
    SHOW( fs::is_regular_file( me));
    SHOW( fs::is_directory( me));
    SHOW( fs::absolute( me));
    SHOW( fs::file_size( me));  // in Bytes
    SHOW( me.parent_path());
    SHOW( me.filename());   // note that filename() returns path instance.
    SHOW( me.stem());       // note that stem() returns path instance.
    SHOW( me.extension());  // note that extension() returns path instance.
    SHOW( me.replace_extension( ".cc"));
    SHOW( me += ".bak");

    fs::path dir = fs::absolute( ".");
    SHOW( dir);
    SHOW( dir == me.parent_path());
    SHOW( dir / "somefile.txt");    // there's also operator/=()

    // Travel directory:

    std::cout << "List of " << dir.string() << ":\n";
    for ( auto &it : fs::directory_iterator( dir))
        std::cout << "\t" << it.path().filename().string() << std::endl;

    // File Operations:

    // void rename( path const &old, path const &new); // rename/move file/directory 
    
    // bool copy( path const &from, path const &to); // copy file/directory
    // bool copy( path const &from, path const &to, fs::copy_options opts);
    //          opts is like 'copy_options::recursive | copy_options::skip_existing',
    //          see: https://en.cppreference.com/w/cpp/filesystem/copy_options for more.

    // bool create_directory( path const &p); // basically POSIX mkdir()
    // bool create_directories( path const &p); // "mkdir -p" in Shell or "mkdirs()" in Java

    // bool remove( path const &p); // basically POSIX remove(), delete file or empty directory
    // uintmax_t remove_all( path const &p); // delete file tree, returns number of entity deleted

    return 0;
}


/*  End of 'filesystem.cpp' */

