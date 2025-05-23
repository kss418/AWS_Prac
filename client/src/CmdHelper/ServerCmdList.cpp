#include "../../include/CmdHelper.hpp"
#include "../../include/Session.hpp"
#include "../../include/ServerFsHelper.hpp"
#include <iostream>

void CmdHelper::server_cd(const std::vector<std::string>& arg){
    if(arg.size() == 1){
        std::cout << "인자가 없습니다." << std::endl;
        return;
    }
    auto& fs = ServerFsHelper::get_instance();
    fs.cd(arg[1], m_io_context);
}

void CmdHelper::server_mkdir(const std::vector<std::string>& arg){
    if(arg.size() == 1){
        std::cout << "인자가 없습니다." << std::endl;
        return;
    }
    auto& fs = ServerFsHelper::get_instance();
    fs.mkdir(arg[1], m_io_context);
}

void CmdHelper::server_rmdir(const std::vector<std::string>& arg){

}

void CmdHelper::server_ls(){
    auto& fs = ServerFsHelper::get_instance();
    for(auto& [file_name, is_dir] : fs.ls(m_io_context)){

    }
}

void CmdHelper::set_download_file(const std::vector<std::string>& arg){

}

void CmdHelper::set_upload_dir(const std::vector<std::string>& arg){

}
