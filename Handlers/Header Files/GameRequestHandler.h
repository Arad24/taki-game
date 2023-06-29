#pragma once
# include "IRequestHandler.h"
# include "../../UsefullFunctions/Header Files/stringFuncs.h"
# include "../../Infrastructure/Header Files/RequestHandlerFactory.h"
# include "../../Managers/Header Files/GameManager.h"

// Forward declarations
class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
	public:
		GameRequestHandler(RequestHandlerFactory& handlerFactory, GameManager& gameManager, LoggedUser user, Game game);

		bool isRequestRelevant(RequestInfo rInfo) override;
		RequestResult handleRequest(RequestInfo rInfo) override;

	private:
		Game m_game;
		LoggedUser m_user;
		GameManager& m_gameManager;
		RequestHandlerFactory& m_handlerFactory;


		RequestResult leaveGame(RequestInfo rInfo);
		RequestResult playCard(RequestInfo rInfo);
		RequestResult getGameResults(RequestInfo rInfo);
		RequestResult drawCard(RequestInfo rInfo);
		RequestResult getGameStatus(RequestInfo rInfo);
		RequestResult closeTaki(RequestInfo rInfo);
};

