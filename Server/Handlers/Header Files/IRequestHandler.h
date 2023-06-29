#pragma once
#include <vector>
#include <ctime>
#include <memory>
# include "../../Request/Header Files/JsonRequestPacketDeserializer.h"
# include "../../Request/Header Files/JsonResponsePacketSerializer.h"


class IRequestHandler;
class JsonResponsePacketSerializer;
class JsonRequestPacketDeserializer;

struct RequestResult
{
	std::vector<unsigned char> buffer;
	std::shared_ptr<IRequestHandler> newHandler;
};

struct RequestInfo
{
	char id;
	std::time_t receivalTime;
	std::vector<unsigned char> buffer;
};

class IRequestHandler
{
	public:
		virtual bool isRequestRelevant(RequestInfo rInfo) = 0;
		virtual RequestResult handleRequest(RequestInfo rInfo) = 0;
};
