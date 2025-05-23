#include "../include/Session.hpp"
#include <iostream>

Session::Session(
    boost::asio::io_context& io_context,
    const std::string& ip,
    unsigned short port,
    std::promise <http::response <http::string_body>>& prom,
    http::verb method,
    boost::beast::string_view target,
    nlohmann::json body
) : m_endpoint(boost::asio::ip::make_address_v4(ip), port),
    m_socket(io_context),
    m_method(method),
    m_target(target),
    m_body(body),
    m_prom(prom)
{
    m_host = ip + ":" + std::to_string(port);
    m_socket.async_connect(
        m_endpoint, 
        [this](const boost::system::error_code& ec){
            handle_connect(ec);
        }
    );
}

void Session::write(){
    auto req = std::make_shared<http::request<http::string_body>>(
        m_method, m_target, m_version
    );
    req->set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req->set(http::field::host, m_host);
    
    if(!m_body.empty()){
        req->body() = m_body.dump();
        req->prepare_payload();
    }

    http::async_write(
        m_socket,
        *req,
        [req, this](
            const boost::system::error_code& ec,
            std::size_t bytes_transffered
        ){
            handle_write(ec, bytes_transffered);
        }
    );
}

void Session::read(){
    http::async_read(
        m_socket,
        m_buffer,
        m_res,
        [this](
            const boost::system::error_code& ec,
            std::size_t bytes_transffered
        ){
            handle_read(ec, bytes_transffered);
        }
    );
}