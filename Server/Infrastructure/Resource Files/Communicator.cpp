# include "../Header Files/Communicator.h"


Communicator::Communicator(RequestHandlerFactory& factory) : m_handlerFactory(factory)
{}

void Communicator::startHandleRequests()
{
	try 
	{
		bindAndListen();
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

}

void Communicator::bindAndListen()
{
	// Create a TCP acceptor to listen for incoming connections
	boost::asio::io_context io_context;
	tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));

	std::cout << "Accepting clients...\n";
	while (true)
	{
		acceptClients(&acceptor, &io_context);
	}
}

void Communicator::acceptClients(tcp::acceptor* acceptor, boost::asio::io_context* io_context)
{
	tcp::socket cSocket(*io_context);
	acceptor->accept(cSocket);

	auto ws = std::make_shared<websocket::stream<boost::asio::ip::tcp::socket>>(std::move(cSocket));

	_mtx.lock();
	addClientToMap(ws);
	_mtx.unlock();

	std::cout << "New client join\n";

	std::thread(&Communicator::handleNewClient, this, std::move(ws)).detach();
}

void Communicator::addClientToMap(std::shared_ptr<websocket::stream<tcp::socket>> cSocket)
{
	std::shared_ptr<LoginRequestHandler> handler = m_handlerFactory.createLoginRequestHandler();

    m_clients.insert(std::make_pair(cSocket, handler));
}

void Communicator::handleNewClient(std::shared_ptr<websocket::stream<tcp::socket>> clientSocket)
{
	try
	{
		handleClient(clientSocket);
	}
	catch (const std::exception& e)
	{
		std::cerr << "User disconnected.\n" << std::endl;
		m_clients.erase(clientSocket);
	}
}

void Communicator::handleClient(std::shared_ptr<websocket::stream<tcp::socket>> clientSocket)
{
	// Construct a WebSocket stream from the socket
	clientSocket->accept();

	try
	{
		while (true)
		{
			std::string msg = getMsgFromClient(*clientSocket);
			
			auto req = msgToReqInfo(msg);

			_mtx.lock();
			RequestResult res = m_clients[clientSocket]->handleRequest(req);
			if (res.newHandler != nullptr) m_clients[clientSocket] = res.newHandler;
			_mtx.unlock();

			std::string serverMsg(res.buffer.begin(), res.buffer.end());


			sendMsgToClient(*clientSocket, serverMsg);
		}
	}
	catch (const std::exception& e)
	{
		m_clients.erase(clientSocket);
	}
}


std::string Communicator::getMsgFromClient(websocket::stream<tcp::socket>& ws)
{
	boost::beast::flat_buffer buffer;
	ws.read(buffer);

	return boost::beast::buffers_to_string(buffer.data());
}


void Communicator::sendMsgToClient(websocket::stream<boost::asio::ip::tcp::socket>& ws, std::string msg)
{
	ws.write(boost::asio::buffer(msg));
}


RequestInfo Communicator::msgToReqInfo(std::string msg)
{
	RequestInfo reqInfo;

	// Get time 
	auto time = std::chrono::system_clock::now();
	reqInfo.receivalTime = std::chrono::system_clock::to_time_t(time);

	// Get id 
	reqInfo.id = msg.at(0);

	// get buffer
	reqInfo.buffer = strToVec(msg);

	return reqInfo;
}

