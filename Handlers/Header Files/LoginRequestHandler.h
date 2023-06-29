#pragma once
#include "IRequestHandler.h"
# include "../../UsefullFunctions/Header Files/stringFuncs.h"
# include "../../Infrastructure/Header Files/RequestHandlerFactory.h"

// Forward declarations
class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
    public:
        LoginRequestHandler(RequestHandlerFactory& handlerFactory);

        bool isRequestRelevant(RequestInfo rInfo) override;
        RequestResult handleRequest(RequestInfo rInfo) override;

    private:
        RequestResult login(RequestInfo rInfo);
        RequestResult signup(RequestInfo rInfo);

        RequestHandlerFactory& m_handlerFactory;
};