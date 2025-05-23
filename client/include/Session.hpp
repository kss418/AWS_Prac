#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>
#include <future>

namespace http = boost::beast::http;

class Session{
public:
    using tcp = boost::asio::ip::tcp;
    
    Session(
        boost::asio::io_context& io_context,
        const std::string& ip,
        unsigned short port,
        std::promise <http::response <http::string_body>>& prom,
        http::verb method,
        boost::beast::string_view target,
        nlohmann::json body = {}
    );

    void write();
    void read();
private:
    tcp::endpoint m_endpoint;
    boost::beast::tcp_stream m_socket;
    const int m_version = 11;
    boost::beast::flat_buffer m_buffer;
    http::verb m_method;
    boost::beast::string_view m_target;
    nlohmann::json m_body;
    std::string m_host;
    std::promise <http::response <http::string_body>>& m_prom;
    http::response <http::string_body> m_res;

    void handle_connect(const boost::system::error_code& ec);
    void handle_write(
        const boost::system::error_code& ec,
        std::size_t bytes_transffered
    );
    void handle_read(
        const boost::system::error_code& ec,
        std::size_t bytes_transffered
    );
};