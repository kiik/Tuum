
/*
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include <iostream>
*/

#include "tuum_fs.hpp"

#include "fs/tuum_file.hpp"
#include "fs/tuum_dbfile.hpp"

//namespace fs = boost::filesystem;

namespace tuum {

  File* NewFile(std::string path, File::Type type)
  {
    File::file_t ft;
    ft = {path, type};

    switch(type) {
      case File::T_Disk:
        return new File(ft);
      case File::T_Dbase:
        return new DBFile(ft);
    }

    return new File(ft);
  }

  int run_file_tests() {
    File* pipe_src = NewFile("assets/test2.ppl", File::T_Dbase);

    pipe_src->write("DATA\n", File::M_Append);

    std::string source = "YYY";
    if(pipe_src->edit(source, 5, File::M_Append) < 0) {
      RTXLOG("File write test failed!", LOG_ERR);
    } else {
      RTXLOG("File write test success.");
    }

    if(pipe_src->read(source) < 0) {
      RTXLOG("File read test failed!", LOG_ERR);
    } else {
      printf("\"%s\"\n", source.c_str());
      RTXLOG("File read test success.");
    }

    delete(pipe_src);
  }

  /*
  int ls(const char* path)
  {
    boost::progress_timer t( std::clog );

    fs::path full_path( fs::initial_path<fs::path>() );

    if (path != nullptr)
      full_path = fs::system_complete( fs::path( path ) );
    else {
      std::cout << "\nusage:   simple_ls [path]" << std::endl;
      return -1;
    }

    unsigned long file_count = 0;
    unsigned long dir_count = 0;
    unsigned long other_count = 0;
    unsigned long err_count = 0;

    if ( !fs::exists( path ) )
    {
      std::cout << "\nNot found: " << full_path.file_string() << std::endl;
      return -1;
    }

    if ( fs::is_directory( full_path ) )
    {
      std::cout << "\nIn directory: "
                << full_path.directory_string() << "\n\n";
      fs::directory_iterator end_iter;
      for ( fs::directory_iterator dir_itr( full_path );
            dir_itr != end_iter;
            ++dir_itr )
      {
        try
        {
          if ( fs::is_directory( dir_itr->status() ) )
          {
            ++dir_count;
            std::cout << dir_itr->path().filename() << " [directory]\n";
          }
          else if ( fs::is_regular_file( dir_itr->status() ) )
          {
            ++file_count;
            std::cout << dir_itr->path().filename() << "\n";
          }
          else
          {
            ++other_count;
            std::cout << dir_itr->path().filename() << " [other]\n";
          }

        }
        catch ( const std::exception & ex )
        {
          ++err_count;
          std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
        }
      }
      std::cout << "\n" << file_count << " files\n"
                << dir_count << " directories\n"
                << other_count << " others\n"
                << err_count << " errors\n";
    }
    else // must be a file
    {
      std::cout << "\nFound: " << full_path.file_string() << "\n";
    }
  }*/

}
