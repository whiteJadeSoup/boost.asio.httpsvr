
#include "Server.h"
#include "connection.hpp"
#include <signal.h>
#include <utility>
#include <boost/asio.hpp>

using  boost::asio::ip::tcp;

namespace http {
namespace server {

Server::Server(const std::string& address,
    const std::string& port, const std::string& doc_root)
    : io_service_(),
    signals_ (io_service_),
    acceptor_ (io_service_),
    socket_ (io_service_)
{
    signals_.add ( SIGINT );
    signals_.add ( SIGTERM );
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)


    do_await_stop ();

    tcp::resolver resolver (io_service_);
    tcp::endpoint endpoint = *resolver.resolve ( {address, port} );


    acceptor_.open ( endpoint.protocol() );
    acceptor_.set_option( tcp::acceptor::reuse_address(true) );
    acceptor_.bind (endpoint);
    acceptor_.listen ();


    do_accept ();
}


void Server::run ()
{
    io_service_.run();
}

void Server::do_accept()
{
    acceptor_.async_accept (socket_,
        [this] (const boost::system::error_code& ec)
        {
            if ( !acceptor_.is_open() )
            {
                return ;
            }
            if (!ec)
            {
                connection_manager_.start( std::make_shared<connection>() );
            }

            do_accept();
        });
}

void Server::do_await_stop ()
{
    signals_.async_wait ( [this] (const boost::system::error_code& ec, int sign_no) {
        acceptor_.close ();
        connection_manager_.stop_all();
    } );
}

} // server
} // http

