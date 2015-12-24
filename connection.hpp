#ifndef CONNECTION_HPP_INCLUDED
#define CONNECTION_HPP_INCLUDED


#include "connection_manager.cpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class connection : public std::enable_shared_from_this<connection>
{
public:
    typedef std::shared_ptr<connection> connection_ptr;

    connection () ;
    void start ();
    void stop ();

private:
    void do_read  ();
    void do_write ();

private:
    // for next connection
    tcp::socket socket_;

    // array for request
    std::array <char, 8250> buff_;

    // manager for all connection
    connection_manager& connection_manager_;
};

#endif // CONNECTION_HPP_INCLUDED
