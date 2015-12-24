#include "connection.hpp"


connection::connection()
{

}


void connection::start ()
{
    // read
    do_read();
}

void connection::do_read()
{
    auto self = shared_from_this();
    socket_.read_some ( boost::buffer(buff_),
        [this, self] (const boost::system::error_code& ec, size_t size_trans)
        {
            if (!ec)
            {
                do_write ();
            }

           else if (ec != boost::asio::error::operation_aborted)
           {
               connection_manager_.stop(shared_from_this());
           }

        } );
}


void connection::do_write ()
{
    auto self = shared_from_this();
    boost::asio::async_write (socket_, boost::asio::buffer(buff_),
        [this, self] (const boost::system::error_code& ec, size_t size_trans)
        {
            boost::system::error_code ec;
            socket_.shutdown (tcp::socket::shutdown_both, ec);
        });
}

void connection::stop ()
{
    socket_.close ();
}
