'use client'
import { useGlobalState } from '../globals';
import { sendMsg, getJsonResponse } from '../websocket';
import { useRouter } from 'next/navigation';
import Image from 'next/image';
import React from 'react';
import TakiLogo from '../taki_logo.png'

const createRoomCode = process.env.CREATEROOM_CODE;
const succesCode = process.env.SUCCESS;

export default function Page()
{
  return (
    <main className="bg-slate-200 w-screen h-screen">
      <div className="w-screen h-16 fixed">
        <MyNavBar/>
      </div>
      <div>
        <CreateRoomForum/>
      </div>
    </main>
  );
}

async function createRoom(msg: string)
{
  
    try {
        const response = await sendMsg(createRoomCode!.charAt(0), msg);
        const jsonRes = getJsonResponse(response);
        
        if (jsonRes.status == succesCode) 
        {
            return jsonRes.roomId;
        } 
        else 
        {
          alert(response);
          return '';
        }
      } catch (error) {
        alert(error);
        return '';
      }
}

function isParamsOk(playerNum : number, timePerPlay : number)
{
  return ((playerNum >= 2 && playerNum <= 6) && (timePerPlay >= 5 && timePerPlay <= 30));
}

const CreateRoomForum = () => 
{

  const [room_name, setName] = React.useState('');
  const [maxPlayers, setMaxPlayers] = React.useState(0);
  const [timePerPlay, setTime] = React.useState(0);
  const [global_username, setUsername] = useGlobalState("username");
  const [isAdmin, setIsAdmin] = useGlobalState("isAdmin");

  const router = useRouter();

  const handleSumbit = async (e: React.FormEvent<HTMLFormElement>) => 
  {
    e.preventDefault();
    if (isParamsOk(maxPlayers, timePerPlay))
    {
      const message = `"roomName":"${room_name}","maxUsers":${maxPlayers},"answerTimeout":${timePerPlay}`;
      console.log(message)
      createRoom(message).then((roomID) => 
      {
          if (roomID != '')
          {
            setIsAdmin(true);
            alert(`room *${room_name}* has been created.`);
            router.push(`/rooms/${roomID}`);
          } 
      })
      .catch((error) => {
        console.error(error);
      });
    }
    else alert('invalid params');

  };


  return (
    <nav className="flex items-center justify-center min-h-screen">
      <div className="text-center bg-white py-5 px-8 shadow-md rounded-md sm:max-w-lg mx-16">
        <p className=' text-black font-medium text-2xl'>Create Room</p>
        <hr className="w-48 h-1 mx-auto bg-gray-100 border-0 rounded md:my-6 dark:bg-gray-700"/>
        <form onSubmit={handleSumbit}>
            <input
                type="text"
                placeholder="Enter Room Name"
                className="rounded px-16 py-2 mt-8 border-2 border-gray-300"
                onChange={(e) => setName(e.target.value)}
                required
            />
            <br />
            <input
                type="number"
                placeholder="Enter Max Players(2-6)"
                className="rounded px-16 py-2 mt-8 border-2 border-gray-300"
                onChange={(e) => setMaxPlayers(parseInt(e.target.value))}
                required
            />
            <br />
            <input
                type="number"
                placeholder="Enter Time Per Turn(5-30)"
                className="rounded px-16 py-2 my-7 border-2 border-gray-300"
                onChange={(e) => setTime(parseInt(e.target.value))}
                required
            />
            <br />
            <button
                type="submit"
                className="bg-blue-500 text-white mt-2 py-3 px-[152px] rounded-md text-center hover:bg-gradient-to-r from-blue-500 to-blue-400"
                >
                Submit
            </button>
        </form>
      </div>
    </nav>
  );
};

const HomeBarLink = () => {
  return (
    <div>
      <a href="./">
        <Image src={TakiLogo} alt="My Image" width={100} height={100} className="cursor-pointer" />
      </a>
    </div>
  );
};

const MyNavBar = () => {
  return (
    <div className="bg-white sticky shadow-md border-blue-500">
      <div className="flex justify-center items-center h-16">
        <HomeBarLink />
      </div>
    </div>
  );
};