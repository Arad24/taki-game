#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
# include "json.hpp"
#include "../../Managers/Header Files/RoomManager.h"

#define CREATEROOM_CODE '6'
# define LOGOUT_CODE '3'
# define JOINROOM_CODE '5'
# define GETROOMS_CODE '4'
# define HIGHSCORE_CODE '8'
# define PLAYERSINROOM_CODE '7'
# define PERSONALSTATS_CODE '9'
# define LENNUM 4
# define ERROR_CODE  '0'
# define LOGIN_CODE  '1'
# define SIGNUP_CODE '2'
# define SUCCESS	 1
# define CLOSEROOM_CODE 'A'
# define STARTGAME_CODE 'B'
# define GETROOMSTATE_CODE 'C'
# define LEAVEROOM_CODE 'D'
# define LEAVEGAME_CODE 'E'
# define DRAWCARD_CODE 'F'
# define CALLLASTCARD_CODE 'G'
# define PLACECARD_CODE 'H'
# define GETGAMERESULTS_CODE 'I'
# define GETONGOINGGAME_CODE 'J'
# define CLOSETAKI_CODE 'K'


typedef struct closeTakiResponse {
	unsigned int status;
};

typedef struct DrawCardFromDeckResponse {
	unsigned int status;
} DrawCardFromDeck;

typedef struct CallLastCardInHandResponse {
	unsigned int status;
} CallLastCardInHandResponse;

typedef struct PlaceCardResponse {
	unsigned int status;
} PlaceCardResponse;

typedef struct LeaveGameResponse {
	unsigned int status;
} LeaveGameResponse;

typedef struct GetQuestionResponse {
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
} GetQuestionResponse;

typedef struct SubmitAnswerResponse {
	unsigned int status;
	unsigned int correctAnswerId;
} SubmitAnswerResponse;

typedef struct PlayerResults {
	std::string username;
	unsigned int cardsInHand;
	unsigned int place;

	nlohmann::json toJson() const
	{
		nlohmann::json js = {
			{"username", username},
			{"cardsInHand", cardsInHand},
			{"place", place},
		};
		return js;
	}
} PlayerResults;

typedef struct GetGameResultsResponse {
	unsigned int status;
	std::vector<PlayerResults> results;
} GetGameResultsResponse;

typedef struct CloseRoomResponse {
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse {
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse {
	unsigned int status;
	int hasGameBegun;
	std::vector<std::string> players;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse {
	unsigned int status;
} LeaveRoomResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
	unsigned int roomId;
} CreateRoomResponse;

typedef struct LogoutResponse {
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
} GetPlayersInRoomResponse;

typedef struct getHighScoreResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} getHighScoreResponse;

typedef struct getPersonalStatsResponse {
	unsigned int status;
	std::vector<std::string> statistics;
} getPersonalStatsResponse;


typedef struct LoginResponse {
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
	std::string message;
} ErrorResponse;

typedef struct getOngoingGameStateResponse
{
	unsigned int status;
	std::vector<std::string> currentCards;
	std::map<std::string, unsigned int> CardsPerPlayer;
	std::string lastCardPlay;
	std::string currentPlayer;
	bool gameDirection;
	bool isGameEnd;
} getOngoingGameStateResponse;


class JsonResponsePacketSerializer
{
	public:
		static std::vector<unsigned char> SerializeResponse(ErrorResponse response);
		static std::vector<unsigned char> SerializeResponse(LoginResponse response);
		static std::vector<unsigned char> SerializeResponse(SignupResponse response);

		static std::vector<unsigned char> SerializeResponse(LogoutResponse response);
		static std::vector<unsigned char> SerializeResponse(GetRoomsResponse response);
		static std::vector<unsigned char> SerializeResponse(GetPlayersInRoomResponse response);
		static std::vector<unsigned char> SerializeResponse(JoinRoomResponse response);
		static std::vector<unsigned char> SerializeResponse(CreateRoomResponse response);
		static std::vector<unsigned char> SerializeResponse(getHighScoreResponse response);
		static std::vector<unsigned char> SerializeResponse(getPersonalStatsResponse response);

		static std::vector<unsigned char> SerializeResponse(CloseRoomResponse response);
		static std::vector<unsigned char> SerializeResponse(StartGameResponse response);
		static std::vector<unsigned char> SerializeResponse(GetRoomStateResponse response);
		static std::vector<unsigned char> SerializeResponse(LeaveRoomResponse response);

		static std::vector<unsigned char> SerializeResponse(GetGameResultsResponse response);
		static std::vector<unsigned char> SerializeResponse(DrawCardFromDeck response);
		static std::vector<unsigned char> SerializeResponse(PlaceCardResponse response);
		static std::vector<unsigned char> SerializeResponse(CallLastCardInHandResponse response);
		static std::vector<unsigned char> SerializeResponse(LeaveGameResponse response);

		static std::vector<unsigned char> SerializeResponse(getOngoingGameStateResponse response);
		static std::vector<unsigned char> SerializeResponse(closeTakiResponse response);

};
