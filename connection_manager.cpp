



#ifndef CONNECT_MANAGER_HPP_INCLUDED
#define CONNECT_MANAGER_HPP_INCLUDED

#include "connection.hpp"
#include <set>

class connection_manager
{
public:
    connection_manager ();

    void start (connection::connection_ptr);
    void stop (connection::connection_ptr);
    void stop_all ();
private:
    std::set<connection::connection_ptr> connections_;
};


connection_manager::connection_manager()
{

}

void connection_manager::start(connection::connection_ptr connection)
{
    connections_.insert (connection);
    connection->start ();
}

void connection_manager::stop(connection::connection_ptr connection)
{
    connections_.erase (connection);
    connection->stop ();
}



void connection_manager::stop_all()
{
    for (auto ptr : connections_)
    {
        ptr->stop ();
    }
    connections_.clear();
}

#endif // CONNECT_MANAGER_HPP_INCLUDED
