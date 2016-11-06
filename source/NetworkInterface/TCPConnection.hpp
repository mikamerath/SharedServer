#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TCPConnection
  : public boost::enable_shared_from_this<TCPConnection>
{
public:
  typedef boost::shared_ptr<TCPConnection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new TCPConnection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  ip::basic_endpoint<ip::tcp> remoteEndpoint() 
  {
    return socket_.remote_endpoint();
  }

  ip::basic_endpoint<ip::tcp> localEndpoint()
  {
    return socket_.local_endpoint();
  }

  void connect(boost::asio::ip::basic_endpoint<boost::asio::ip::tcp> ep) {
    socket_.connect(ep);
  }

  void send(std::string msg) {
    
  }

  void start()
  {
    /*message_ = make_daytime_string();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
      boost::bind(&TCPConnection::handle_write, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));*/
  }

private:
  TCPConnection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
    size_t /*bytes_transferred*/)
  {
  }

  tcp::socket socket_;
  std::string message_;
};
#endif // !TCP_CONNECTION
