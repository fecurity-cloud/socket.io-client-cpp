//
//  sio_client.h
//
//  Created by Melo Yao on 3/25/15.
//

#ifndef SIO_CLIENT_H
#define SIO_CLIENT_H
#include <string>
#include <functional>
#include "sio_message.h"
#include "sio_socket.h"

namespace sio
{
    class client_impl;
    
    class client {
    public:
        enum close_reason
        {
            close_reason_normal,
            close_reason_drop
        };
        
        typedef std::function<void(void)> con_listener;
        
        typedef std::function<void(close_reason const& reason)> close_listener;

        typedef std::function<void(unsigned, unsigned)> reconnect_listener;
        
        typedef std::function<void(std::string const& nsp)> socket_listener;
        
        client();
        ~client();
        
        //set listeners and event bindings.
        void set_open_listener(con_listener const& l) const;
        
        void set_fail_listener(con_listener const& l) const;
        
        void set_reconnecting_listener(con_listener const& l) const;

        void set_reconnect_listener(reconnect_listener const& l) const;

        void set_close_listener(close_listener const& l) const;
        
        void set_socket_open_listener(socket_listener const& l) const;
        
        void set_socket_close_listener(socket_listener const& l) const;
        
        void clear_con_listeners() const;
        
        void clear_socket_listeners() const;
        
        // Client Functions - such as send, etc.
        void connect(const std::string& uri) const;

        void connect(const std::string& uri, const message::ptr& auth) const;

        void connect(const std::string& uri, const std::map<std::string,std::string>& query) const;

        void connect(const std::string& uri, const std::map<std::string,std::string>& query, const message::ptr& auth) const;

        void connect(const std::string& uri, const std::map<std::string,std::string>& query,
                     const std::map<std::string,std::string>& http_extra_headers) const;

        void connect(const std::string& uri, const std::map<std::string,std::string>& query,
                     const std::map<std::string,std::string>& http_extra_headers, const message::ptr& auth) const;

        void set_reconnect_attempts(int attempts) const;

        void set_reconnect_delay(unsigned millis) const;

        void set_reconnect_delay_max(unsigned millis) const;

        void set_logs_default() const;

        void set_logs_quiet() const;

        void set_logs_verbose() const;

        sio::socket::ptr const& socket(const std::string& nsp = "") const;
        
        // Closes the connection
        void close() const;
        
        void sync_close() const;
        
        void set_proxy_basic_auth(const std::string& uri, const std::string& username, const std::string& password) const;
		
        bool opened() const;
        
        std::string const& get_sessionid() const;
        
    private:
        //disable copy constructor and assign operator.
        client(client const&){}
        void operator=(client const&){}
        
        client_impl* m_impl;
    };
    
}


#endif // __SIO_CLIENT__H__
