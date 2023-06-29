# include "../Header Files/GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, GameManager& gameManager, LoggedUser user, Game game) 
	: m_handlerFactory(handlerFactory), m_gameManager(gameManager), m_user(user), m_game(game) {}

bool GameRequestHandler::isRequestRelevant(RequestInfo rInfo)
{
	return rInfo.id >= LEAVEGAME_CODE && rInfo.id <= CLOSETAKI_CODE;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo rInfo)
{
	if (isRequestRelevant(rInfo))
	{
		RequestResult res;
		switch (rInfo.id)
		{
			case LEAVEGAME_CODE: // Leave room
				res = leaveGame(rInfo);
				break;

			case DRAWCARD_CODE: // Take card
				res = drawCard(rInfo);
				break;
			
			case CALLLASTCARD_CODE:
				break;

			case PLACECARD_CODE: // Card on the table
				res = playCard(rInfo);
				break;

			case GETGAMERESULTS_CODE: // At the end
				res = getGameResults(rInfo);
				break;

			case GETONGOINGGAME_CODE:
				res = getGameStatus(rInfo);
				break;

			case CLOSETAKI_CODE:
				res = closeTaki(rInfo);
				break;

			default:
				ErrorResponse errRes = { "Invalid Request" };
				res = { JsonResponsePacketSerializer::SerializeResponse(errRes), nullptr };
				break;
		}

		return res;
	}
	else
	{
		ErrorResponse res = { "Invalid Request" };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}


RequestResult GameRequestHandler::leaveGame(RequestInfo rInfo)
{
	try
	{
		m_gameManager.getGameById(m_game.getId())->removePlayer(m_user);

		LeaveGameResponse res = { SUCCESS };
		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	catch (const std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult GameRequestHandler::playCard(RequestInfo rInfo)
{
	try
	{
		auto req = JsonRequestPacketDeserializer::deserializePlaceCardRequest(rInfo.buffer);

		Card card(req.cardId.substr(1, req.cardId.length()), req.cardId[0]);

		m_gameManager.getGameById(m_game.getId())->playCard(m_user, card);

		PlaceCardResponse res = { SUCCESS };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	catch (const std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult GameRequestHandler::getGameResults(RequestInfo rInfo)
{
	try
	{

		GetGameResultsResponse res = { SUCCESS, m_gameManager.getGameById(m_game.getId())->getPlayers() };

		m_gameManager.addGameResults(m_game.getId(), m_user.getUsername());


		if (m_gameManager.getGameById(m_game.getId())->addPlayerEnd() == m_game.getPlayers().size())
		{
			m_gameManager.deleteGame(m_game.getId());
		}

		return { JsonResponsePacketSerializer::SerializeResponse(res), m_handlerFactory.createMenuRequestHandler(m_user.getUsername()) };
	}
	catch (const std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}

}


RequestResult GameRequestHandler::drawCard(RequestInfo rInfo)
{
	try
	{
		auto game = m_gameManager.getGameById(m_game.getId());
		int cardsNum = 1;
		if (game->getPlus() != 0) cardsNum = game->getPlus();

		for (int i = 0; i < cardsNum; i++)
		{
			game->getPlayerCards(m_user)->addCard(game->drawCards(1, m_user.getUsername())->getRandomCard());
		}
		

		m_gameManager.getGameById(m_game.getId())->setPlus(0);
		m_gameManager.getGameById(m_game.getId())->moveToNextPlayer();

		DrawCardFromDeckResponse res = { SUCCESS };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	catch (const std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}

RequestResult GameRequestHandler::getGameStatus(RequestInfo rInfo)
{
	try
	{
		auto game = m_gameManager.getGameById(m_game.getId());

		getOngoingGameStateResponse res = {
			SUCCESS, 
			game->getPlayerCards(m_user)->toString(),
			game->getCardsPerPlayer(), 
			game->getLastCardPlay(), 
			game->getCurrPlayer(), 
			game->getDirection(),
			game->getIsGameEnd()
		};

		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
	catch (const std::exception& e)
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
	}
}


RequestResult GameRequestHandler::closeTaki(RequestInfo rInfo)
{
	{
		try
		{
			auto game = m_gameManager.getGameById(m_game.getId());

			game->closeTaki();

			CloseRoomResponse res = { SUCCESS };

			return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
		}
		catch (const std::exception& e)
		{
			ErrorResponse res = { e.what() };
			return { JsonResponsePacketSerializer::SerializeResponse(res), nullptr };
		}
	}
}
