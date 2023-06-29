#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "json.hpp"

#define BASE16 16
#define SMALLF 'f'
#define SMALLA 'a'
#define CAPITALF 'F'
#define CAPITALA 'A'
#define STARTRANGE '0'
#define ENDRANGE '9'
#define ADDTEN 10
#define DEFAULTVALUE 0
#define STARTDATA 1
#define LENRANGESTART 1
#define LENRANGEEND 4

typedef struct PlaceCardRequest
{
	std::string cardId;
} PlaceCardRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
} SubmitAnswerRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct LoginRequest
{
	std::string username;
	std::string password;
} LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} SignupRequest;


typedef struct LeaveRoomRequest {
	unsigned int status;
} LeaveRoomRequest;

typedef struct GetRoomStateRequest {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int answerTimeout;
} GetRoomStateRequest;

typedef struct CloseRoomRequest {
	unsigned int status;
} CloseRoomRequest;

typedef struct StartGameRequest {
	unsigned int status;
} StartGameRequest;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);

	static CloseRoomRequest deserializeCloseRoomRequest(std::vector<unsigned char> buffer);
	static StartGameRequest deserializeStartGameRequest(std::vector<unsigned char> buffer);
	static GetRoomStateRequest deserializeGetRoomStateRequest(std::vector<unsigned char> buffer);
	static LeaveRoomRequest deserializeLeaveRoomRequest(std::vector<unsigned char> buffer);

	static PlaceCardRequest deserializePlaceCardRequest(std::vector<unsigned char> buffer);
};